// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from xarm_1s_messages:msg/JoyMsg.idl
// generated code does not contain a copyright notice

#ifndef XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__STRUCT_H_
#define XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/JoyMsg in the package xarm_1s_messages.
typedef struct xarm_1s_messages__msg__JoyMsg
{
  int64_t xslider;
  int64_t yslider;
  int64_t zslider;
  int64_t rollslider;
} xarm_1s_messages__msg__JoyMsg;

// Struct for a sequence of xarm_1s_messages__msg__JoyMsg.
typedef struct xarm_1s_messages__msg__JoyMsg__Sequence
{
  xarm_1s_messages__msg__JoyMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} xarm_1s_messages__msg__JoyMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // XARM_1S_MESSAGES__MSG__DETAIL__JOY_MSG__STRUCT_H_
