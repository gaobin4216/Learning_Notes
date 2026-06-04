# ROS机器人开发学习资料

本目录包含ROS1和ROS2的完整学习资料，从零基础到机械臂控制。

## 目录结构

```
ROS机器人开发/
├── ROS1/                           # ROS1学习资料（Noetic）
│   ├── 01-ROS基础入门与环境搭建.md
│   ├── 02-ROS通信机制.md
│   ├── 03-机器人建模与URDF.md
│   ├── 04-ros_control与MoveIt通信架构.md
│   └── 05-MoveIt驱动Gazebo与真实机械臂.md
│
├── ROS2/                           # ROS2学习资料（Jazzy）
│   ├── 01-ROS2概述与环境搭建.md
│   ├── 02-ROS2开发工具.md
│   ├── 03-ROS2通信机制.md
│   └── 04-ROS2机械臂控制.md
│
├── ROS1与ROS2对比.md               # ROS1/ROS2详细对比
└── ROS节点名称关系详解.md           # 节点名、程序名、功能包名的关系
```

## 学习顺序

### ROS1路径（适合初学者）
1. ROS基础入门与环境搭建 → 2. 通信机制 → 3. 机器人建模 → 4. ros_control与MoveIt → 5. MoveIt驱动Gazebo

### ROS2路径（适合有ROS1基础）
1. ROS2概述与环境搭建 → 2. 开发工具 → 3. 通信机制 → 4. 机械臂控制

## 核心概念

- **ROS1**：基于Master的中心化架构，使用catkin编译
- **ROS2**：基于DDS的去中心化架构，使用colcon编译
- **节点（Node）**：ROS中的可执行程序单元
- **功能包（Package）**：ROS代码的基本组织单元
- **MoveIt/MoveIt2**：机械臂运动规划框架
- **ros_control/ros2_control**：硬件抽象与控制中间件

## 常用命令速查

| 功能 | ROS1 | ROS2 |
|------|------|------|
| 运行节点 | `rosrun <包名> <节点名>` | `ros2 run <包名> <节点名>` |
| 启动launch | `roslaunch <包名> <launch文件>` | `ros2 launch <包名> <launch文件>` |
| 编译 | `catkin_make` | `colcon build` |
| 设置环境 | `source devel/setup.bash` | `source install/setup.bash` |
| 查看节点 | `rosnode list` | `ros2 node list` |
| 查看话题 | `rostopic list` | `ros2 topic list` |

## 常见问题

- **节点名和程序名有什么区别？** → 参见 `ROS节点名称关系详解.md`
- **ROS1和ROS2该学哪个？** → 初学者建议从ROS1开始，有基础后学ROS2
- **如何选择ROS2版本？** → 推荐使用最新LTS版本（如Jazzy）

## 学习建议

1. **先动手再理论**：先跑通示例，再理解原理
2. **善用终端**：ROS调试大量依赖命令行工具
3. **多看日志**：`ros2 topic echo`、`ros2 node info` 是调试利器
4. **参考官方文档**：[ROS2 Wiki](https://docs.ros.org/)
