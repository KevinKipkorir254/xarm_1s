cmake_minimum_required(VERSION 3.8)
project(xarm_1s_joy)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(xarm_1s_messages REQUIRED)
pkg_check_modules(HIDAPI REQUIRED hidapi-libusb)

if(NOT HIDAPI_FOUND)
  # Fallback to manual search if pkg-config fails
  find_path(HIDAPI_INCLUDE_DIRS NAMES hidapi.h PATH_SUFFIXES hidapi)
  find_library(HIDAPI_LIBRARIES NAMES hidapi-libusb)

  if(NOT HIDAPI_INCLUDE_DIRS OR NOT HIDAPI_LIBRARIES)
    message(FATAL_ERROR "hidapi not found. Please install libhidapi-dev.")
  endif()
endif()

# Add executable
add_executable(game_pad src/game_pad.cpp)

# Include directories
target_include_directories(game_pad PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${HIDAPI_INCLUDE_DIRS}
)

# Link libraries and add dependencies
target_link_libraries(game_pad
  ${HIDAPI_LIBRARIES}
  ${rclcpp_LIBRARIES}
  ${std_msgs_LIBRARIES}
  ${xarm_1s_messages_LIBRARIES}
)

# Ensure ROS 2 packages are found
ament_target_dependencies(game_pad
  "rclcpp"
  "std_msgs"
  "xarm_1s_messages"
)

# Install targets
install(TARGETS game_pad
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()