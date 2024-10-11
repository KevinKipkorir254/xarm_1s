// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from xarm_1s_messages:msg/JoyMsg.idl
// generated code does not contain a copyright notice

#ifndef XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__BUILDER_HPP_
#define XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "xarm_1s_messages/msg/detail/joy_msg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace xarm_1s_messages
{

namespace msg
{

namespace builder
{

class Init_JoyMsg_rollslider
{
public:
  explicit Init_JoyMsg_rollslider(::xarm_1s_messages::msg::JoyMsg & msg)
  : msg_(msg)
  {}
  ::xarm_1s_messages::msg::JoyMsg rollslider(::xarm_1s_messages::msg::JoyMsg::_rollslider_type arg)
  {
    msg_.rollslider = std::move(arg);
    return std::move(msg_);
  }

private:
  ::xarm_1s_messages::msg::JoyMsg msg_;
};

class Init_JoyMsg_zslider
{
public:
  explicit Init_JoyMsg_zslider(::xarm_1s_messages::msg::JoyMsg & msg)
  : msg_(msg)
  {}
  Init_JoyMsg_rollslider zslider(::xarm_1s_messages::msg::JoyMsg::_zslider_type arg)
  {
    msg_.zslider = std::move(arg);
    return Init_JoyMsg_rollslider(msg_);
  }

private:
  ::xarm_1s_messages::msg::JoyMsg msg_;
};

class Init_JoyMsg_yslider
{
public:
  explicit Init_JoyMsg_yslider(::xarm_1s_messages::msg::JoyMsg & msg)
  : msg_(msg)
  {}
  Init_JoyMsg_zslider yslider(::xarm_1s_messages::msg::JoyMsg::_yslider_type arg)
  {
    msg_.yslider = std::move(arg);
    return Init_JoyMsg_zslider(msg_);
  }

private:
  ::xarm_1s_messages::msg::JoyMsg msg_;
};

class Init_JoyMsg_xslider
{
public:
  Init_JoyMsg_xslider()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JoyMsg_yslider xslider(::xarm_1s_messages::msg::JoyMsg::_xslider_type arg)
  {
    msg_.xslider = std::move(arg);
    return Init_JoyMsg_yslider(msg_);
  }

private:
  ::xarm_1s_messages::msg::JoyMsg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::xarm_1s_messages::msg::JoyMsg>()
{
  return xarm_1s_messages::msg::builder::Init_JoyMsg_xslider();
}

}  // namespace xarm_1s_messages

#endif  // XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__BUILDER_HPP_
