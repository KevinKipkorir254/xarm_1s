#ifndef ROBOTIC_ARM_HWINTERFACE_HPP
#define ROBOTIC_ARM_HWINTERFACE_HPP

#include <rclcpp/rclcpp.hpp>
#include <hardware_interface/system_interface.hpp>
#include <rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp>
#include <rclcpp_lifecycle/state.hpp>
#include <libserial/SerialPort.h>
#include "sensor_msgs/msg/joint_state.hpp"
//#include "xarm_1s_hardware_interface/xarm.hpp"
#include "hidapi/hidapi.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <iomanip>


#include <vector>
#include <string>

#define SIGNATURE               0x55
#define CMD_BEEP                0x00
#define CMD_SERVO_MOVE          0x03
#define CMD_ACTION_GROUP_RUN    0x06
#define CMD_ACTION_GROUP_STOP   0x07
#define CMD_ACTION_GROUP_END    0x08
#define CMD_ACTION_GROUP_SPEED  0x0B
#define CMD_GET_BATTERY_VOLTAGE 0x0f
#define CMD_SERVO_STOP          0x14
#define CMD_GET_SERVO_POSITION  0x15


#define MAX_STR 255
#define REPORT_SIZE 65

namespace robotic_arm_controllers
{
    using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

    class RoboticArmHWInterface : public hardware_interface::SystemInterface
    {
        public:

            struct xArmServo {
                        int servo_id;
                        unsigned position;
                    };
            RoboticArmHWInterface();
            int i = 0;

            // Destructor
            virtual ~RoboticArmHWInterface();

           
            // Implementing rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface
            virtual CallbackReturn on_activate(const rclcpp_lifecycle::State &previous_state) override;
            virtual CallbackReturn on_deactivate(const rclcpp_lifecycle::State &previous_state) override;

            // Implementing hardware_interface::SystemInterface
            virtual CallbackReturn on_init(const hardware_interface::HardwareInfo &hardware_info) override;
            virtual std::vector<hardware_interface::StateInterface> export_state_interfaces() override;
            virtual std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;
            virtual hardware_interface::return_type read(const rclcpp::Time & time, const rclcpp::Duration & period) override;
            virtual hardware_interface::return_type write(const rclcpp::Time & time, const rclcpp::Duration & period) override;

            //Communicating with the bot.
            std::string byteToHex(unsigned char byte) ;
            void setPosition(int servo_id, unsigned position, unsigned duration = 1000, bool wait = false);
            void setPosition(xArmServo servo, unsigned duration = 1000, bool wait = false);
            void setPosition(xArmServo servos[], int count, unsigned duration = 1000, bool wait = false);

            int getPosition(int servo_id);
            int getPosition(xArmServo &servo);
            bool getPosition(xArmServo servos[], int count);
            
            void servoOff(int servo_id);
            void servoOff(int num, int servo_id, ...);
            void servoOff(xArmServo servo);
            void servoOff(xArmServo servos[], int count);
            void servoOff();

            void actionRun(int group, unsigned times = 1);
            void actionStop();
            void actionSpeed(int group, unsigned percent);
            bool actionIsRunning();
            bool serialEvent();

            int getBatteryVoltage();
            
            void beep();


        private:
            rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr publisher_;
            LibSerial::SerialPort serial_port_;
            rclcpp::Node::SharedPtr node_;
            std::string port_;

            std::vector<double> joint_positions;

            std::vector<double> position_commands;
            std::vector<double> position_states;
            
            enum xArmMode : int {xArm, LeArm};
            

            //std::vector<uint8_t> buffer(_buffer.data(), _buffer.data() + len);
            uint8_t _buffer[32];
            xArmMode xMode;
            bool actionRunning;
    
            unsigned clamp(unsigned v, unsigned lo, unsigned hi);
            unsigned clampServoLimits(int servo, unsigned value);
            void send(int cmd, int len);
            int recv(int cmd);


            //sending and receiving data stuff
            
            int res;
            unsigned char buf[REPORT_SIZE];
            hid_device *handle;
            wchar_t wstr[MAX_STR];
            std::vector<int> positions;

    };   
}

#endif