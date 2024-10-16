// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from xarm_1s_messages:msg/JoyMsg.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "xarm_1s_messages/msg/detail/joy_msg__struct.h"
#include "xarm_1s_messages/msg/detail/joy_msg__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool xarm_1s_messages__msg__joy_msg__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[37];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("xarm_1s_messages.msg._joy_msg.JoyMsg", full_classname_dest, 36) == 0);
  }
  xarm_1s_messages__msg__JoyMsg * ros_message = _ros_message;
  {  // xslider
    PyObject * field = PyObject_GetAttrString(_pymsg, "xslider");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->xslider = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // yslider
    PyObject * field = PyObject_GetAttrString(_pymsg, "yslider");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->yslider = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // zslider
    PyObject * field = PyObject_GetAttrString(_pymsg, "zslider");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->zslider = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // rollslider
    PyObject * field = PyObject_GetAttrString(_pymsg, "rollslider");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->rollslider = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * xarm_1s_messages__msg__joy_msg__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of JoyMsg */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("xarm_1s_messages.msg._joy_msg");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "JoyMsg");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  xarm_1s_messages__msg__JoyMsg * ros_message = (xarm_1s_messages__msg__JoyMsg *)raw_ros_message;
  {  // xslider
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->xslider);
    {
      int rc = PyObject_SetAttrString(_pymessage, "xslider", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // yslider
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->yslider);
    {
      int rc = PyObject_SetAttrString(_pymessage, "yslider", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // zslider
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->zslider);
    {
      int rc = PyObject_SetAttrString(_pymessage, "zslider", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rollslider
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->rollslider);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rollslider", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
