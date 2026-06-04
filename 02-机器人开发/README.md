# 02-机器人开发

ROS 机器人操作系统与 CAN 总线通信的学习资料。

## 目录

### ROS机器人开发

ROS1 (Noetic) 和 ROS2 (Jazzy) 的完整学习路径，从零基础到机械臂控制。

- **ROS1/** — ROS1 学习资料（5篇，适合初学者）
- **ROS2/** — ROS2 学习资料（4篇，适合有ROS1基础）
- **ROS1与ROS2对比.md** — 两代ROS的详细对比
- **ROS节点名称关系详解.md** — 节点名、程序名、功能包名的关系

详见 [ROS机器人开发/README.md](ROS机器人开发/README.md)

### CAN与CANopen

CAN 总线与 CANopen 协议的基础知识与实践。

| 编号 | 文件 | 内容 |
|------|------|------|
| (1) | CAN与CANopen通信基础 | CAN总线原理、数据帧、CANopen协议栈 |
| (2) | CAN设备在Linux上使用 | SocketCAN、can-utils工具、SDO控制实例 |
| (3) | PDO通信参数与映射参数 | RPDO/TPDO配置详解 |
| (4) | ROS与CAN | socketcan_interface、ros_canopen包 |
| (5) | TPDO与RPDO | 电机控制中的PDO配置实战 |
