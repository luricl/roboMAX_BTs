# Behaviour Trees Sample Implementations

## RoboMAX

The implementations included in this repository are based on the [RoboMAX](https://github.com/Askarpour/RoboMAX) artifact, a extensible collection of robotic mission adaptation exemplars.

## Docs

Please check the [BT.CPP v3 Docs](https://www.behaviortree.dev/) for additional references.

## Installation

1. Install the [ROS2 Humble](https://docs.ros.org/en/humble/Installation.html) and [nav2]() packages


2. Install Groot (BT editing tool)

```bash
sudo apt install -y git qtbase5-dev libqt5svg5-dev libzmq3-dev libdw-dev cmake build-essential
git clone https://github.com/BehaviorTree/Groot.git
cd Groot && git submodule update --init --recursive && mkdir build && cd build && cmake .. && make
```

3. Build the rome_bt and rome_sim ROS2 packages.

```bash
source /opt/ros/humble/setup.bash
colcon build
```

4. Source the package installs.

```bash
source install/setup.bash
```

## BT.CPP

The trees at `src/rome_bt/behavior_trees` can be executed with the following command:

```bash
ros2 launch rome_bt execute_bt.launch.py bt:="full/path/to/tree"
```

## Executing a BT

The provided `rome_bt` package is used to develop and run behavior trees. Usually to develop nodes 
we create a header file with all our definitions in /include and the actual code implementation in the /src directory.

To execute a node we need to register it to the BT.CPP dynamic loader to load it during runtime.

Try to execute the rome_sim package and then run `rome_bt` with one of the behavior trees in another terminal.

```bash
ros2 launch rome_sim tb4_sim_bringup.launch.py
```

```bash
ros2 launch rome_bt execute_bt.launch.py bt:="$(ros2 pkg prefix rome_bt)/share/rome_bt/behavior_trees/[BT].xml"
```
