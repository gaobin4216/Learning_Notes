## USB转CAN适配器连接CAN设备,检查已经连接的can设备
**注意U转can的驱动，终端电阻，稳压模块**
1、确认USB转CAN适配器已被系统识别
命令：```lsusb```
作用：检查USB转CAN适配器是否被正确识别为USB设备。
2、查看内核日志中的CAN设备初始化信息
命令：```dmesg | grep -i can```
作用：通过内核日志确认CAN设备驱动加载和设备注册状态。
3、检查SocketCAN网络接口
命令：```ip link show | grep can```
作用：查看系统中已注册的CAN接口（如can0、can1等）。
4、验证CAN接口驱动模块加载
命令：```lsmod | grep can```
作用：确认SocketCAN相关内核模块是否已加载（如 can, can_raw, can_dev 等）。
5、使用专用工具检测CAN设备
工具：candump（需安装 can-utils）
```
sudo ip link set can0 type can bitrate 1000000 #配置波特率
sudo ip link set up can0 #启动can接口 ，关闭时 sudo ip link set can0 down
sudo ip link set can0 txqueuelen 1000 #优化传输队列，在高实时性系统中（如机器人控制），增大txqueuelen可避免数据拥堵
sudo ip -details link show can0 #查看接口状态
sudo ip link set can0 down #关闭can0接口
candump can0  # 接收数据
cansend can0 123#AABBCCDD  # 发送测试帧
```
作用：实时监听CAN总线数据，验证设备通信是否正常。若设备已连接且总线有数据，会显示实时报文。

## 钛虎关节模组的SDO控制实例，轮廓速度模式
can_id为7
```
cansend can0 607#2b7a6000d56c0000
cansend can0 607#2b4060000f000000
cansend can0 607#2b4060001f000000
cansend can0 607#2B40600006000000
cansend can0 607#2B4060000F000000
cansend can0 607#2F60600003000000
cansend can0 607#238360000A000000
cansend can0 607#238460000A000000
cansend can0 607#23816000D0070000
cansend can0 607#23FF6000E8030000
```