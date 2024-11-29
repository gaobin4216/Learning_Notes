## 创建URDF模型 
* 下载ros soildworks的工具  
* 设置坐标轴，注意SW中的Y轴是moveit中的Z轴,在SW中朝上应该朝Y方向  
* 设置个关节基准轴，设置连杆、旋转轴，输出urdf和mesh  
* 文件夹中只有mesh、yrdf和package.xml、camkelist.txt有用  

## 使用moveit! Setup Assistant工具生成配置文件
*  将urdf放在工作空间下,作为一个功能包
*  新建一个功能包，在功能包中touch .setup_assistant
*  roslaunch moveit_setup_assiatant  setup_assistant.launch 生成的文件放在新功能包下，也可以修改已经生成的功能包
*  catkin_make，之后就可以roslaunch了

## 驱动
  * 添加robotmodel
  * 添加motionplanning 
## 控制
 路径规划、轨迹规划，rviz显示