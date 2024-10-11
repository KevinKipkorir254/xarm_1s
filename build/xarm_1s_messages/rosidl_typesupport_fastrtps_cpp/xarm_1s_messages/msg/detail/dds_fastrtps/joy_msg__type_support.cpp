// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from xarm_1s_messages:msg/JoyMsg.idl
// generated code does not contain a copyright notice
#include "xarm_1s_messages/msg/detail/joy_msg__rosidl_typesupport_fastrtps_cpp.hpp"
#include "xarm_1s_messages/msg/detail/joy_msg__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

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
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: xslider
  cdr << ros_message.xslider;
  // Member: yslider
  cdr << ros_message.yslider;
  // Member: zslider
  cdr << ros_message.zslider;
  // Member: rollslider
  cdr << ros_message.rollslider;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_xarm_1s_messages
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  xarm_1s_messages::msg::JoyMsg & ros_message)
{
  // Member: xslider
  cdr >> ros_message.xslider;

  // Member: yslider
  cdr >> ros_message.yslider;

  // Member: zslider
  cdr >> ros_message.zslider;

  // Member: rollslider
  cdr >> ros_message.rollslider;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_xarm_1s_messages
get_serialized_size(
  const xarm_1s_messages::msg::JoyMsg & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: xslider
  {
    size_t item_size = sizeof(ros_message.xslider);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: yslider
  {
    size_t item_size = sizeof(ros_message.yslider);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: zslider
  {
    size_t item_size = sizeof(ros_message.zslider);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: rollslider
  {
    size_t item_size = sizeof(ros_message.rollslider);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_xarm_1s_messages
max_serialized_size_JoyMsg(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: xslider
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: yslider
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: zslider
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: rollslider
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = xarm_1s_messages::msg::JoyMsg;
    is_plain =
      (
      offsetof(DataType, rollslider) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _JoyMsg__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const xarm_1s_messages::msg::JoyMsg *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _JoyMsg__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<xarm_1s_messages::msg::JoyMsg *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _JoyMsg__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const xarm_1s_messages::msg::JoyMsg *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _JoyMsg__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_JoyMsg(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _JoyMsg__callbacks = {
  "xarm_1s_messages::msg",
  "JoyMsg",
  _JoyMsg__cdr_serialize,
  _JoyMsg__cdr_deserialize,
  _JoyMsg__get_serialized_size,
  _JoyMsg__max_serialized_size
};

static rosidl_message_type_support_t _JoyMsg__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_JoyMsg__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace xarm_1s_messages

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_xarm_1s_messages
const rosidl_message_type_support_t *
get_message_type_support_handle<xarm_1s_messages::msg::JoyMsg>()
{
  return &xarm_1s_messages::msg::typesupport_fastrtps_cpp::_JoyMsg__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, xarm_1s_messages, msg, JoyMsg)() {
  return &xarm_1s_messages::msg::typesupport_fastrtps_cpp::_JoyMsg__handle;
}

#ifdef __cplusplus
}
#endif
