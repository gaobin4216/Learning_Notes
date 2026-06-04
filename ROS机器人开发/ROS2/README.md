# ROS2 学习路径

本目录包含 ROS2 (Robot Operating System 2) 的学习资料，以 **Jazzy** 版本为例。

## 学习顺序

| 编号 | 文件 | 内容 | 预计时长 |
|------|------|------|----------|
| 01 | ROS2概述与环境搭建 | ROS2是什么、安装、工作空间、功能包、常用命令 | 2-3天 |
| 02 | ROS2开发工具 | colcon编译、launch文件、RViz2、rqt、tf2、Gazebo | 3-4天 |
| 03 | ROS2通信机制 | 节点、话题、服务、动作、参数、QoS、TF2 | 3-4天 |
| 04 | ROS2机械臂控制 | MoveIt2、ros2_control、仿真与真实机械臂 | 3-5天 |

> ROS1与ROS2的详细对比请参见上级目录的 `ROS1与ROS2对比.md`

## 核心概念速查

- **DDS**: 数据分发服务，ROS2的通信底层
- **QoS**: 服务质量策略，控制通信可靠性
- **colcon**: ROS2的编译工具（替代catkin）
- **ament**: ROS2的构建系统（替代catkin）
- **MoveIt2**: MoveIt的ROS2版本，机械臂运动规划
- **ros2_control**: ros_control的ROS2版本，硬件抽象框架
- **RViz2**: RViz的ROS2版本，可视化工具

## 常用命令

```bash
# 节点
ros2 run <包名> <节点名>
ros2 node list

# 话题
ros2 topic list / echo / pub

# 服务
ros2 service list / call

# 动作
ros2 action list / send_goal

# 编译
colcon build
source install/setup.bash

# Launch
ros2 launch <包名> <launch文件>
```
