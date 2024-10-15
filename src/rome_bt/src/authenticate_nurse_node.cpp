#include "authenticate_nurse_node.h"


authenticateNurseNode::authenticateNurseNode(const std::string &xml_tag_name,
                             const BT::NodeConfiguration &conf,
                             rclcpp::Node::SharedPtr node_ptr): BT::SyncActionNode(xml_tag_name, conf), node_ptr_(node_ptr)
{
    std::string topic = "authenticated_nurses";
    auto qos = rclcpp::SystemDefaultsQoS();
    qos.best_effort();
    str_publisher_ptr_ = node_ptr->create_publisher<std_msgs::msg::String>(topic, qos);
}

BT::NodeStatus authenticateNurseNode::tick(){
    std_msgs::msg::String str_msg;
    auto nurse = getInput<std::string>("nurse");
    std::string authorized_nurse = "Mary";
    auto num_input = getInput<int>("number");
    int times_to_send = num_input.value();
    if (authorized_nurse == nurse.value()){
        str_msg.data = nurse.value();
        for(int i=0; i<times_to_send; i++){
            str_publisher_ptr_->publish(str_msg);
            sleep(1);
        }
        
        RCLCPP_INFO_STREAM(node_ptr_->get_logger(), "authenticated nurse: " << nurse.value().c_str() << "\n");
        return BT::NodeStatus::SUCCESS;
    } else{
        return BT::NodeStatus::FAILURE;
    }
}
