// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from xarm_1s_messages:msg/JoyMsg.idl
// generated code does not contain a copyright notice
#include "xarm_1s_messages/msg/detail/joy_msg__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "xarm_1s_messages/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "xarm_1s_messages/msg/detail/joy_msg__struct.h"
#include "xarm_1s_messages/msg/detail/joy_msg__functions.h"
#include "fastcdr/Cdr.h"

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

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _JoyMsg__ros_msg_type = xarm_1s_messages__msg__JoyMsg;

static bool _JoyMsg__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _JoyMsg__ros_msg_type * ros_message = static_cast<const _JoyMsg__ros_msg_type *>(untyped_ros_message);
  // Field name: xslider
  {
    cdr << ros_message->xslider;
  }

  // Field name: yslider
  {
    cdr << ros_message->yslider;
  }

  // Field name: zslider
  {
    cdr << ros_message->zslider;
  }

  // Field name: rollslider
  {
    cdr << ros_message->rollslider;
  }

  return true;
}

static bool _JoyMsg__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _JoyMsg__ros_msg_type * ros_message = static_cast<_JoyMsg__ros_msg_type *>(untyped_ros_message);
  // Field name: xslider
  {
    cdr >> ros_message->xslider;
  }

  // Field name: yslider
  {
    cdr >> ros_message->yslider;
  }

  // Field name: zslider
  {
    cdr >> ros_message->zslider;
  }

  // Field name: rollslider
  {
    cdr >> ros_message->rollslider;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_xarm_1s_messages
size_t get_serialized_size_xarm_1s_messages__msg__JoyMsg(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _JoyMsg__ros_msg_type * ros_message = static_cast<const _JoyMsg__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name xslider
  {
    size_t item_size = sizeof(ros_message->xslider);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name yslider
  {
    size_t item_size = sizeof(ros_message->yslider);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name zslider
  {
    size_t item_size = sizeof(ros_message->zslider);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name rollslider
  {
    size_t item_size = sizeof(ros_message->rollslider);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _JoyMsg__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_xarm_1s_messages__msg__JoyMsg(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_xarm_1s_messages
size_t max_serialized_size_xarm_1s_messages__msg__JoyMsg(
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

  // member: xslider
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: yslider
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: zslider
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: rollslider
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
    using DataType = xarm_1s_messages__msg__JoyMsg;
    is_plain =
      (
      offsetof(DataType, rollslider) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _JoyMsg__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_xarm_1s_messages__msg__JoyMsg(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_JoyMsg = {
  "xarm_1s_messages::msg",
  "JoyMsg",
  _JoyMsg__cdr_serialize,
  _JoyMsg__cdr_deserialize,
  _JoyMsg__get_serialized_size,
  _JoyMsg__max_serialized_size
};

static rosidl_message_type_support_t _JoyMsg__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_JoyMsg,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, xarm_1s_messages, msg, JoyMsg)() {
  return &_JoyMsg__type_support;
}

#if defined(__cplusplus)
}
#endif
