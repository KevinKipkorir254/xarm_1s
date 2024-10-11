#include <chrono>
#include <functional>
#include <memory>
#include <string>


#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"
#include <geometry_msgs/msg/point.hpp>

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("current_positions"), count_(0)
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Point>("current_positions", 10);
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

      message.x = 0.05;
      message.y = 0.0;// this is what behaves as z
      message.z = 0.1;
      RCLCPP_INFO(this->get_logger(), "Publishing: '%f', '%f', '%f'", message.x, message.y, message.z);
      publisher_->publish(message);
      t++;
    }

    float a = 0.1;
    float r = 40;
    int t = 0;

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
