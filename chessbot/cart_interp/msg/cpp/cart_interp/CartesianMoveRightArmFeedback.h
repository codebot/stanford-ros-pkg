/* auto-generated by genmsg_cpp from /home/davidmandle/rospackages/cart_interp/msg/CartesianMoveRightArmFeedback.msg.  Do not edit! */
#ifndef CART_INTERP_CARTESIANMOVERIGHTARMFEEDBACK_H
#define CART_INTERP_CARTESIANMOVERIGHTARMFEEDBACK_H

#include <string>
#include <vector>
#include "ros/message.h"
#include "ros/debug.h"
#include "ros/assert.h"
#include "ros/time.h"

#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Pose.h"

namespace cart_interp
{

//! \htmlinclude CartesianMoveRightArmFeedback.msg.html

class CartesianMoveRightArmFeedback : public ros::Message
{
public:
  typedef boost::shared_ptr<CartesianMoveRightArmFeedback> Ptr;
  typedef boost::shared_ptr<CartesianMoveRightArmFeedback const> ConstPtr;

  typedef geometry_msgs::Pose _currentpoint_type;

  geometry_msgs::Pose currentpoint;

  CartesianMoveRightArmFeedback() : ros::Message()
  {
  }
  CartesianMoveRightArmFeedback(const CartesianMoveRightArmFeedback &copy) : ros::Message(),
    currentpoint(copy.currentpoint)
  {
    (void)copy;
  }
  CartesianMoveRightArmFeedback &operator =(const CartesianMoveRightArmFeedback &copy)
  {
    if (this == &copy)
      return *this;
    currentpoint = copy.currentpoint;
    return *this;
  }
  virtual ~CartesianMoveRightArmFeedback() 
  {
  }
  inline static std::string __s_getDataType() { return std::string("cart_interp/CartesianMoveRightArmFeedback"); }
  inline static std::string __s_getMD5Sum() { return std::string("02a6b904b8484b60a59895e6158270a9"); }
  inline static std::string __s_getMessageDefinition()
  {
    return std::string(
    "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
    "# feedback definition\n"
    "geometry_msgs/Pose currentpoint\n"
    "\n"
    "================================================================================\n"
    "MSG: geometry_msgs/Pose\n"
    "# A representation of pose in free space, composed of postion and orientation. \n"
    "Point position\n"
    "Quaternion orientation\n"
    "\n"
    "================================================================================\n"
    "MSG: geometry_msgs/Point\n"
    "# This contains the position of a point in free space\n"
    "float64 x\n"
    "float64 y\n"
    "float64 z\n"
    "\n"
    "================================================================================\n"
    "MSG: geometry_msgs/Quaternion\n"
    "# This represents an orientation in free space in quaternion form.\n"
    "\n"
    "float64 x\n"
    "float64 y\n"
    "float64 z\n"
    "float64 w\n"
    "\n"
    "\n"
    );
  }
  inline virtual const std::string __getDataType() const { return __s_getDataType(); }
  inline virtual const std::string __getMD5Sum() const { return __s_getMD5Sum(); }
  inline virtual const std::string __getMessageDefinition() const { return __s_getMessageDefinition(); }
  inline uint32_t serializationLength() const
  {
    unsigned __l = 0;
    __l += currentpoint.serializationLength(); // currentpoint
    return __l;
  }
  virtual uint8_t *serialize(uint8_t *write_ptr,
#if defined(__GNUC__)
                             __attribute__((unused)) uint32_t seq) const
#else
                             uint32_t seq) const
#endif
  {
    write_ptr = currentpoint.serialize(write_ptr, seq);
    return write_ptr;
  }
  virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    read_ptr = currentpoint.deserialize(read_ptr);
    return read_ptr;
  }
};

typedef boost::shared_ptr<CartesianMoveRightArmFeedback> CartesianMoveRightArmFeedbackPtr;
typedef boost::shared_ptr<CartesianMoveRightArmFeedback const> CartesianMoveRightArmFeedbackConstPtr;


}

#endif
