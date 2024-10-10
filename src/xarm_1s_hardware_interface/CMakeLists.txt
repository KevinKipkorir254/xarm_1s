cmake_minimum_required(VERSION 3.8)
project(xarm_1s_hardware_interface)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(SERIAL libserial)

# Manually specify hidapi paths
set(HIDAPI_INCLUDE_DIR "/usr/include")
set(HIDAPI_LIBRARY "/usr/lib/x86_64-linux-gnu/libhidapi-libusb.so")

# Find hidapi manually
find_path(HIDAPI_INCLUDE_DIR NAMES hidapi.h PATH_SUFFIXES hidapi)
find_library(HIDAPI_LIBRARY NAMES hidapi-libusb)

if(NOT HIDAPI_INCLUDE_DIR OR NOT HIDAPI_LIBRARY)
    message(FATAL_ERROR "hidapi not found. Please install libhidapi-dev.")
endif()


# Add hidapi to your include directories
include_directories(
  include
  ${HIDAPI_INCLUDE_DIR}
)

add_library(
  ${PROJECT_NAME} SHARED
  src/hardware_interface.cpp
  src/servo.cpp
  src/util.cpp
  src/xarm.cpp
)

target_include_directories(
  ${PROJECT_NAME} PRIVATE
  include
  "${SERIAL_INCLUDE_DIRS}"
  ${HIDAPI_INCLUDE_DIR}
)

target_link_libraries(
  ${PROJECT_NAME}
  "${SERIAL_LDFLAGS}"
  ${HIDAPI_LIBRARY}
)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp_lifecycle
  rclcpp
  pluginlib
  hardware_interface
)

pluginlib_export_plugin_description_file(hardware_interface robotic_arm_hw_plugin.xml)

ament_python_install_package(${PROJECT_NAME})

install(
  TARGETS ${PROJECT_NAME}
  DESTINATION lib
)

install(
  DIRECTORY include
  DESTINATION include
)

install(
  DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

# install(PROGRAMS
#   ${PROJECT_NAME}/slider_control.py
#   DESTINATION lib/${PROJECT_NAME}
# )

ament_export_include_directories(
  include()
)

ament_export_libraries(
  ${PROJECT_NAME}
)

ament_export_dependencies(
  rclcpp_lifecycle
  rclcpp
  pluginlib
  hardware_interface 
  hidapi
)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
