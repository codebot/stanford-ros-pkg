#include <ros/ros.h>
#include "sensor_msgs/JointState.h"
#include "openarms/ArmActuators.h"
#include "openarms/SetJointTarget.h"
using std::string;

sensor_msgs::JointState g_target;
double g_gripper_target = 0;
ros::Publisher *g_actuator_pub = NULL;
openarms::ArmActuators g_actuators;
//double g_stepper_vel[4];
static double g_servo_integral_err[4] = {0.0, 0.0, 0.0, 0.0};

void target_cb(const sensor_msgs::JointState &target_msg)
{
  g_target = target_msg;
}

bool set_joint_target_srv(openarms::SetJointTarget::Request &req,
                          openarms::SetJointTarget::Response &res)
{
  g_target = req.target;
  return true;
}

void state_cb(const sensor_msgs::JointState::ConstPtr &state_msg)
{
  const double MAX_VEL_BIGDOGS = 5000, MAX_VEL_LITTLEDOGS = 8000;
  const double MAX_ACCEL_PER_SEC = 60000;
  static ros::Time s_prev_time;
  static bool s_prev_time_init = false;

  static double s_prev_encoder[4];
  static double s_prev_vel[4];
  
  // Upper 4 DOF PID gains:
  //               0    1    2    3
  const double stepper_ki[4] = {400.0, 400.0, 650.0, 800.0};
  //const double stepper_ki[4] = {0, 0, 0, 0};

  //const double stepper_kp[4] = {-40000, -40000, 0.0, 0.0};
  const double stepper_kp[4] = {-40000, -50000, -65000, -80000};
  const double stepper_kd[4] = {0.0, 0.0, 0.0, 0.0};
  const double pos_err_sat[4] = {0.1, 0.1, 0.1, 0.2};
  
  if (!s_prev_time_init)
  {
    s_prev_time_init = true;
    s_prev_time = ros::Time::now();
    for (int i = 0; i < 4; i++)
    {
      s_prev_encoder[i] = 0;
      s_prev_vel[i] = 0;
    }
    return; // come back next time when ur initialized SEE YA
  }

  if (g_target.position.size() < 7)
    return; // bogus

  ros::Time t = ros::Time::now();
  double dt = (t - s_prev_time).toSec();
  s_prev_time = t;
  const int32_t MAX_ACCEL = (int32_t)(MAX_ACCEL_PER_SEC * dt);

  // compute *actual* velocities and accels using the state_msg positions, 
  // which are the actual encoder readings:
  double pos_err[4], vel[4], accel[4];
  for (int i = 0; i < 4; i++)
  {
    // low-pass filter the encoders to smooth out their difference...
    vel[i] = 0.3*(state_msg->position[i] - s_prev_encoder[i]) + 
             0.7*s_prev_vel[i];
    s_prev_encoder[i] = state_msg->position[i];
    if (vel[i] < -8000)
      vel[i] += 10000;
    else if (vel[i] > 8000)
      vel[i] -= 10000;

    accel[i] = vel[i] - s_prev_vel[i];
    s_prev_vel[i] = vel[i];

    pos_err[i] = g_target.position[i] - state_msg->position[i]; // rad
    // saturate this so it doesn't dominate the velocity loop
    if (pos_err[i] > pos_err_sat[i])
      pos_err[i] = pos_err_sat[i];
    else if (pos_err[i] < -pos_err_sat[i])
      pos_err[i] = -pos_err_sat[i];
  }

  double desired_vel[4];
  desired_vel[0] = stepper_ki[0] * pos_err[0]
                   - stepper_kp[0] * vel[0]
                   - stepper_kd[0] * accel[0];
  desired_vel[1] = 0.8096 * desired_vel[0]
                   + stepper_ki[1] * pos_err[1]
                   - stepper_kp[1] * vel[1]
                   - stepper_kd[1] * accel[1];
  desired_vel[2] = 0.47934 * desired_vel[1]
                   + stepper_ki[2] * pos_err[2]
                   - stepper_kp[2] * vel[2]
                   - stepper_kd[2] * accel[2]; 
  desired_vel[3] = 0.47934 * desired_vel[1]
                   + stepper_ki[3] * pos_err[3]
                   - stepper_kp[3] * vel[3]
                   - stepper_kd[3] * accel[3];

  // saturate steppers
  for (int i = 0; i < 4; i++)
  {
    double des_accel = desired_vel[i] - g_actuators.stepper_vel[i];

    // enforce acceleration limit
    if (des_accel > MAX_ACCEL)
      des_accel = MAX_ACCEL;
    else if (des_accel < -MAX_ACCEL)
      des_accel = -MAX_ACCEL;

    // enforce velocity limit
    g_actuators.stepper_vel[i] += des_accel;
    const double MAX_VEL = (i < 2 ? MAX_VEL_BIGDOGS : MAX_VEL_LITTLEDOGS);
    if (g_actuators.stepper_vel[i] > MAX_VEL)
      g_actuators.stepper_vel[i] = MAX_VEL;
    else if (g_actuators.stepper_vel[i] < -MAX_VEL)
      g_actuators.stepper_vel[i] = -MAX_VEL;
  }
  // handle the servos
  for (int i = 4; i < 8; i++)
  {
    double err = 0;
    err = g_target.position[i] - state_msg->position[i];

    g_servo_integral_err[i-4] += err; //*dt;

    // keep it from having too large of an integral in case it is stuck
    double MAX_INTEGRAL = 1000;
    if (g_servo_integral_err[i-4] > MAX_INTEGRAL)
      g_servo_integral_err[i-4] = MAX_INTEGRAL;
    else if (g_servo_integral_err[i-4] < -MAX_INTEGRAL)
      g_servo_integral_err[i-4] = -MAX_INTEGRAL;

    double ki = 0; //40;  // integral gain
    double kp = 0; //2000; // proportional gain

    double desired_torque = kp * err + ki * g_servo_integral_err[i-4];

    //if (i == 4)
    //  printf("i=%d: kp*err = %f, ki*interr = %f\n",i,kp*err,ki*g_servo_integral_err[i-4]);

    // enforce torque limit
    int32_t MAX_TORQUE = 500;
    if (desired_torque > MAX_TORQUE)
      desired_torque = MAX_TORQUE;
    else if (desired_torque < -MAX_TORQUE)
      desired_torque = -MAX_TORQUE;
    g_actuators.servo_torque[i-4] = desired_torque;
  }
  // ship out the command
  g_actuator_pub->publish(g_actuators);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "control_jointspace");
  ros::NodeHandle n;
  ros::Subscriber target_sub = n.subscribe("target_joints", 1, target_cb);
  ros::Subscriber state_sub = n.subscribe("joint_states", 1, state_cb);
  ros::Publisher actuator_pub = n.advertise<openarms::ArmActuators>("arm_actuators_autopilot", 1);
  ros::ServiceServer service = n.advertiseService("set_joint_target",
                                                  set_joint_target_srv);
  g_actuator_pub = &actuator_pub;
  g_actuators.stepper_vel.resize(4);
  g_actuators.servo_torque.resize(4);
  for (int i = 0; i < 4; i++)
    g_actuators.stepper_vel[i] = 0;

  ros::Rate loop_rate(100);
  while (ros::ok())
  {
    loop_rate.sleep();
    ros::spinOnce();
  }
}

