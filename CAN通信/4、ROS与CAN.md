# SocketCan
- Socket CAN 是一种利用现有的网络协议栈实现的开源 CAN 驱动和网络协议接口。它允许在 Linux 操作系统上以标准的 Socket 接口进行 CAN 通信，使得 CAN 通信变得既简单又高效。Socket CAN 是 Linux 内核的一部分。
* Socket CAN 包含以下几个主要组件：
   * can-utils：这是一套用于测试和配置 CAN 设备的工具集。
   * CAN 套接字库：提供了 CAN 通信的 API。
   * 驱动程序：Linux 内核中的驱动支持多种 CAN 硬件。
 * Socket CAN的基础设施
   * 硬件设备主要包括：
     * CAN 接口设备：如 USB-to-CAN 或者 PCI CAN 卡。
     * 目标设备：用于测试的 CAN 总线设备或系统。
   * 软件环境应该包括：
     * Linux 操作系统：推荐使用最新稳定版本的 Linux 发行版。
     * 必要的开发工具：如 GCC 编译器、Make 工具和文本编辑器。
# ROS系统对于CAN通信的支持
    ROS针对socketcan提供了三个层次的驱动库，分别是ros_canopen，socketcan_bridge和socketcan_interface。
    
    这三个包的关系非常明确：
    1、socketcan_interface作为基础，提供了与SocketCAN的直接交互；
    2、socketcan_bridge使用这些接口将ROS系统与CAN网络连接起来；
    3、ros_canopen则在这些基础上实现了符合CANopen协议的高级功能。
        这样的分层设计使得每个组件都可以专注于其核心功能，同时保持了系统的模块化和可扩展性。

* socketcan_interface：
        功能：这是最底层的包，直接与Linux的SocketCAN库交互。它提供了基础的API来发送和接收CAN帧，抽象化了对硬件的直接操作。
        作用：它作为基础层，被其他高级的ROS CAN包使用，来进行更复杂的数据处理和通信逻辑。
* socketcan_bridge：
        功能：这个包是用于将ROS消息（topics）与CAN帧之间进行转换的中间件。它监听ROS系统中的特定topics，将消息转换为CAN帧并发送到CAN网络；同时，它也接收来自CAN网络的帧，转换成ROS消息并发布到ROS网络。
        作用：socketcan_bridge是ROS中最常用的包之一，因为它桥接了ROS系统与实际的硬件设备之间的通信，是实现两者间互操作性的关键组件。
* ros_canopen：
        功能：这个包是基于CANopen协议的实现，它利用socketcan_interface提供的接口，实现了CANopen标准的高级功能，如节点管理、数据对象传输等。
        作用：ros_canopen用于那些需要符合CANopen通信协议的复杂工业应用，提供了一套完整的解决方案，使得ROS能够更好地集成进这些环境中。

