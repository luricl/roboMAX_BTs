#include "bt_executor.h"
#include "approach_arm_node.cpp"
#include "approach_nurse_node.cpp"
#include "authenticate_nurse_node.cpp"
// #include "close_drawer_node.cpp"
#include "deposit_node.cpp"
#include "drawer_interface_node.cpp"
#include "navTo_node.cpp"
// #include "open_drawer_node.cpp"
#include "pickup_sample_node.cpp"


BTExecutor::BTExecutor(const std::string &node_name): rclcpp::Node(node_name) {
    this->declare_parameter("bt", rclcpp::PARAMETER_STRING);
    this->declare_parameter("tick_rate_ms", rclcpp::PARAMETER_INTEGER);
    RCLCPP_INFO(get_logger(), "Started BT Executor");
}

void BTExecutor::setup(){
    RCLCPP_INFO(get_logger(), "Started BT Setup");
    create_behavior_tree();
    RCLCPP_INFO(get_logger(), "Created BT Successfully");

    rclcpp::Parameter int_param = this->get_parameter("tick_rate_ms");
    int tick_rate_ms = int_param.as_int();
    auto timer_period = std::chrono::duration<int, std::ratio<1, 1000>>(tick_rate_ms);
    timer_ = this->create_wall_timer(
        timer_period,
        std::bind(&BTExecutor::update_behavior_tree, this));

    rclcpp::spin(shared_from_this());
}

void BTExecutor::halt_behavior_tree(){
    timer_->cancel();
    rclcpp::shutdown();
}

void BTExecutor::update_behavior_tree()
{
    BT::NodeStatus tree_status = tree_.tickRoot();
    if (tree_status == BT::NodeStatus::FAILURE){
        RCLCPP_INFO(get_logger(), "BT Ended with FAILURE");
        halt_behavior_tree();
    } else if (tree_status == BT::NodeStatus::SUCCESS){
        RCLCPP_INFO(get_logger(), "BT Ended with SUCCESS");
        halt_behavior_tree();
    }

}

void BTExecutor::register_nav2_plugins(){
    const std::string plugins_path = ament_index_cpp::get_package_share_directory("rome_bt") + "/behavior_trees/plugins.txt";
    std::ifstream plugin_file;
    plugin_file.open(plugins_path);

    BT::SharedLibrary loader;

    if (plugin_file.is_open())
        for(std::string plugin; std::getline(plugin_file, plugin);)
            factory_.registerFromPlugin(loader.getOSName(plugin));

    plugin_file.close();
}

void BTExecutor::create_behavior_tree(){
    rclcpp::Parameter str_param = this->get_parameter("bt");
    std::string tree_xml = str_param.as_string();

    // Registering Custom BT Nodes
    RCLCPP_INFO(get_logger(), "Registering Nodes");   
    BT::NodeBuilder builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<approachArmNode>(name, config, shared_from_this());
    };
    factory_.registerBuilder<approachArmNode>("approach_arm", builder);

    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<approachNurseNode>(name, config, shared_from_this());
    };
    factory_.registerBuilder<approachNurseNode>("approach_nurse", builder);

    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<authenticateNurseNode>(name, config, shared_from_this());
    };
    factory_.registerBuilder<authenticateNurseNode>("authenticate_nurse", builder);

    // builder = [=](const std::string &name, const BT::NodeConfiguration &config){
    //     return std::make_unique<closeDrawerNode>(name, config, shared_from_this());
    // };
    // factory_.registerBuilder<closeDrawerNode>("close_drawer", builder);

    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<depositNode>(name, config, shared_from_this());
    };
    factory_.registerBuilder<depositNode>("deposit", builder);
    
    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<drawerInterfaceNode>(name, config, shared_from_this());
    };
    factory_.registerBuilder<drawerInterfaceNode>("drawer_interface", builder);
    
    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<navToNode>(name, config, shared_from_this());
    };
    factory_.registerBuilder<navToNode>("navTo", builder);
    
    // builder = [=](const std::string &name, const BT::NodeConfiguration &config){
    //     return std::make_unique<openDrawerNode>(name, config, shared_from_this());
    // };
    // factory_.registerBuilder<openDrawerNode>("open_drawer", builder);

    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<pickupSampleNode>(name, config, shared_from_this());
    };
    factory_.registerBuilder<pickupSampleNode>("pickup_sample", builder);

    // Registering nav2 nodes
    RCLCPP_INFO(get_logger(), "Registering Nav2 Plugins");
    register_nav2_plugins();


    // Creating tree from xml
    RCLCPP_INFO(get_logger(), "Creating Tree %s", tree_xml.c_str());
    tree_ = factory_.createTreeFromFile(tree_xml);
}


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<BTExecutor>("bt_executor");
  node->setup();

  return 0;
}
