#include "send_ready_signal_node.h"


sendReadySignalNode::sendReadySignalNode(const std::string &xml_tag_name,
                             const BT::NodeConfiguration &conf,
                             rclcpp::Node::SharedPtr node_ptr): BT::ConditionNode(xml_tag_name, conf){
    std::string topic = "ready_signal";
    auto qos = rclcpp::SystemDefaultsQoS();
    qos.best_effort();
    str_publisher_ptr_ = node_ptr->create_publisher<std_msgs::msg::String>(topic, qos);
}

BT::NodeStatus sendReadySignalNode::tick(){
    std_msgs::msg::String str_msg;
    auto msg = getInput<std::string>("message");
    auto num_input = getInput<int>("number");
    int times_to_send = num_input.value();
    str_msg.data = msg.value();
    for(int i=0; i<times_to_send; i++){
        str_publisher_ptr_->publish(str_msg);
        sleep(1);
    }
    return BT::NodeStatus::SUCCESS;
}
