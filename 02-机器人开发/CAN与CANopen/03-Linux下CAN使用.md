# Linux下CAN使用指南

> 本章介绍如何在Linux系统中配置和使用CAN总线

---

## 目录

1. [SocketCAN概述](#1-socketcan概述)
2. [硬件准备](#2-硬件准备)
3. [驱动配置](#3-驱动配置)
4. [can-utils工具](#4-can-utils工具)
5. [Python编程](#5-python编程)
6. [C++编程](#6-c编程)
7. [常见问题](#7-常见问题)

---

## 1. SocketCAN概述

### 1.1 什么是SocketCAN？

```
SocketCAN = Socket + CAN

定义：
- Linux内核中的CAN协议栈
- 使用标准Socket接口进行CAN通信
- 类似于TCP/IP网络编程

特点：
┌─────────────────────────────────────────────────────────────┐
│  ✅ 标准接口：使用socket/bind/sendto/recvfrom              │
│  ✅ 多协议支持：CAN、CANFD、ISO-TP等                        │
│  ✅ 多设备支持：can0、can1、can2...                         │
│  ✅ 高效：内核级实现，性能好                                │
│  ✅ 开源：Linux内核自带                                     │
└─────────────────────────────────────────────────────────────┘
```

### 1.2 SocketCAN架构

```
┌─────────────────────────────────────────────────────────────┐
│                                                             │
│  用户空间                                                   │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  应用程序（candump、cansend、Python、C++）          │   │
│  └─────────────────────────────────────────────────────┘   │
│                           │                                 │
│                           ▼                                 │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  Socket接口（socket/bind/sendto/recvfrom）          │   │
│  └─────────────────────────────────────────────────────┘   │
│                           │                                 │
├───────────────────────────┼─────────────────────────────────┤
│                           │                                 │
│  内核空间                 ▼                                 │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  SocketCAN协议栈                                    │   │
│  │  - can_raw（原始CAN帧）                             │   │
│  │  - can_bcm（广播管理）                              │   │
│  │  - can_isotp（ISO-TP传输）                          │   │
│  └─────────────────────────────────────────────────────┘   │
│                           │                                 │
│                           ▼                                 │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  网络设备层                                         │   │
│  │  - can0、can1、can2...                              │   │
│  └─────────────────────────────────────────────────────┘   │
│                           │                                 │
│                           ▼                                 │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  CAN驱动                                            │   │
│  │  - USB-CAN驱动                                      │   │
│  │  - PCI-CAN驱动                                      │   │
│  │  - SPI-CAN驱动                                      │   │
│  └─────────────────────────────────────────────────────┘   │
│                           │                                 │
│                           ▼                                 │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  CAN硬件                                            │   │
│  │  - USB-CAN适配器                                    │   │
│  │  - PCI-CAN卡                                        │   │
│  │  - CAN控制器                                        │   │
│  └─────────────────────────────────────────────────────┘   │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### 1.3 SocketCAN协议类型

```
┌─────────────┬────────────────────────────────────────────────┐
│   协议      │                    说明                        │
├─────────────┼────────────────────────────────────────────────┤
│  CAN_RAW    │  原始CAN帧，最常用                             │
│  CAN_BCM    │  广播管理，周期性发送/接收                     │
│  CAN_ISOTP  │  ISO-TP传输，大数据分段传输                    │
│  CAN_J1939  │  J1939协议，商用车辆                           │
└─────────────┴────────────────────────────────────────────────┘

CAN_RAW特点：
- 直接收发CAN帧
- 支持过滤器
- 最常用
```

---

## 2. 硬件准备

### 2.1 USB-CAN适配器

```
常见USB-CAN适配器：

1. PCAN-USB（Peak）
   - 品牌：德国Peak
   - 特点：稳定、驱动完善
   - 价格：较贵

2. CANalyst-II
   - 品牌：创芯科技
   - 特点：性价比高
   - 价格：便宜

3. USBtin
   - 品牌：open source
   - 特点：开源硬件
   - 价格：便宜

4. CandleLight
   - 品牌：open source
   - 特点：开源、CANFD支持
   - 价格：便宜

选择建议：
- 学习/开发：CANalyst-II或CandleLight
- 生产环境：PCAN-USB
```

### 2.2 驱动安装

```
1. 检查内核版本
   uname -r
   # 要求 >= 3.6

2. 检查CAN驱动模块
   lsmod | grep can
   # 应该看到 can, can_raw, can_dev 等

3. 如果没有，手动加载
   sudo modprobe can
   sudo modprobe can_raw
   sudo modprobe vcan      # 虚拟CAN
   sudo modprobe gs_usb    # USB-CAN适配器

4. 检查USB设备
   lsusb
   # 应该看到CAN适配器

5. 检查CAN接口
   ip link show | grep can
   # 应该看到 can0, can1 等
```

### 2.3 虚拟CAN（用于测试）

```
创建虚拟CAN接口：

# 创建虚拟CAN
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

验证：
ip link show vcan0
# 应该显示 vcan0: <NOARP,UP,LOWER_UP>

使用：
# 发送测试帧
cansend vcan0 123#AABBCCDD

# 接收
candump vcan0

删除虚拟CAN：
sudo ip link delete vcan0
```

---

## 3. 驱动配置

### 3.1 查看CAN设备

```
1. 检查USB-CAN适配器
   lsusb
   # 示例输出：
   # Bus 001 Device 005: ID 0b40:0123 Generic USB CAN

2. 查看内核日志
   dmesg | grep -i can
   # 示例输出：
   # [12345.678] gs_usb 1-1:1.0: CAN device registered (can0)

3. 查看CAN接口
   ip link show | grep can
   # 示例输出：
   # 3: can0: <NOARP,UP,LOWER_UP> mtu 16 qdisc pfifo_fast state UP

4. 查看CAN驱动模块
   lsmod | grep can
   # 示例输出：
   # gs_usb                 20480  0
   # can_dev                20480  1 gs_usb
   # can_raw                20480  0
   # can                    20480  1 can_raw
```

### 3.2 配置CAN接口

```
1. 关闭CAN接口
   sudo ip link set can0 down

2. 设置波特率
   sudo ip link set can0 type can bitrate 500000

3. 启动CAN接口
   sudo ip link set up can0

4. 验证配置
   sudo ip -details link show can0
   # 示例输出：
   # can0: <NOARP,UP,LOWER_UP> mtu 16 qdisc pfifo_fast state UP
   #     link/can  promiscuity 0
   #     can state ERROR-ACTIVE restart-ms 0
   #           bitrate 500000 sample-point 0.875
   #           tq 125 prop-seg 6 phase-seg1 7 phase-seg2 2 sjw 1

5. 设置传输队列长度（可选）
   sudo ip link set can0 txqueuelen 1000
```

### 3.3 常用配置脚本

```bash
#!/bin/bash
# setup_can.sh - CAN接口配置脚本

CAN_INTERFACE=${1:-can0}
BITRATE=${2:-500000}

echo "配置CAN接口: $CAN_INTERFACE"
echo "波特率: $BITRATE bps"

# 关闭接口
sudo ip link set $CAN_INTERFACE down

# 设置波特率
sudo ip link set $CAN_INTERFACE type can bitrate $BITRATE

# 设置传输队列
sudo ip link set $CAN_INTERFACE txqueuelen 1000

# 启动接口
sudo ip link set up $CAN_INTERFACE

# 验证
echo "CAN接口状态："
sudo ip -details link show $CAN_INTERFACE

echo "配置完成！"
```

---

## 4. can-utils工具

### 4.1 安装can-utils

```
Ubuntu/Debian：
sudo apt-get install can-utils

CentOS/RHEL：
sudo yum install can-utils

从源码编译：
git clone https://github.com/linux-can/can-utils.git
cd can-utils
make
sudo make install
```

### 4.2 candump（接收数据）

```
功能：监听CAN总线数据

用法：
candump [选项] <接口>

常用选项：
- -t a：显示时间戳
- -c：显示颜色
- -e：显示错误帧
- -f：显示完整帧信息

示例：
# 监听can0
candump can0

# 监听多个接口
candump can0,can1

# 显示时间戳
candump -t a can0

# 显示颜色
candump -c can0

# 过滤特定ID
candump can0:0x123

# 过滤ID范围
candump can0:0x100:0x1FF

输出格式：
can0  123   [4]  AA BB CC DD
  │    │    │    │
  │    │    │    └── 数据
  │    │    └── 数据长度
  │    └── CAN ID
  └── 接口名
```

### 4.3 cansend（发送数据）

```
功能：发送CAN帧

用法：
cansend <接口> <帧格式>

帧格式：
- 标准帧：ID#数据
- 扩展帧：ID##数据

示例：
# 发送标准帧
cansend can0 123#AABBCCDD

# 发送扩展帧
cansend can0 12345678#AABBCCDD

# 发送远程帧
cansend can0 123#R

# 发送8字节数据
cansend can0 123#1122334455667788

数据格式：
- 十六进制，不带0x前缀
- 每字节2个字符
- 最多8字节（16个字符）
```

### 4.4 cansniffer（数据分析）

```
功能：分析CAN总线数据变化

用法：
cansniffer [选项] <接口>

常用选项：
- -c：显示颜色
- -t：显示时间戳

示例：
cansniffer can0

输出格式：
ID    | Data                                    | Count
------|-----------------------------------------|------
0x123 | AA BB CC DD 00 00 00 00                 | 100
0x456 | 00 00 00 00 11 22 33 44                 | 50

功能：
- 显示各ID的数据变化
- 高亮变化的字节
- 统计接收次数
```

### 4.5 canplayer（回放数据）

```
功能：回放CAN日志文件

用法：
canplayer [选项] <文件>

示例：
# 录制
candump -l can0 > can_log.asc

# 回放
canplayer can_log.asc

# 指定接口
canplayer -I can_log.asc can0=can1
```

### 4.6 cangen（生成测试数据）

```
功能：生成随机CAN帧（用于测试）

用法：
cangen [选项] <接口>

常用选项：
- -g ms：帧间隔（毫秒）
- -I id：起始ID
- -L len：数据长度
- -n count：帧数量

示例：
# 每100ms发送一帧
cangen -g 100 can0

# 发送10帧
cangen -n 10 can0

# 指定ID范围
cangen -I 100:1FF can0
```

---

## 5. Python编程

### 5.1 安装python-can

```
pip install python-can
```

### 5.2 基础示例

```python
import can

# 创建CAN总线接口
bus = can.interface.Bus(channel='can0', bustype='socketcan')

# 发送消息
msg = can.Message(
    arbitration_id=0x123,
    data=[0xAA, 0xBB, 0xCC, 0xDD],
    is_extended_id=False
)
bus.send(msg)
print(f"发送: {msg}")

# 接收消息
msg = bus.recv(timeout=1.0)  # 1秒超时
if msg:
    print(f"接收: {msg}")
else:
    print("接收超时")

# 关闭接口
bus.shutdown()
```

### 5.3 过滤器配置

```python
import can

bus = can.interface.Bus(channel='can0', bustype='socketcan')

# 配置过滤器
# 只接收ID=0x123的帧
bus.set_filters([
    {"can_id": 0x123, "can_mask": 0x7FF}
])

# 接收ID范围0x100~0x1FF
bus.set_filters([
    {"can_id": 0x100, "can_mask": 0x700}
])

# 接收所有帧
bus.set_filters([])

# 循环接收
for msg in bus:
    print(f"ID: {msg.arbitration_id:03X}, Data: {msg.data.hex()}")
```

### 5.4 SDO通信示例

```python
import can
import struct

class CANopenSDO:
    def __init__(self, bus, node_id):
        self.bus = bus
        self.node_id = node_id
        self.tx_cob = 0x600 + node_id
        self.rx_cob = 0x580 + node_id

    def read(self, index, subindex):
        """读取对象字典"""
        # 构造SDO请求
        cmd = 0x40  # 读取命令
        data = struct.pack('<BBxxI', cmd, subindex, index)

        msg = can.Message(
            arbitration_id=self.tx_cob,
            data=data,
            is_extended_id=False
        )
        self.bus.send(msg)

        # 等待响应
        response = self.bus.recv(timeout=1.0)
        if response and response.arbitration_id == self.rx_cob:
            cmd = response.data[0]
            if cmd & 0x80:  # 错误
                error_code = struct.unpack('<I', response.data[4:8])[0]
                raise Exception(f"SDO错误: 0x{error_code:08X}")
            else:
                # 解析数据
                if cmd == 0x43:  # 4字节
                    return struct.unpack('<I', response.data[4:8])[0]
                elif cmd == 0x4B:  # 2字节
                    return struct.unpack('<H', response.data[4:6])[0]
                elif cmd == 0x4F:  # 1字节
                    return response.data[4]
        return None

    def write(self, index, subindex, value, size=4):
        """写入对象字典"""
        # 构造SDO请求
        if size == 4:
            cmd = 0x23
            data = struct.pack('<BBxxI', cmd, subindex, index, value)
        elif size == 2:
            cmd = 0x2B
            data = struct.pack('<BBxxH', cmd, subindex, index, value)
        elif size == 1:
            cmd = 0x2F
            data = struct.pack('<BBxxB', cmd, subindex, index, value)

        msg = can.Message(
            arbitration_id=self.tx_cob,
            data=data,
            is_extended_id=False
        )
        self.bus.send(msg)

        # 等待响应
        response = self.bus.recv(timeout=1.0)
        if response and response.arbitration_id == self.rx_cob:
            cmd = response.data[0]
            if cmd == 0x60:  # 成功
                return True
            elif cmd & 0x80:  # 错误
                error_code = struct.unpack('<I', response.data[4:8])[0]
                raise Exception(f"SDO错误: 0x{error_code:08X}")
        return False

# 使用示例
bus = can.interface.Bus(channel='can0', bustype='socketcan')
sdo = CANopenSDO(bus, node_id=1)

# 读取设备类型
device_type = sdo.read(0x1000, 0x00)
print(f"设备类型: 0x{device_type:08X}")

# 写入心跳周期
sdo.write(0x1017, 0x00, 1000, size=2)

bus.shutdown()
```

### 5.5 PDO通信示例

```python
import can
import struct
import threading
import time

class CANopenPDO:
    def __init__(self, bus, node_id):
        self.bus = bus
        self.node_id = node_id

        # PDO的COB-ID
        self.tpdo_cob = [0x180 + node_id, 0x280 + node_id,
                         0x380 + node_id, 0x480 + node_id]
        self.rpdo_cob = [0x200 + node_id, 0x300 + node_id,
                         0x400 + node_id, 0x500 + node_id]

    def send_tpdo(self, pdo_num, data):
        """发送TPDO"""
        msg = can.Message(
            arbitration_id=self.tpdo_cob[pdo_num],
            data=data,
            is_extended_id=False
        )
        self.bus.send(msg)

    def recv_rpdo(self, timeout=1.0):
        """接收RPDO"""
        msg = self.bus.recv(timeout=timeout)
        if msg:
            for i, cob in enumerate(self.rpdo_cob):
                if msg.arbitration_id == cob:
                    return i, msg.data
        return None, None

# 使用示例
bus = can.interface.Bus(channel='can0', bustype='socketcan')
pdo = CANopenPDO(bus, node_id=1)

# 发送TPDO0
pdo.send_tpdo(0, [0x01, 0x02, 0x03, 0x04])

# 接收RPDO0
pdo_num, data = pdo.recv_rpdo(timeout=1.0)
if data:
    print(f"RPDO{pdo_num}: {data.hex()}")

bus.shutdown()
```

---

## 6. C++编程

### 6.1 基础示例

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

int main() {
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;

    // 创建Socket
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (s < 0) {
        perror("socket");
        return 1;
    }

    // 获取接口索引
    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    // 绑定Socket
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    bind(s, (struct sockaddr *)&addr, sizeof(addr));

    // 发送帧
    frame.can_id = 0x123;
    frame.can_dlc = 4;
    frame.data[0] = 0xAA;
    frame.data[1] = 0xBB;
    frame.data[2] = 0xCC;
    frame.data[3] = 0xDD;

    write(s, &frame, sizeof(struct can_frame));
    printf("发送: ID=0x%03X, DLC=%d\n", frame.can_id, frame.can_dlc);

    // 接收帧
    int nbytes = read(s, &frame, sizeof(struct can_frame));
    if (nbytes > 0) {
        printf("接收: ID=0x%03X, DLC=%d, Data=", frame.can_id, frame.can_dlc);
        for (int i = 0; i < frame.can_dlc; i++) {
            printf("%02X ", frame.data[i]);
        }
        printf("\n");
    }

    close(s);
    return 0;
}
```

### 6.2 编译和运行

```
编译：
g++ -o can_example can_example.cpp

运行：
./can_example
```

### 6.3 过滤器配置

```cpp
#include <linux/can.h>
#include <linux/can/raw.h>

// 配置过滤器
struct can_filter rfilter[1];
rfilter[0].can_id = 0x123;
rfilter[0].can_mask = 0x7FF;

setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

// 接收ID范围0x100~0x1FF
struct can_filter rfilter[1];
rfilter[0].can_id = 0x100;
rfilter[0].can_mask = 0x700;

setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

// 接收所有帧
setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);
```

---

## 7. 常见问题

### Q1: CAN接口无法启动？

**A**:
1. 检查驱动是否加载：`lsmod | grep can`
2. 检查USB设备：`lsusb`
3. 检查内核日志：`dmesg | grep can`
4. 检查波特率设置是否正确

### Q2: 收不到数据？

**A**:
1. 检查CAN接口状态：`ip -details link show can0`
2. 检查终端电阻：确认120Ω终端电阻
3. 检查波特率：所有节点波特率必须一致
4. 检查过滤器：确认过滤器配置正确

### Q3: 发送失败？

**A**:
1. 检查总线状态：是否有错误帧
2. 检查总线负载：是否过载
3. 检查ID冲突：是否有相同ID

### Q4: 如何提高传输效率？

**A**:
1. 增加传输队列长度：`ip link set can0 txqueuelen 1000`
2. 使用CANFD：支持更大数据帧
3. 优化PDO配置：减少不必要的数据

### Q5: 如何调试CAN通信？

**A**:
1. 使用candump监控总线
2. 使用cansend发送测试帧
3. 检查错误计数器
4. 使用示波器查看波形

---

## 下一步

学习完Linux下CAN使用后，进入 [ROS与CAN集成](05-ROS与CAN集成.md) 了解ROS系统集成。
