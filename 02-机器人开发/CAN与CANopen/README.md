# CAN与CANopen通信

CAN总线与CANopen协议的基础知识与实践指南。

---

## 目录

| 编号 | 文件 | 内容 |
|------|------|------|
| 1 | CAN与CANopen通信基础 | CAN总线原理、数据帧、CANopen协议栈 |
| 2 | CAN设备在Linux上使用 | SocketCAN、can-utils工具、SDO控制实例 |
| 3 | PDO通信参数与映射参数 | RPDO/TPDO配置详解 |
| 4 | ROS与CAN | socketcan_interface、ros_canopen包 |
| 5 | TPDO与RPDO | 电机控制中的PDO配置实战 |

---

## 学习路径

```
阶段1：CAN基础（第1篇）
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
├── CAN总线定义与特点
├── 硬件连接与差分信号
├── CAN数据帧结构
└── 通信过程与过滤器
        │
        ▼
阶段2：CANopen协议（第1篇后半部分）
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
├── OSI模型与CANopen
├── 对象字典
├── SDO与PDO通信
└── NMT网络管理
        │
        ▼
阶段3：Linux实践（第2篇）
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
├── SocketCAN配置
├── can-utils工具使用
└── SDO读写实例
        │
        ▼
阶段4：PDO深入（第3、5篇）
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
├── PDO通信参数
├── 映射参数配置
└── 电机控制实战
        │
        ▼
阶段5：ROS集成（第4篇）
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
├── socketcan_interface
├── ros_canopen包
└── ROS节点控制CAN设备
```

---

## 核心概念速查

### CAN总线

```
特点：
- 多主站结构，任何节点都可主动发送
- 差分信号，抗干扰能力强
- 半双工通信
- 最高1Mbps（标准CAN）

硬件：
- CAN_H 和 CAN_L 差分信号线
- 120Ω终端电阻（两端）
- CAN控制器 + CAN收发器
```

### CANopen协议

```
核心概念：
- 对象字典（Object Dictionary）：设备参数的数据库
- SDO（Service Data Object）：配置参数读写
- PDO（Process Data Object）：实时数据传输
- NMT（Network Management）：网络状态管理

通信模型：
┌─────────────┐     SDO      ┌─────────────┐
│   主站      │◄────────────►│   从站      │
│  (Master)   │     PDO      │  (Slave)    │
└─────────────┘◄────────────►└─────────────┘
```

---

## 常见应用场景

1. **电机控制**：通过CAN/CANopen控制伺服电机
2. **传感器网络**：多传感器数据采集
3. **工业自动化**：PLC与设备通信
4. **机器人系统**：关节电机通信

---

## 工具推荐

| 工具 | 用途 | 平台 |
|------|------|------|
| can-utils | CAN调试工具 | Linux |
| SocketCAN | Linux CAN驱动 | Linux |
| PCAN-View | CAN总线分析 | Windows |
| CANopenNode | 开源CANopen栈 | 跨平台 |

---

## 参考资源

- [CAN协议规范](https://www.can-cia.org/)
- [CANopen标准](https://www.can-cia.org/canopen/)
- [SocketCAN文档](https://www.kernel.org/doc/html/latest/networking/can.html)
