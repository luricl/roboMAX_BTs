#include "authenticate_person_node.h"
#include <vector>


authenticatePersonNode::authenticatePersonNode(const std::string &xml_tag_name,
                             const BT::NodeConfiguration &conf,
                             rclcpp::Node::SharedPtr node_ptr): BT::SyncActionNode(xml_tag_name, conf), node_ptr_(node_ptr)
{
    std::string topic = "person";
    auto qos = rclcpp::SystemDefaultsQoS();
    qos.best_effort();
    str_publisher_ptr_ = node_ptr->create_publisher<std_msgs::msg::String>(topic, qos);
}

BT::NodeStatus authenticatePersonNode::tick(){
    std_msgs::msg::String str_msg;
    auto person = getInput<std::string>("person");
    auto num_input = getInput<int>("number");

    if (!person) {
        RCLCPP_ERROR(node_ptr_->get_logger(), "Failed to get 'person' input: %s", person.error().c_str());
        return BT::NodeStatus::FAILURE;
    }

    std::vector<std::string> authorized_people = {"12345", "0987", "5678"};
    int times_to_send = num_input.value();
    for(auto authorized_person : authorized_people){
        if (authorized_person == person.value()){
            str_msg.data = person.value();
            for(int i=0; i<times_to_send; i++){
                str_publisher_ptr_->publish(str_msg);
                sleep(1);
            }
            
            RCLCPP_INFO_STREAM(node_ptr_->get_logger(), "authenticated person: " << person.value().c_str() << "\n");
            return BT::NodeStatus::SUCCESS;
        }
    }

    RCLCPP_INFO_STREAM(node_ptr_->get_logger(), "Fail to authenticate person: " << person.value().c_str() << "\n");
    RCLCPP_INFO_STREAM(node_ptr_->get_logger(), "Returning to base\n");
    
    return BT::NodeStatus::FAILURE;
}
