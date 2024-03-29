#include <ros/ros.h>
#include "openarms/ArmSensors.h"
#include "openarms/ArmActuators.h"
using std::string;

double g_gripper_target = 0;
ros::Publisher *g_actuator_pub = NULL;
openarms::ArmActuators g_actuators;
//double g_stepper_vel[4];
uint16_t g_encoder_target[4] = {0, 0, 0, 0};

void sensors_cb(const openarms::ArmSensors::ConstPtr &msg)
{
  const double MAX_VEL_BIGDOGS = 1000, MAX_VEL_LITTLEDOGS = 1000;
  const double MAX_ACCEL_PER_SEC = 20000;
  static ros::Time s_prev_time;
  static bool s_prev_time_init = false;
  static double s_prev_encoder[4];
  static bool chatter_forward = true;

  if (!s_prev_time_init)
  {
    s_prev_time_init = true;
    s_prev_time = ros::Time::now();
    for (int i = 0; i < 4; i++)
      s_prev_encoder[i] = 0;
    return;
  }
  else
  {
    ros::Time t = ros::Time::now();
    double dt = (t - s_prev_time).toSec();
    if (dt > 0.05)
    {
      for (int i = 0; i < 4; i++)
        g_actuators.stepper_vel[i] = 0;
      for (int i = 0; i < 1; i++)
      {
        if (chatter_forward)
          g_actuators.stepper_vel[i] = 50;
        else
          g_actuators.stepper_vel[i] = -50;
      }
      chatter_forward = !chatter_forward;
      s_prev_time = t;
    }
    for (int i = 4; i < 8; i++)
      g_actuators.servo_torque[i-4] = 0;
    g_actuator_pub->publish(g_actuators);
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "find_stepper_home");
  ros::NodeHandle n;
  ros::Subscriber sensors_sub = n.subscribe("arm_sensors", 1, sensors_cb);
  ros::Publisher actuator_pub = n.advertise<openarms::ArmActuators>("arm_actuators_autopilot", 1);

  g_actuator_pub = &actuator_pub;
  g_actuators.stepper_vel.resize(4);
  g_actuators.servo_torque.resize(4);
  for (int i = 0; i < 4; i++)
  {
    g_actuators.stepper_vel[i] = 0;
    g_actuators.servo_torque[i] = 0;
  }

  ros::Rate loop_rate(100);
  while (ros::ok())
  {
    loop_rate.sleep();
    ros::spinOnce();
  }
}

