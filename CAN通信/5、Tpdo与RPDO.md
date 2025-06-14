# PDO
* PDO通信是基于生产者/消费者的通讯模式，每个PDO有一个唯一的标识符且可以通过一个节点发送，但有多个节点可以接收。由生产者发送的 PDO称为发送PDO(TPDO)，同样消费者接收的PDO称为接收PDO(即RPDO)。PDO 的接收不需要消费者的确认。
* 发送接受是相对从节点来说的。

# 在电机控制中

**TPDO（生产者发送的PDO）**：电机发送电机状态（位置、速度、电流等），由事件触发、定时触发、远程请求。在​​周期性同步（SYNC）​​模式下，TPDO可定时发送数据（如每10ms发送一次实际位置）。

**RPDO（生产者接收的PDO）**：上位机发送控制指令（目标位置、速度、扭矩等），由电机接收到。

## TPDO配置
### 通信参数
* 禁用目标TPDO
* 设置TPDO的传输类型
* 禁止时间
### 映射参数
* 清除原有映射
* 添加新的映射参数（通过orders向量传递）
* 设置映射参数数量
* 重新启用TPDO

## RPDO配置
### 通信参数
* 禁用目标RPDO
* 设置RPDO的传输类型
* RPDO​​作为​​接收方​​，通常由主站控制发送频率，抑制时间意义有限，所以一般不设置抑制时间
### 映射参数
* 清除原有映射
* 添加新的映射参数（通过orders向量传递）
* 设置映射参数数量
* 重新启用RPDO