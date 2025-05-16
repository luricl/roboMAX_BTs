#include "rclcpp/rclcpp.hpp"
#include <rclcpp/qos.hpp>
#include "std_msgs/msg/string.hpp"

#include "behaviortree_cpp_v3/action_node.h"

#include <string>


class authenticatePersonNode: public BT::SyncActionNode{
    public:
        explicit authenticatePersonNode(const std::string &name,
                               const BT::NodeConfiguration &config,
                               rclcpp::Node::SharedPtr node_ptr);

        BT::NodeStatus tick() override;

        static BT::PortsList providedPorts() {
            return BT::PortsList {BT::InputPort<std::string>("person"),
                                  BT::InputPort<int>("number")};
        }

    private:
        rclcpp::Node::SharedPtr node_ptr_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr str_publisher_ptr_;
};