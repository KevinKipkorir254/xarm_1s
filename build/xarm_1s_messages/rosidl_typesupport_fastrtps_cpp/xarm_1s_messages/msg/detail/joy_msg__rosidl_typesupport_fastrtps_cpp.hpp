// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from xarm_1s_messages:msg/JoyMsg.idl
// generated code does not contain a copyright notice

#ifndef XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "xarm_1s_messages/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "xarm_1s_messages/msg/detail/joy_msg__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace xarm_1s_messages
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_xarm_1s_messages
cdr_serialize(
  const xarm_1s_messages::msg::JoyMsg & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_xarm_1s_messages
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  xarm_1s_messages::msg::JoyMsg & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_xarm_1s_messages
get_serialized_size(
  const xarm_1s_messages::msg::JoyMsg & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_xarm_1s_messages
max_serialized_size_JoyMsg(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace xarm_1s_messages

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_xarm_1s_messages
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, xarm_1s_messages, msg, JoyMsg)();

#ifdef __cplusplus
}
#endif

#endif  // XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
