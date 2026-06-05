# ROS与CAN集成

> 在ROS系统中通过SocketCAN实现CAN/CANopen通信

---

## 目录

1. [ROS CAN驱动架构](#1-ros-can驱动架构)
2. [环境配置](#2-环境配置)
3. [socketcan_interface](#3-socketcan_interface)
4. [socketcan_bridge](#4-socketcan_bridge)
5. [ros_canopen](#5-ros_canopen)
6. [实战案例](#6-实战案例)
7. [常见问题](#7-常见问题)

---

## 1. ROS CAN驱动架构

### 1.1 三层架构

```
ROS针对SocketCAN提供了三个层次的驱动库：

┌─────────────────────────────────────────────────────────────┐
│                                                             │
│  应用层                                                     │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  ros_canopen                                          │   │
│  │  - CANopen协议实现                                    │   │
│  │  - 节点管理、SDO、PDO、NMT                            │   │
│  │  - 驱动器控制（CiA 402）                              │   │
│  └─────────────────────────────────────────────────────┘   │
│                           │                                 │
│                           ▼                                 │
│  中间层                                                     │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  socketcan_bridge                                     │   │
│  │  - ROS Topic ↔ CAN帧 转换                            │   │
│  │  - 双向桥接                                           │   │
│  └─────────────────────────────────────────────────────┘   │
│                           │                                 │
│                           ▼                                 │
│  基础层                                                     │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  socketcan_interface                                  │   │
│  │  - SocketCAN底层API                                   │   │
│  │  - CAN帧收发                                          │   │
│  │  - 硬件抽象                                           │   │
│  └─────────────────────────────────────────────────────┘   │
│                           │                                 │
│                           ▼                                 │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  Linux SocketCAN（内核）                              │   │
│  └─────────────────────────────────────────────────────┘   │
│                                                             │
└─────────────────────────────────────────────────────────────┘

各层职责：
┌──────────────────────┬──────────────────────────────────────┐
│  包名                │  功能                                │
├──────────────────────┼──────────────────────────────────────┤
│  socketcan_interface │  底层SocketCAN接口，CAN帧收发        │
│  socketcan_bridge    │  ROS Topic与CAN帧的双向转换          │
│  ros_canopen         │  CANopen协议栈，设备控制             │
└──────────────────────┴──────────────────────────────────────┘
```

### 1.2 选择建议

```
根据需求选择合适的包：

1. 只需要收发原始CAN帧
   → 使用 socketcan_interface + socketcan_bridge

2. 需要ROS Topic接口
   → 使用 socketcan_bridge

3. 需要CANopen协议（SDO/PDO/NMT）
   → 使用 ros_canopen

4. 需要控制CANopen电机驱动器
   → 使用 ros_canopen 的 canopen_motor_node
```

---

## 2. 环境配置

### 2.1 安装ROS CAN包

```bash
# ROS1 (Melodic/Noetic)
sudo apt-get install ros-${ROS_DISTRO}-socketcan-bridge
sudo apt-get install ros-${ROS_DISTRO}-ros-canopen

# ROS2 (Foxy/Humble/Iron)
sudo apt-get install ros-${ROS_DISTRO}-canopen-ros2-bridge
sudo apt-get install ros-${ROS_DISTRO}-ros2-canopen

# 或从源码编译
mkdir -p ~/ros_ws/src && cd ~/ros_ws/src
git clone https://github.com/ros-industrial/socketcan_interface.git
git clone https://github.com/ros-industrial/socketcan_bridge.git
git clone https://github.com/ros-industrial/ros_canopen.git
cd ~/ros_ws
catkin_make  # ROS1
colcon build  # ROS2
```

### 2.2 系统配置

```bash
# 1. 加载CAN内核模块
sudo modprobe can
sudo modprobe can_raw
sudo modprobe vcan  # 测试用

# 2. 创建CAN接口
# 真实设备
sudo ip link set can0 type can bitrate 500000
sudo ip link set up can0

# 虚拟CAN（测试）
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

# 3. 验证
ip link show | grep can
```

---

## 3. socketcan_interface

### 3.1 功能概述

```
socketcan_interface 提供底层SocketCAN API：

核心功能：
- 打开/关闭CAN接口
- 发送/接收CAN帧
- 设置过滤器
- 错误处理

类层次：
┌─────────────────────────────────────────────────────────────┐
│  SocketCANInterface                                         │
│  ├── open()      打开接口                                   │
│  ├── close()     关闭接口                                   │
│  ├── send()      发送帧                                     │
│  ├── receive()   接收帧                                     │
│  └── setFilter() 设置过滤器                                 │
└─────────────────────────────────────────────────────────────┘
```

### 3.2 C++使用示例

```cpp
#include <socketcan_interface/socketcan.h>
#include <socketcan_interface/threading.h>

class CANDriver {
public:
    CANDriver() {
        // 创建接口
        interface_ = std::make_shared<can::SocketCANInterface>();
    }

    bool init(const std::string& device) {
        // 打开CAN设备
        if (!interface_->init(device, false)) {
            ROS_ERROR("Failed to initialize CAN device: %s", device.c_str());
            return false;
        }

        // 启动接收线程
        interface_->run();

        // 设置监听器
        listener_ = interface_->createMsgListener(
            can::CommInterface::FrameDelegate(this, &CANDriver::frameCallback));

        return true;
    }

    void send(uint32_t id, const std::vector<uint8_t>& data) {
        can::Frame frame(id, data.size());
        std::copy(data.begin(), data.end(), frame.data.begin());
        interface_->send(frame);
    }

private:
    void frameCallback(const can::Frame& frame) {
        ROS_INFO("Received: ID=0x%03X, DLC=%d", frame.id, frame.dlc);
    }

    can::SocketCANInterfaceSharedPtr interface_;
    can::CommInterface::FrameListenerConstSharedPtr listener_;
};
```

### 3.3 配置文件

```yaml
# can_config.yaml
device: can0
bitrate: 500000
loopback: false
```

---

## 4. socketcan_bridge

### 4.1 功能概述

```
socketcan_bridge 提供ROS Topic与CAN帧的桥接：

┌─────────────────────────────────────────────────────────────┐
│                                                             │
│  ROS Topic                        CAN总线                   │
│  ┌─────────────┐                  ┌─────────────┐          │
│  │ /sent_msgs   │ ──── send ────► │  CAN帧      │          │
│  │ (can_msgs/   │                  │             │          │
│  │  Frame)      │                  │             │          │
│  └─────────────┘                  └─────────────┘          │
│                                                             │
│  ┌─────────────┐                  ┌─────────────┐          │
│  │ /received_   │ ◄── receive ─── │  CAN帧      │          │
│  │ msgs         │                  │             │          │
│  └─────────────┘                  └─────────────┘          │
│                                                             │
└─────────────────────────────────────────────────────────────┘

ROS消息类型：can_msgs/Frame
  - id: CAN ID
  - dlc: 数据长度
  - data: 8字节数据
  - is_rtr: 是否远程帧
  - is_extended: 是否扩展帧
```

### 4.2 启动节点

```bash
# ROS1
rosrun socketcan_bridge socketcan_bridge_node \
  _can_device:=can0 \
  ~sent_msg_topic:=/can/sent \
  ~received_msg_topic:=/can/received

# ROS2
ros2 run socketcan_bridge socketcan_bridge_node \
  --ros-args \
  -p can_device:=can0 \
  -p sent_msg_topic:=/can/sent \
  -p received_msg_topic:=/can/received
```

### 4.3 发送CAN帧

```python
# Python发送示例
import rclpy
from rclpy.node import Node
from can_msgs.msg import Frame

class CANSender(Node):
    def __init__(self):
        super().__init__('can_sender')
        self.pub = self.create_publisher(Frame, '/can/sent', 10)
        self.timer = self.create_timer(0.1, self.send_frame)  # 10Hz

    def send_frame(self):
        msg = Frame()
        msg.id = 0x123
        msg.dlc = 4
        msg.data = [0xAA, 0xBB, 0xCC, 0xDD, 0, 0, 0, 0]
        self.pub.publish(msg)
        self.get_logger().info(f'Sent: ID=0x{msg.id:03X}')

rclpy.init()
node = CANSender()
rclpy.spin(node)
```

### 4.4 接收CAN帧

```python
# Python接收示例
import rclpy
from rclpy.node import Node
from can_msgs.msg import Frame

class CANReceiver(Node):
    def __init__(self):
        super().__init__('can_receiver')
        self.sub = self.create_subscription(
            Frame, '/can/received', self.frame_callback, 10)

    def frame_callback(self, msg):
        data_hex = ' '.join(f'{b:02X}' for b in msg.data[:msg.dlc])
        self.get_logger().info(
            f'Received: ID=0x{msg.id:03X}, DLC={msg.dlc}, Data={data_hex}')

rclpy.init()
node = CANReceiver()
rclpy.spin(node)
```

---

## 5. ros_canopen

### 5.1 功能概述

```
ros_canopen 实现完整的CANopen协议栈：

核心组件：
┌──────────────────────┬──────────────────────────────────────┐
│  组件                │  功能                                │
├──────────────────────┼──────────────────────────────────────┤
│  canopen_master      │  CANopen主站                         │
│  canopen_proxy       │  代理节点，SDO读写                   │
│  canopen_motor_node  │  电机控制节点（CiA 402）             │
│  canopen_chain_node  │  多设备链式管理                      │
└──────────────────────┴──────────────────────────────────────┘
```

### 5.2 配置文件结构

```
ros_canopen 配置文件结构：

config/
├── can0.yaml           # CAN接口配置
├── bus.yml             # 总线设备描述
└── motors/             # 电机配置
    └── motor1.yaml

can0.yaml 示例：
```yaml
bus:
  device: can0
  bitrate: 500000

master:
  node_id: 0
  sync_period: 10000  # 10ms SYNC周期

defaults:
  eds_pkg: my_robot_config
  eds_file: config/motor.eds

nodes:
  motor1:
    node_id: 1
    driver: canopen_motor_node
    name: motor1
```

### 5.3 电机控制节点

```yaml
# motor1.yaml
node_id: 1
name: motor1

# EDS/DCF文件
eds_pkg: my_robot_config
eds_file: config/motor.eds

# 运行模式
mode: profile_position

# PDO映射
tpdo:
  - index: 0
    cob_id: 0x181
    transmission_type: 254  # 事件触发
    event_timer: 10         # 10ms
    mapping:
      - index: 0x6041       # 状态字
        sub_index: 0
        length: 16
      - index: 0x6064       # 实际位置
        sub_index: 0
        length: 32

rpdo:
  - index: 0
    cob_id: 0x201
    transmission_type: 254
    mapping:
      - index: 0x6040       # 控制字
        sub_index: 0
        length: 16
      - index: 0x607A       # 目标位置
        sub_index: 0
        length: 32
```

### 5.4 启动文件

```xml
<!-- ROS1 launch -->
<launch>
  <node name="canopen_node" pkg="canopen_motor_node"
        type="canopen_motor_node" output="screen">
    <param name="bus/device" value="can0"/>
    <param name="bus/bitrate" value="500000"/>
    <param name="master/node_id" value="0"/>
    <param name="master/sync_period" value="10000"/>
    <rosparam command="load" file="$(find my_robot)/config/motor1.yaml"/>
  </node>
</launch>
```

```python
# ROS2 launch
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='canopen_ros2_control',
            executable='canopen_ros2_control_node',
            name='canopen_node',
            parameters=[
                {'bus.device': 'can0'},
                {'bus.bitrate': 500000},
                {'master.node_id': 0},
                {'master.sync_period': 10000},
            ],
        ),
    ])
```

### 5.5 ROS接口

```bash
# 查看可用的ROS接口
ros2 topic list | grep motor1
# /motor1/joint_states
# /motor1/joint_trajectory

ros2 service list | grep motor1
# /motor1/init
# /motor1/halt
# /motor1/recover

# 发送位置指令
ros2 topic pub /motor1/joint_trajectory \
  trajectory_msgs/JointTrajectory "{
    joint_names: ['motor1'],
    points: [{
      positions: [1.57],
      velocities: [0.0],
      time_from_start: {sec: 1}
    }]
  }"

# 读取状态
ros2 topic echo /motor1/joint_states
```

---

## 6. 实战案例

### 6.1 单电机控制

```
场景：通过ROS控制一个CANopen伺服电机

硬件：
- Linux PC + USB-CAN适配器
- CANopen伺服电机（节点ID=1）

步骤：

1. 配置CAN接口
   sudo ip link set can0 type can bitrate 500000
   sudo ip link set up can0

2. 创建ROS包
   ros2 pkg create --build-type ament_cmake my_motor_control

3. 编写配置文件
   config/motor.yaml

4. 编写启动文件
   launch/motor.launch.py

5. 运行
   ros2 launch my_motor_control motor.launch.py

6. 控制
   ros2 topic pub /motor1/joint_trajectory ...
```

### 6.2 Python直接控制（不依赖ros_canopen）

```python
import rclpy
from rclpy.node import Node
import can
import struct
import threading

class SimpleCANopenController(Node):
    """简化的CANopen控制器，直接通过SocketCAN通信"""

    def __init__(self):
        super().__init__('canopen_controller')
        self.bus = can.interface.Bus(channel='can0', bustype='socketcan')
        self.node_id = 1
        self.tx_cob = 0x600 + self.node_id  # SDO请求
        self.rx_cob = 0x580 + self.node_id  # SDO响应

        # 启动接收线程
        self.running = True
        self.recv_thread = threading.Thread(target=self.receive_loop)
        self.recv_thread.start()

        self.get_logger().info(f'CANopen controller started, node_id={self.node_id}')

    def sdo_read(self, index, subindex):
        """SDO读取"""
        cmd = 0x40
        data = struct.pack('<BBxxI', cmd, subindex, index)
        msg = can.Message(arbitration_id=self.tx_cob, data=data)
        self.bus.send(msg)

        # 等待响应
        response = self.bus.recv(timeout=1.0)
        if response and response.arbitration_id == self.rx_cob:
            resp_cmd = response.data[0]
            if resp_cmd == 0x43:  # 4字节
                return struct.unpack('<I', response.data[4:8])[0]
            elif resp_cmd == 0x4B:  # 2字节
                return struct.unpack('<H', response.data[4:6])[0]
            elif resp_cmd == 0x4F:  # 1字节
                return response.data[4]
        return None

    def sdo_write(self, index, subindex, value, size=4):
        """SDO写入"""
        if size == 4:
            cmd = 0x23
            data = struct.pack('<BBxxI', cmd, subindex, index, value)
        elif size == 2:
            cmd = 0x2B
            data = struct.pack('<BBxxH', cmd, subindex, index, value)
        elif size == 1:
            cmd = 0x2F
            data = struct.pack('<BBxxB', cmd, subindex, index, value)

        msg = can.Message(arbitration_id=self.tx_cob, data=data)
        self.bus.send(msg)

        response = self.bus.recv(timeout=1.0)
        if response and response.arbitration_id == self.rx_cob:
            return response.data[0] == 0x60
        return False

    def init_motor(self):
        """初始化电机（CiA 402状态机）"""
        # 读取设备类型
        device_type = self.sdo_read(0x1000, 0x00)
        self.get_logger().info(f'Device type: 0x{device_type:08X}')

        # 设置运行模式为轮廓位置模式
        self.sdo_write(0x6060, 0x00, 0x01, size=1)

        # 状态机转换
        self.sdo_write(0x6040, 0x00, 0x06, size=2)   # Shutdown
        self.sdo_write(0x6040, 0x00, 0x07, size=2)   # Switch on
        self.sdo_write(0x6040, 0x00, 0x0F, size=2)   # Enable operation

        self.get_logger().info('Motor initialized')

    def set_position(self, position):
        """设置目标位置"""
        self.sdo_write(0x607A, 0x00, position, size=4)
        self.sdo_write(0x6040, 0x00, 0x1F, size=2)  # 新设定点

    def receive_loop(self):
        """接收线程"""
        while self.running:
            msg = self.bus.recv(timeout=0.1)
            if msg:
                self.process_frame(msg)

    def process_frame(self, msg):
        """处理接收到的CAN帧"""
        # TPDO1: 状态字 + 实际位置
        if msg.arbitration_id == 0x180 + self.node_id:
            status_word, actual_pos = struct.unpack('<Hi', msg.data[:6])
            self.get_logger().info(
                f'Status: 0x{status_word:04X}, Position: {actual_pos}')

    def shutdown(self):
        """关闭"""
        self.running = False
        self.recv_thread.join()
        self.bus.shutdown()


def main():
    rclpy.init()
    controller = SimpleCANopenController()

    try:
        controller.init_motor()
        controller.set_position(100000)
        rclpy.spin(controller)
    except KeyboardInterrupt:
        pass
    finally:
        controller.shutdown()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
```

---

## 7. 常见问题

### Q1: socketcan_bridge找不到设备？

**A**: 
1. 确认CAN接口已配置并启动：`ip link show can0`
2. 确认用户有权限访问：`sudo chmod 666 /dev/can0` 或加入 `dialout` 组
3. 检查launch文件中的设备名是否正确

### Q2: ros_canopen初始化失败？

**A**:
1. 检查EDS/DCF文件路径是否正确
2. 确认节点ID与实际设备匹配
3. 检查波特率是否与设备一致
4. 使用 `candump` 确认总线上有数据

### Q3: 如何同时控制多个电机？

**A**:
1. 每个电机使用不同的节点ID
2. 在配置文件中添加多个节点
3. 使用 `canopen_chain_node` 管理多个设备
4. 或者为每个电机创建独立的控制器节点

### Q4: 实时性不够怎么办？

**A**:
1. 使用实时内核（PREEMPT_RT）
2. 提高ROS节点的优先级
3. 减少SYNC周期
4. 使用PDO而非SDO传输实时数据
5. 增大传输队列：`ip link set can0 txqueuelen 1000`

### Q5: CANopen与ROS2控制如何集成？

**A**: 使用 `ros2_control` 框架：
```yaml
# ros2_control配置
hardware:
  - name: canopen_hardware
    type: canopen_ros2_control/CANopenSystem
    parameters:
      bus.device: can0
      bus.bitrate: 500000
      motors:
        - name: motor1
          node_id: 1
```

---

## 下一步

学习完所有CAN与CANopen内容后，可以：
1. 实践控制真实的CANopen电机
2. 集成到机器人控制系统
3. 探索CANFD高速通信
