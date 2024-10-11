// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from xarm_1s_messages:msg/JoyMsg.idl
// generated code does not contain a copyright notice

#ifndef XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__STRUCT_HPP_
#define XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__xarm_1s_messages__msg__JoyMsg __attribute__((deprecated))
#else
# define DEPRECATED__xarm_1s_messages__msg__JoyMsg __declspec(deprecated)
#endif

namespace xarm_1s_messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct JoyMsg_
{
  using Type = JoyMsg_<ContainerAllocator>;

  explicit JoyMsg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->xslider = 0ll;
      this->yslider = 0ll;
      this->zslider = 0ll;
      this->rollslider = 0ll;
    }
  }

  explicit JoyMsg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->xslider = 0ll;
      this->yslider = 0ll;
      this->zslider = 0ll;
      this->rollslider = 0ll;
    }
  }

  // field types and members
  using _xslider_type =
    int64_t;
  _xslider_type xslider;
  using _yslider_type =
    int64_t;
  _yslider_type yslider;
  using _zslider_type =
    int64_t;
  _zslider_type zslider;
  using _rollslider_type =
    int64_t;
  _rollslider_type rollslider;

  // setters for named parameter idiom
  Type & set__xslider(
    const int64_t & _arg)
  {
    this->xslider = _arg;
    return *this;
  }
  Type & set__yslider(
    const int64_t & _arg)
  {
    this->yslider = _arg;
    return *this;
  }
  Type & set__zslider(
    const int64_t & _arg)
  {
    this->zslider = _arg;
    return *this;
  }
  Type & set__rollslider(
    const int64_t & _arg)
  {
    this->rollslider = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    xarm_1s_messages::msg::JoyMsg_<ContainerAllocator> *;
  using ConstRawPtr =
    const xarm_1s_messages::msg::JoyMsg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<xarm_1s_messages::msg::JoyMsg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<xarm_1s_messages::msg::JoyMsg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      xarm_1s_messages::msg::JoyMsg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<xarm_1s_messages::msg::JoyMsg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      xarm_1s_messages::msg::JoyMsg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<xarm_1s_messages::msg::JoyMsg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<xarm_1s_messages::msg::JoyMsg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<xarm_1s_messages::msg::JoyMsg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__xarm_1s_messages__msg__JoyMsg
    std::shared_ptr<xarm_1s_messages::msg::JoyMsg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__xarm_1s_messages__msg__JoyMsg
    std::shared_ptr<xarm_1s_messages::msg::JoyMsg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const JoyMsg_ & other) const
  {
    if (this->xslider != other.xslider) {
      return false;
    }
    if (this->yslider != other.yslider) {
      return false;
    }
    if (this->zslider != other.zslider) {
      return false;
    }
    if (this->rollslider != other.rollslider) {
      return false;
    }
    return true;
  }
  bool operator!=(const JoyMsg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct JoyMsg_

// alias to use template instance with default allocator
using JoyMsg =
  xarm_1s_messages::msg::JoyMsg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace xarm_1s_messages

#endif  // XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__STRUCT_HPP_
