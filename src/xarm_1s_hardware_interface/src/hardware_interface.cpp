#include "xarm_1s_hardware_interface/hardware_interface.hpp"
#include <hardware_interface/types/hardware_interface_type_values.hpp>
#include <pluginlib/class_list_macros.hpp>


namespace robotic_arm_controllers
{
RoboticArmHWInterface::RoboticArmHWInterface()
{
  RCLCPP_INFO(rclcpp::get_logger("EncodedDcMotorKitHardwareInterface"), "In constructor...............");
}


RoboticArmHWInterface::~RoboticArmHWInterface()
{

}


CallbackReturn RoboticArmHWInterface::on_init(const hardware_interface::HardwareInfo &hardware_info)
{
  RCLCPP_INFO(rclcpp::get_logger("EncodedDcMotorKitHardwareInterface"), "In on init...............");
      // Initialize your hardware interface here
  CallbackReturn result = hardware_interface::SystemInterface::on_init(hardware_info);
  if (result != CallbackReturn::SUCCESS)
  {
    return result;
  }

    // Print out all joints and set initial values to zero
    for (const auto& joint : info_.joints)
    {
        RCLCPP_INFO_STREAM(rclcpp::get_logger("EncodedDcMotorKitHardwareInterface"), "Joint name: " << joint.name);
    }

    //reserve space for position states and commands
    position_states.resize(info_.joints.size(), 0.0);
    position_commands.resize(info_.joints.size(), 0.0);

    //initialize components to allow publishing
    node_ = rclcpp::Node::make_shared("hardware_interface_node");
    publisher_ = node_->create_publisher<sensor_msgs::msg::JointState>("joint_states", 10);


  return CallbackReturn::SUCCESS;
}


std::vector<hardware_interface::StateInterface> RoboticArmHWInterface::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;

  // Provide only a position Interafce
  for (size_t i = 0; i < info_.joints.size(); i++)
  {
    state_interfaces.emplace_back(hardware_interface::StateInterface(info_.joints[i].name, hardware_interface::HW_IF_POSITION, &position_states[i]));
  }

  return state_interfaces;
}


std::vector<hardware_interface::CommandInterface> RoboticArmHWInterface::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;

  // Provide only a position Interafce
  for (size_t i = 0; i < info_.joints.size(); i++)
  {
    command_interfaces.emplace_back(hardware_interface::CommandInterface(info_.joints[i].name, hardware_interface::HW_IF_POSITION, &position_commands[i]));
  }

  return command_interfaces;
}


CallbackReturn RoboticArmHWInterface::on_activate(const rclcpp_lifecycle::State &previous_state)
{
  RCLCPP_INFO(rclcpp::get_logger("EncodedDcMotorKitHardwareInterface"), "Starting robot hardware ...");


  return CallbackReturn::SUCCESS;
}


CallbackReturn RoboticArmHWInterface::on_deactivate(const rclcpp_lifecycle::State &previous_state)
{

  return CallbackReturn::SUCCESS;
}

// Read the current states of the motors, servo angles, and send them to ros2
// Due to the limitation of our H/W openloop control is used, we assume the servo reach the desired positions
hardware_interface::return_type RoboticArmHWInterface::read(const rclcpp::Time &time,
                                                          const rclcpp::Duration &period)
{

  auto msg = sensor_msgs::msg::JointState();
  msg.header.stamp = node_->get_clock()->now();
  msg.name = {"shoulder_pan", "shoulder_lift", "elbow", "wrist_flex", "wrist_roll", "grip_left"};
  msg.position = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  publisher_->publish(msg);


  return hardware_interface::return_type::OK;
}

// Send the desired joint position, servoangles
hardware_interface::return_type RoboticArmHWInterface::write(const rclcpp::Time &time,
                                                           const rclcpp::Duration &period)
{

  return hardware_interface::return_type::OK;
}

}  // namespace robotic_arm_hwinterface

PLUGINLIB_EXPORT_CLASS( robotic_arm_controllers::RoboticArmHWInterface, hardware_interface::SystemInterface)