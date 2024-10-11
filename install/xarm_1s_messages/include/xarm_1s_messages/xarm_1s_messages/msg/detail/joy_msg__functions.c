// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from xarm_1s_messages:msg/JoyMsg.idl
// generated code does not contain a copyright notice
#include "xarm_1s_messages/msg/detail/joy_msg__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
xarm_1s_messages__msg__JoyMsg__init(xarm_1s_messages__msg__JoyMsg * msg)
{
  if (!msg) {
    return false;
  }
  // xslider
  // yslider
  // zslider
  // rollslider
  return true;
}

void
xarm_1s_messages__msg__JoyMsg__fini(xarm_1s_messages__msg__JoyMsg * msg)
{
  if (!msg) {
    return;
  }
  // xslider
  // yslider
  // zslider
  // rollslider
}

bool
xarm_1s_messages__msg__JoyMsg__are_equal(const xarm_1s_messages__msg__JoyMsg * lhs, const xarm_1s_messages__msg__JoyMsg * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // xslider
  if (lhs->xslider != rhs->xslider) {
    return false;
  }
  // yslider
  if (lhs->yslider != rhs->yslider) {
    return false;
  }
  // zslider
  if (lhs->zslider != rhs->zslider) {
    return false;
  }
  // rollslider
  if (lhs->rollslider != rhs->rollslider) {
    return false;
  }
  return true;
}

bool
xarm_1s_messages__msg__JoyMsg__copy(
  const xarm_1s_messages__msg__JoyMsg * input,
  xarm_1s_messages__msg__JoyMsg * output)
{
  if (!input || !output) {
    return false;
  }
  // xslider
  output->xslider = input->xslider;
  // yslider
  output->yslider = input->yslider;
  // zslider
  output->zslider = input->zslider;
  // rollslider
  output->rollslider = input->rollslider;
  return true;
}

xarm_1s_messages__msg__JoyMsg *
xarm_1s_messages__msg__JoyMsg__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  xarm_1s_messages__msg__JoyMsg * msg = (xarm_1s_messages__msg__JoyMsg *)allocator.allocate(sizeof(xarm_1s_messages__msg__JoyMsg), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(xarm_1s_messages__msg__JoyMsg));
  bool success = xarm_1s_messages__msg__JoyMsg__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
xarm_1s_messages__msg__JoyMsg__destroy(xarm_1s_messages__msg__JoyMsg * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    xarm_1s_messages__msg__JoyMsg__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
xarm_1s_messages__msg__JoyMsg__Sequence__init(xarm_1s_messages__msg__JoyMsg__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  xarm_1s_messages__msg__JoyMsg * data = NULL;

  if (size) {
    data = (xarm_1s_messages__msg__JoyMsg *)allocator.zero_allocate(size, sizeof(xarm_1s_messages__msg__JoyMsg), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = xarm_1s_messages__msg__JoyMsg__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        xarm_1s_messages__msg__JoyMsg__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
xarm_1s_messages__msg__JoyMsg__Sequence__fini(xarm_1s_messages__msg__JoyMsg__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      xarm_1s_messages__msg__JoyMsg__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

xarm_1s_messages__msg__JoyMsg__Sequence *
xarm_1s_messages__msg__JoyMsg__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  xarm_1s_messages__msg__JoyMsg__Sequence * array = (xarm_1s_messages__msg__JoyMsg__Sequence *)allocator.allocate(sizeof(xarm_1s_messages__msg__JoyMsg__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = xarm_1s_messages__msg__JoyMsg__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
xarm_1s_messages__msg__JoyMsg__Sequence__destroy(xarm_1s_messages__msg__JoyMsg__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    xarm_1s_messages__msg__JoyMsg__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
xarm_1s_messages__msg__JoyMsg__Sequence__are_equal(const xarm_1s_messages__msg__JoyMsg__Sequence * lhs, const xarm_1s_messages__msg__JoyMsg__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!xarm_1s_messages__msg__JoyMsg__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
xarm_1s_messages__msg__JoyMsg__Sequence__copy(
  const xarm_1s_messages__msg__JoyMsg__Sequence * input,
  xarm_1s_messages__msg__JoyMsg__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(xarm_1s_messages__msg__JoyMsg);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    xarm_1s_messages__msg__JoyMsg * data =
      (xarm_1s_messages__msg__JoyMsg *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!xarm_1s_messages__msg__JoyMsg__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          xarm_1s_messages__msg__JoyMsg__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!xarm_1s_messages__msg__JoyMsg__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
