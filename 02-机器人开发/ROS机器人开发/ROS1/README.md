# ROS1 学习路径

本目录包含 ROS1 (Robot Operating System) 的完整学习资料，从零基础到机械臂控制。

## 学习顺序

建议按照编号顺序学习，每个文件都建立在前面文件的基础上：

| 编号 | 文件 | 内容 | 预计时长 |
|------|------|------|----------|
| 01 | ROS基础入门与环境搭建 | ROS是什么、安装、编译系统、工作空间与功能包 | 2-3天 |
| 02 | ROS通信机制 | 话题、服务、动作、参数服务器、launch文件、TF | 3-4天 |
| 03 | 机器人建模与URDF | URDF语法、SolidWorks导出、Setup Assistant、Gazebo配置 | 2-3天 |
| 04 | ros_control与MoveIt通信架构 | ros_control框架、MoveIt通信、编程与轨迹规划 | 3-4天 |
| 05 | MoveIt驱动Gazebo与真实机械臂 | 控制器配置、launch实战、完整仿真流程 | 3-5天 |

## 核心概念速查

- **节点 (Node)**: ROS中的可执行程序单元
- **话题 (Topic)**: 异步通信机制，用于数据传输
- **服务 (Service)**: 同步通信机制，用于请求-应答
- **动作 (Action)**: 带反馈和取消功能的通信机制
- **功能包 (Package)**: ROS代码的基本组织单元
- **URDF**: 统一机器人描述格式，定义机器人模型
- **MoveIt**: 机械臂运动规划框架
- **ros_control**: 硬件抽象与控制中间件

## 常用命令

```bash
roscore                          # 启动ROS核心
rosrun <包名> <节点名>            # 运行节点
roslaunch <包名> <launch文件名>   # 启动launch文件
rostopic list                    # 查看话题列表
rostopic echo <话题名>            # 查看话题消息
catkin_make                      # 编译工作空间
source ~/catkin_ws/devel/setup.bash  # 设置环境变量
```
