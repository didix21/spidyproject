// Generated by gencpp from file communication_pkg/PWMFeedback.msg
// DO NOT EDIT!


#ifndef COMMUNICATION_PKG_MESSAGE_PWMFEEDBACK_H
#define COMMUNICATION_PKG_MESSAGE_PWMFEEDBACK_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace communication_pkg
{
template <class ContainerAllocator>
struct PWMFeedback_
{
  typedef PWMFeedback_<ContainerAllocator> Type;

  PWMFeedback_()
    : feedback(0)  {
    }
  PWMFeedback_(const ContainerAllocator& _alloc)
    : feedback(0)  {
    }



   typedef uint32_t _feedback_type;
  _feedback_type feedback;




  typedef boost::shared_ptr< ::communication_pkg::PWMFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::communication_pkg::PWMFeedback_<ContainerAllocator> const> ConstPtr;

}; // struct PWMFeedback_

typedef ::communication_pkg::PWMFeedback_<std::allocator<void> > PWMFeedback;

typedef boost::shared_ptr< ::communication_pkg::PWMFeedback > PWMFeedbackPtr;
typedef boost::shared_ptr< ::communication_pkg::PWMFeedback const> PWMFeedbackConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::communication_pkg::PWMFeedback_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::communication_pkg::PWMFeedback_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace communication_pkg

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'actionlib_msgs': ['/opt/ros/indigo/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'communication_pkg': ['/home/sxubach/Documents/Robot_Learning/robotLearning/catkin_ws/devel/share/communication_pkg/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::communication_pkg::PWMFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::communication_pkg::PWMFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::communication_pkg::PWMFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::communication_pkg::PWMFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::communication_pkg::PWMFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::communication_pkg::PWMFeedback_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::communication_pkg::PWMFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "cbfbf3355c876d056ca78e89534a5173";
  }

  static const char* value(const ::communication_pkg::PWMFeedback_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xcbfbf3355c876d05ULL;
  static const uint64_t static_value2 = 0x6ca78e89534a5173ULL;
};

template<class ContainerAllocator>
struct DataType< ::communication_pkg::PWMFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "communication_pkg/PWMFeedback";
  }

  static const char* value(const ::communication_pkg::PWMFeedback_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::communication_pkg::PWMFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#feedback\n\
uint32 feedback\n\
\n\
\n\
";
  }

  static const char* value(const ::communication_pkg::PWMFeedback_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::communication_pkg::PWMFeedback_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.feedback);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct PWMFeedback_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::communication_pkg::PWMFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::communication_pkg::PWMFeedback_<ContainerAllocator>& v)
  {
    s << indent << "feedback: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.feedback);
  }
};

} // namespace message_operations
} // namespace ros

#endif // COMMUNICATION_PKG_MESSAGE_PWMFEEDBACK_H
