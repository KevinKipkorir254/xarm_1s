#include "xarm_1s_hardware_interface/hardware_interface.hpp"
#include <hardware_interface/types/hardware_interface_type_values.hpp>
#include <pluginlib/class_list_macros.hpp>
#include <iomanip>

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
        //reserve space for position states and commands
        position_states.resize(info_.joints.size(), 0.0);
        position_commands.resize(info_.joints.size(), 0.0);
   

    // Print out all joints and set initial values to zero
    for (const auto& joint : info_.joints)
    {
        //RCLCPP_INFO_STREAM(rclcpp::get_logger("EncodedDcMotorKitHardwareInterface"), "Joint name: " << joint.name);
        if(joint.command_interfaces.size() != 1 || joint.command_interfaces[0].name != hardware_interface::HW_IF_POSITION)
        {
          RCLCPP_FATAL(rclcpp::get_logger("HardwareInterface"),"Joint '%s' has %zu command interfaces found. 1 expected.", joint.name.c_str(), joint.command_interfaces.size());
          return CallbackReturn::ERROR;
        }
        if(joint.state_interfaces.size() != 1 || joint.state_interfaces[0].name != hardware_interface::HW_IF_POSITION)
        {
          RCLCPP_FATAL(rclcpp::get_logger("HardwareInterface"),"Joint '%s' has %zu state interfaces found. 1 expected.", joint.name.c_str(), joint.state_interfaces.size());
          return CallbackReturn::ERROR;
        }
    }

    //initialize components to allow publishing
    //node_ = rclcpp::Node::make_shared("hardware_interface_node");
    //publisher_ = node_->create_publisher<sensor_msgs::msg::JointState>("joint_states", 10);


   try{
        //arm = Controller("hidraw0");
        RCLCPP_INFO_STREAM(rclcpp::get_logger("hardware_interface_node"), "Serial Port initialized successfully.");

      } catch(const std::exception &e)
      {
            RCLCPP_ERROR(rclcpp::get_logger("hardware_interface_node"), "Serial port initialization failed: %s", e.what());
      }


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

    // Initialize the hidapi library
    res = hid_init();
    printf("hid_init result: %d\n", res);

    // Open the device using the VID, PID
    handle = hid_open(0x0483, 0x5750, NULL);
    if (!handle) {
        printf("Unable to open device\n");
        return CallbackReturn::ERROR;
    }

    // Read the Manufacturer String
    res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
    printf("Manufacturer String: %ls\n", wstr);

    // Read the Product String
    res = hid_get_product_string(handle, wstr, MAX_STR);
    printf("Product String: %ls\n", wstr);

    // Read the Serial Number String
    res = hid_get_serial_number_string(handle, wstr, MAX_STR);
    printf("Serial Number String: %ls\n", wstr);

    positions.resize(6, 0);///since we have 6 motors
    

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
  
  for (int servo = 1; servo <= 6; ++servo) {
    
            // Set up the command
            memset(buf, 0, sizeof(buf));
            buf[0] = 0x00;  // Report ID
            buf[1] = SIGNATURE;
            buf[2] = SIGNATURE;
            buf[3] = 0x04;  // data size
            buf[4] = CMD_GET_SERVO_POSITION;
            buf[5] = 0x01;  // Number of servos
            buf[6] = servo; // Servo ID

            // Send the command
            res = hid_write(handle, buf, sizeof(buf));
            if (res < 0) {
                //printf("Error writing to device.\n");
                hid_close(handle);
                hid_exit();
                return hardware_interface::return_type::ERROR;
            }

            // Read the response
            res = hid_read_timeout(handle, buf, sizeof(buf), 100);
            if (res > 0) {
                if (res >= 10 && buf[1] == SIGNATURE && buf[3] == CMD_GET_SERVO_POSITION) {
                    int position = (buf[7] << 8) | buf[6];
                    positions[servo-1] = position;//starts at end effector last one is base motor
                } else {
                    //printf("ERROR ");
                }
            } else if (res == 0) {
                //printf("TIMEOUT ");
            } else {
                //printf("ERROR ");
            }
        }
        
 /*
         //double position_states[6];
         for(int i = 0; i < 5; i++)
         {
            position_states[i] = -1.57 + (positions[5-i] * 3.14)/1000;
         }
         position_states[5] = 0.3 - (positions[0] * 3.14)/1000;
    */

   for(int i = 0; i < 6; i++)
   {
    position_states[i] = position_commands[i];
   }
        // Log calculated position_states
        //RCLCPP_INFO(rclcpp::get_logger("RoboticArmHWInterface"), ".");
    RCLCPP_INFO(rclcpp::get_logger("RoboticArmHWInterface"), "%f, %f, %f, %f, %f, %f", position_commands[0], position_commands[1], position_commands[2], position_commands[3], position_commands[4], position_commands[5]);


  return hardware_interface::return_type::OK;
}

// Send the desired joint position, servoangles
hardware_interface::return_type RoboticArmHWInterface::write(const rclcpp::Time &time,
                                                           const rclcpp::Duration &period)
{
  
      //RCLCPP_INFO(rclcpp::get_logger("RoboticArmHWInterface"), "%f, %f, %f, %f, %f, %f", position_commands[0], position_commands[1], position_commands[2], position_commands[3], position_commands[4], position_commands[5]);
      for(int i = 0; i < 5; i++)
      {
        positions[i] = static_cast<int>((position_commands[i] * 1000 + 1570)/3.14);/// shoulder_pan, shoulder_lift, elbow, wrist_flex, wrist_roll, grip_left
      }

      positions[5] = static_cast<int>((position_commands[5] * 1000 + 300)/3.14);/// grip_left
      //RCLCPP_INFO(rclcpp::get_logger("RoboticArmHWInterface"), "%d, %d, %d, %d, %d, %d", positions[0], positions[1], positions[2], positions[3], positions[4], positions[5]);
     /*
      int duration = 1000;

      for(int i = 0; i < 6; i++)
      {
        //RCLCPP_INFO(rclcpp::get_logger("RoboticArmHWInterface"), "%d", positions[i]);
        std::vector<uint8_t> data = { 1, static_cast<uint8_t>(duration & 0xff), static_cast<uint8_t>((duration & 0xff00) >> 8)};
        data.push_back(static_cast<uint8_t>((6-i)));
        data.push_back(static_cast<uint8_t>(positions[i] & 0xff));
        data.push_back(static_cast<uint8_t>((positions[i] & 0xff00) >> 8));

        std::vector<uint8_t> report_data = {0, SIGNATURE, SIGNATURE, static_cast<uint8_t>(data.size() + 2), CMD_SERVO_MOVE};
        report_data.insert(report_data.end(), data.begin(), data.end());
        hid_write(handle, report_data.data(), report_data.size());
      }
      */
      //std::cout << std::setw(5) << current_positions[servo-1] << " ";

  return hardware_interface::return_type::OK;
}

// Function to convert a byte to a hexadecimal string
std::string byteToHex(unsigned char byte) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(2) << (int)byte; // format byte as two-digit hex
    return oss.str();
}

void RoboticArmHWInterface::send(int cmd, int len = 0)
{
   
}

int RoboticArmHWInterface::recv(int cmd)
{
  std::vector<uint8_t> temp_buffer(4);

  try
  {
        //serial_port_.Read(temp_buffer, 4, 1000);  // 1000 ms timeout

  }catch(const LibSerial::ReadTimeout)
  {
        std::cerr << "Read timeout" << std::endl;
        return -1;
  }
  if(temp_buffer[0] == SIGNATURE && temp_buffer[1] == SIGNATURE && temp_buffer[3] == cmd)
  {
            int len = temp_buffer[2] - 2;  // Get the length
        
        // Read 'len' bytes into _buffer
        std::vector<uint8_t> buffer_recv(len);
        try { 

          //serial_port_.Read(buffer_recv, len, 1000);

        } catch (const LibSerial::ReadTimeout&) {
            std::cerr << "Read timeout for data" << std::endl;
            return -1;
        }
        return len;
  }

  return -1;
}

unsigned RoboticArmHWInterface::clamp(unsigned v, unsigned lo, unsigned hi)
{
   return (v < lo) ? lo : (hi < v) ? hi : v;
}

unsigned RoboticArmHWInterface::clampServoLimits(int servo, unsigned value) 
{
  switch (xMode)
  {
    case xArm:
      return clamp(value, 0, 1000);
    case LeArm:
      if(servo == 1) {
        return clamp(value, 1500, 2500);
      } else {
        return clamp(value, 500, 2500);
      }
    default:
      return value;
  }
}

// Function to get the low byte of a 16-bit integer
uint8_t lowByte(uint16_t val) {
    return val & 0xFF;
}

// Function to get the high byte of a 16-bit integer
uint8_t highByte(uint16_t val) {
    return (val >> 8) & 0xFF;
}


/*** SetPosition ***/
void RoboticArmHWInterface::setPosition(int servo_id, unsigned position, unsigned duration, bool wait)
{
  position = clampServoLimits(servo_id, position);
  _buffer[0] = 1;
  _buffer[1] = lowByte(duration);
  _buffer[2] = highByte(duration);
  _buffer[3] = servo_id;
  _buffer[4] = lowByte(position);
  _buffer[5] = highByte(position);
  send(CMD_SERVO_MOVE, 6);
  if (wait) 
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
  }
}


void RoboticArmHWInterface::setPosition(xArmServo servo, unsigned duration, bool wait)
{
  setPosition( servo.servo_id, servo.position, duration, wait);
}


void RoboticArmHWInterface::setPosition(xArmServo servos[], int count, unsigned duration, bool wait)
{

  int len = count * 3 + 3;
  _buffer[0] = count;
  _buffer[1] = lowByte(duration);
  _buffer[2] = highByte(duration);
  for (int i = 3, j = 0; j < count; i += 3, j++) {
    _buffer[i] = servos[j].servo_id;
    _buffer[i + 1] = lowByte(servos[j].position);
    _buffer[i + 2] = highByte(servos[j].position);
  }

  send(CMD_SERVO_MOVE, len);

  if (wait) 
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
  }
}

/*** GetPosition ***/

int RoboticArmHWInterface::getPosition(int servo_id)
{
  _buffer[0] = 1;
  _buffer[1] = servo_id;
  send(CMD_GET_SERVO_POSITION, 2);
  if (-1 != recv(CMD_GET_SERVO_POSITION)) {
    return _buffer[3] * 256 + _buffer[2];
  }
  return -1;
}

int RoboticArmHWInterface::getPosition(xArmServo &servo)
{
  int pos = getPosition(servo.servo_id);
  servo.position = pos;
  return pos;
}

bool RoboticArmHWInterface::getPosition(xArmServo servos[], int count)
{
  _buffer[0] = count;
  for (int i = 1, j = 0; j < count; i++, j++) {
    _buffer[i] = servos[j].servo_id;
  }
  send(CMD_GET_SERVO_POSITION, count + 1);
  // servo positions returned are in the same order sent.
  if (-1 != recv(CMD_GET_SERVO_POSITION)) {
    for (int i = 2, j = 0; j < count; i += 3, j++) {
      servos[j].position = _buffer[i + 1] * 256 + _buffer[i];
    }
    return true;
  }
  return false;
}

/*** Off ***/

void RoboticArmHWInterface::servoOff(int servo_id)
{
  _buffer[0] = 1;
  _buffer[1] = servo_id;
  send(CMD_SERVO_STOP, 2);
}

void RoboticArmHWInterface::servoOff(int num, int servo_id, ...)
{
  _buffer[0] = num;
  _buffer[1] = servo_id;  
  if (num > 1) {
    va_list args;
    va_start(args, servo_id);
    for (int i = 2; i <= num; i++) 
    {
      _buffer[i] = (uint8_t)va_arg(args, int);
    }
    va_end(args);    
  }
  send(CMD_SERVO_STOP, num + 1);
}

void RoboticArmHWInterface::servoOff(xArmServo servo)
{
  servoOff(servo.servo_id);
}

void RoboticArmHWInterface::servoOff(xArmServo servos[], int count)
{
  _buffer[0] = count;
  for (int i = 1, j = 0; j < count; i++, j++) {
    _buffer[i] = servos[j].servo_id;
  }
  send(CMD_SERVO_STOP, count + 1);
}

void RoboticArmHWInterface::servoOff()
{
  _buffer[0] = 6;
  _buffer[1] = 1;
  _buffer[2] = 2;
  _buffer[3] = 3;
  _buffer[4] = 4;
  _buffer[5] = 5;
  _buffer[6] = 6;
  send(CMD_SERVO_STOP, 7);
}

/*** Action Group ***/

  void RoboticArmHWInterface::actionRun(int group, unsigned times) {
    _buffer[0] = group;
    _buffer[1] = lowByte(times);
    _buffer[2] = highByte(times);
    send(CMD_ACTION_GROUP_RUN, 3);
    actionRunning = true;
  }

  void RoboticArmHWInterface::actionStop() {
    send(CMD_ACTION_GROUP_STOP, 0);
  }

  void RoboticArmHWInterface::actionSpeed(int group, unsigned percent) {
    _buffer[0] = group;
    _buffer[1] = lowByte(percent);
    _buffer[2] = highByte(percent);
    bool _actionRunning = actionRunning;
    send(CMD_ACTION_GROUP_SPEED, 3);
    actionRunning = _actionRunning;
  }

  bool RoboticArmHWInterface::actionIsRunning() {
    return actionRunning;
  }

  bool RoboticArmHWInterface::serialEvent() {
    if (actionRunning) {
   
        
        std::vector<uint8_t> buffer_recv(4);
        //Serila.Read(buffer_recv, 4, 1000);
        if (buffer_recv[0] == SIGNATURE && buffer_recv[1] == SIGNATURE) {
          switch (buffer_recv[3])
          {
          case CMD_ACTION_GROUP_STOP:
          case CMD_ACTION_GROUP_END:
            actionRunning = false;
            return true;
          default:
            break;
          }
        }
      
    }
    return false;
  }

/*** GetBatteryVoltage ***/

int RoboticArmHWInterface::getBatteryVoltage()
{
  send(CMD_GET_BATTERY_VOLTAGE);
  if (-1 != recv(CMD_GET_BATTERY_VOLTAGE)) {
    return _buffer[1] * 256 + _buffer[0];
  }
  return -1;
}

void RoboticArmHWInterface::beep() {
  //serial_port_.WriteByte((uint8_t)CMD_BEEP);
}

}  // namespace robotic_arm_hwinterface

PLUGINLIB_EXPORT_CLASS( robotic_arm_controllers::RoboticArmHWInterface, hardware_interface::SystemInterface)