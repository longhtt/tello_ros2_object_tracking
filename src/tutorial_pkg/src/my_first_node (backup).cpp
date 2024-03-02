#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/u_int8.hpp"

class MyNode : public rclcpp::Node
{
public:
   MyNode() : Node("my_node")
   {
      subscriber_ = create_subscription<sensor_msgs::msg::Image>(
         "/image_raw", rclcpp::SensorDataQoS(), std::bind(&MyNode::image_callback, this, std::placeholders::_1));

      publisher_ = create_publisher<std_msgs::msg::UInt8>("/brightness", rclcpp::SensorDataQoS());

      RCLCPP_INFO(get_logger(), "Node started!");
   }

private:
   void image_callback(const sensor_msgs::msg::Image::SharedPtr image)
   {
      long long sum = 0;
      for (uint8_t value : image->data)
      {
         sum += value;
      }
      int avg = sum / image->data.size();

      std_msgs::msg::UInt8 brightness_msg;
      brightness_msg.data = avg;
      publisher_->publish(brightness_msg);
   }

   rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscriber_;
   rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr publisher_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MyNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}