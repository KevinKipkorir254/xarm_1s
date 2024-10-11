#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <hidapi/hidapi.h>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "xarm_1s_messages/msg/joy_msg.hpp"


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


using namespace std::chrono_literals;
int res;
unsigned char buf[REPORT_SIZE];
hid_device *handle;
wchar_t wstr[MAX_STR];

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("game_pad"), count_(0)
    {
      publisher_ = this->create_publisher<xarm_1s_messages::msg::JoyMsg>("game_pad", 10);
      timer_ = this->create_wall_timer( 8ms, std::bind(&MinimalPublisher::timer_callback, this));
      
            // Initialize the hidapi library
            res = hid_init();
            //printf("hid_init result: %d\n", res);
            RCLCPP_INFO(this->get_logger(), "hid_init result: %d\n", res);

            // Open the device using the VID, PID
            handle = hid_open( 0x2563, 0x0526, NULL);
            if (!handle) {
                //printf("Unable to open device\n");
                RCLCPP_INFO(this->get_logger(), "Unable to open device\n");
            }

            // Read the Manufacturer String
            res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
            //printf("Manufacturer String: %ls\n", wstr);
            RCLCPP_INFO(this->get_logger(), "Manufacturer String: %ls\n", wstr);

            // Read the Product String
            res = hid_get_product_string(handle, wstr, MAX_STR);
            //printf("Product String: %ls\n", wstr);
            RCLCPP_INFO(this->get_logger(), "Product String: %ls\n", wstr);

            // Read the Serial Number String
            res = hid_get_serial_number_string(handle, wstr, MAX_STR);
            //printf("Serial Number String: %ls\n", wstr);
            RCLCPP_INFO(this->get_logger(), "Serial Number String: %ls\n", wstr);
    }

  private:
    void timer_callback()
    {            // Read the response
        res = hid_read_timeout(handle, buf, sizeof(buf), 100);
        if (res > 0) {
            if (res >= 11) {  // Expecting at least 11 bytes
                    //RCLCPP_INFO(this->get_logger(), "Received data:");
                    //RCLCPP_INFO(this->get_logger(), "Button state: 0x%02X", buf[0]);
                        
                        int8_t left_x = (int8_t)buf[1];
                        int8_t left_y = (int8_t)buf[2];
                        int8_t right_x = (int8_t)buf[3];
                        int8_t right_y = (int8_t)buf[4];

                        // Transform values
                        int8_t transformed_left_x = left_x + 128;
                        int8_t transformed_left_y = left_y + 128;
                        int8_t transformed_right_x = right_x + 128;
                        int8_t transformed_right_y = right_y + 128;

                        RCLCPP_INFO(this->get_logger(), "Transformed Left stick X: %d", transformed_left_x);
                        RCLCPP_INFO(this->get_logger(), "Transformed Left stick Y: %d", transformed_left_y);
                        RCLCPP_INFO(this->get_logger(), "Transformed Right stick X: %d", transformed_right_x);
                        RCLCPP_INFO(this->get_logger(), "Transformed Right stick Y: %d", transformed_right_y);

                        auto msg = xarm_1s_messages::msg::JoyMsg();
                        msg.xslider = transformed_left_x;
                        msg.yslider = transformed_left_y;
                        msg.zslider = transformed_right_x;
                        msg.rollslider = transformed_right_y;
                        publisher_->publish(msg);
                    //RCLCPP_INFO(this->get_logger(), "Additional buttons: 0x%02X", buf[5]);
                
                // Print remaining bytes if any
                for (int i = 6; i < res; i++) {
                    //RCLCPP_INFO(this->get_logger(), "Additional data[%d]: 0x%02X", i, buf[i]);
                }
            } else {
                RCLCPP_WARN(this->get_logger(), "Received incomplete data packet");
            }
        } else if (res == 0) {
            RCLCPP_INFO(this->get_logger(), "TIMEOUT");
        } else {
                    RCLCPP_ERROR(this->get_logger(), "ERROR reading data");
                }
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<xarm_1s_messages::msg::JoyMsg>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}