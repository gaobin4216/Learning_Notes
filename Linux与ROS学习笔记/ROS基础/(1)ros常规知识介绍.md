ROS使用第一步：
Ros安装好之后，可以从ros index中sudo apt install ros-neotic-rqt-xxxxx的软件包
然后先运行roscore  （ros的核心）
然后重开一个命令行开始rosrun下载的软件包中的节点。 
apt上下载的软件包都是编译好的可执行文件，在opt下ros的share中，ROS运行时需要找到自己依赖的软件包的位置也在里面

也可以从GitHub上下载到工作空间的src中，用catkin自己编译，然后运行。


软件包是ros文件的基础，不过不是所有软件包都有节点，很多软件包是依赖性质的基础包，例如std_msgs消息包等

## 从机械臂视角来看ROS
通信机制：节点、话题通信、服务通信、参数服务器  
开发工具：launch、Rviz、rqt、Gazebo、tf  
应用功能：Moveit!  
生态系统：Moveit api、官方教程、机器人功能包

