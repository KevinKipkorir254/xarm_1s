#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <geometry_msgs/msg/twist.hpp>


#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"
#include <geometry_msgs/msg/point.hpp>

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */
using std::placeholders::_1;

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("current_positions"), count_(0)
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Point>("current_positions", 10);
      subscriber_ = this->create_subscription<geometry_msgs::msg::Twist>("cmd_vel", 10, std::bind(&MinimalPublisher::twist_callback, this, _1));
      timer_ = this->create_wall_timer(
      25ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      //auto message = std_msgs::msg::String();
      auto message = geometry_msgs::msg::Point();

      /*
      message.x = (r * sin(t/57.2958))/100;//(-r * sin(t/57.2958))/20;
      message.y = (r * cos(t/57.2958) + 100)/100;
      message.z = (a * t)/1000;
      */

      message.x = x_linear_velocity;
      message.y = y_linear_velocity;
      message.z = z_linear_velocity;
      //RCLCPP_INFO(this->get_logger(), "Publishing: '%f', '%f', '%f'", message.x, message.y, message.z);
      publisher_->publish(message);
    }

    void twist_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
    {
      x_linear_velocity += msg->linear.x;
      y_linear_velocity += msg->linear.y;
      z_linear_velocity += msg->linear.z;
      //RCLCPP_INFO(this->get_logger(), "Received twist: '%f', '%f', '%f'", msg->linear.x, msg->linear.y, msg->linear.z);
    }

    float a = 0;
    float r = 40;
    int t = 0;
    float x_linear_velocity = 0.202857;
    float y_linear_velocity = 0.0;
    float z_linear_velocity = 0.092634;
    float x_angular_velocity = 0.0;

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscriber_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
