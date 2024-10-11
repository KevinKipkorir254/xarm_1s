// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from xarm_1s_messages:msg/JoyMsg.idl
// generated code does not contain a copyright notice

#ifndef XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__TRAITS_HPP_
#define XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "xarm_1s_messages/msg/detail/joy_msg__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace xarm_1s_messages
{

namespace msg
{

inline void to_flow_style_yaml(
  const JoyMsg & msg,
  std::ostream & out)
{
  out << "{";
  // member: xslider
  {
    out << "xslider: ";
    rosidl_generator_traits::value_to_yaml(msg.xslider, out);
    out << ", ";
  }

  // member: yslider
  {
    out << "yslider: ";
    rosidl_generator_traits::value_to_yaml(msg.yslider, out);
    out << ", ";
  }

  // member: zslider
  {
    out << "zslider: ";
    rosidl_generator_traits::value_to_yaml(msg.zslider, out);
    out << ", ";
  }

  // member: rollslider
  {
    out << "rollslider: ";
    rosidl_generator_traits::value_to_yaml(msg.rollslider, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const JoyMsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: xslider
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "xslider: ";
    rosidl_generator_traits::value_to_yaml(msg.xslider, out);
    out << "\n";
  }

  // member: yslider
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yslider: ";
    rosidl_generator_traits::value_to_yaml(msg.yslider, out);
    out << "\n";
  }

  // member: zslider
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "zslider: ";
    rosidl_generator_traits::value_to_yaml(msg.zslider, out);
    out << "\n";
  }

  // member: rollslider
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rollslider: ";
    rosidl_generator_traits::value_to_yaml(msg.rollslider, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const JoyMsg & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace xarm_1s_messages

namespace rosidl_generator_traits
{

[[deprecated("use xarm_1s_messages::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const xarm_1s_messages::msg::JoyMsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  xarm_1s_messages::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use xarm_1s_messages::msg::to_yaml() instead")]]
inline std::string to_yaml(const xarm_1s_messages::msg::JoyMsg & msg)
{
  return xarm_1s_messages::msg::to_yaml(msg);
}

template<>
inline const char * data_type<xarm_1s_messages::msg::JoyMsg>()
{
  return "xarm_1s_messages::msg::JoyMsg";
}

template<>
inline const char * name<xarm_1s_messages::msg::JoyMsg>()
{
  return "xarm_1s_messages/msg/JoyMsg";
}

template<>
struct has_fixed_size<xarm_1s_messages::msg::JoyMsg>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<xarm_1s_messages::msg::JoyMsg>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<xarm_1s_messages::msg::JoyMsg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__TRAITS_HPP_
