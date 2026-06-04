# Simulink：图形化建模与仿真

## 一、什么是 Simulink

Simulink 是 MATLAB 的图形化仿真环境，用**拖拽模块 + 连线**的方式搭建系统模型，替代纯代码编程。它和 MATLAB 的关系：

- MATLAB → 写代码做数值计算
- Simulink → 拖模块搭系统模型做仿真

> Simulink 不是免费的，需要单独的许可证（通常和 MATLAB 一起购买或由学校/单位提供）。

---

## 二、Simulink 能做什么

| 领域 | 典型应用 |
|------|----------|
| **控制系统** | PID 控制器设计、系统响应仿真 |
| **信号处理** | 滤波器设计、信号分析 |
| **通信系统** | 调制解调、信道建模 |
| **电力电子** | 电机驱动、逆变器仿真 |
| **汽车工程** | 自动驾驶算法、整车模型 |
| **机器人** | 运动学/动力学仿真 |
| **深度学习** | 与 MATLAB 深度学习工具箱结合 |

---

## 三、Simulink 基本操作

### 打开 Simulink

```matlab
simulink          % 命令窗口输入
```

或在 MATLAB 主页点击 `Simulink` 按钮。

### 界面组成

| 区域 | 功能 |
|------|------|
| **Library Browser** | 模块库，所有可用模块的浏览器 |
| **模型窗口** | 搭建模型的画布 |
| **工具栏** | 运行仿真、配置参数等 |

### 搭建模型的基本流程

1. 打开 Simulink → 新建空白模型（Blank Model）
2. 从 Library Browser 拖入模块
3. 连接模块的输入输出端口
4. 双击模块设置参数
5. 添加 Scope（示波器）等观测模块
6. 点击 **Run** 运行仿真
7. 查看 Scope 输出

---

## 四、常用模块

### Sources（信号源）

| 模块 | 功能 |
|------|------|
| **Sine Wave** | 正弦波 |
| **Step** | 阶跃信号 |
| **Constant** | 常量 |
| **Clock** | 时钟信号 |
| **From Workspace** | 从 MATLAB 工作区读取数据 |

### Sinks（输出/观测）

| 模块 | 功能 |
|------|------|
| **Scope** | 示波器，实时显示波形 |
| **Display** | 显示数值 |
| **To Workspace** | 将数据写回 MATLAB 工作区 |
| **To File** | 保存到文件 |

### Math Operations（数学运算）

| 模块 | 功能 |
|------|------|
| **Sum** | 加减运算 |
| **Gain** | 增益（乘法） |
| **Integrator** | 积分 |
| **Derivative** | 微分 |
| **Math Function** | 数学函数（sin、cos 等） |

### Continuous（连续系统）

| 模块 | 功能 |
|------|------|
| **Transfer Fcn** | 传递函数 |
| **State-Space** | 状态空间模型 |
| **PID Controller** | PID 控制器 |

---

## 五、一个简单的例子：弹簧-阻尼系统

### 系统描述

一个质量-弹簧-阻尼系统：

```
外力 F(t) → [弹簧 k] → [阻尼 c] → 质量 m → 位移 x(t)
```

运动方程：`m*x'' + c*x' + k*x = F(t)`

### Simulink 模型搭建

1. **拖入模块**：
   - `Step`（阶跃力输入）
   - `Sum`（求和，设置为 `+-`）
   - `Gain` × 2（分别代表 c/m 和 k/m）
   - `Integrator` × 2（两次积分得到位移）
   - `Scope`（查看位移曲线）

2. **连线**：按方程连接各模块

3. **设置参数**：
   - m = 1, c = 0.5, k = 2
   - 仿真时间 0~20s

4. **运行仿真** → Scope 中看到位移响应曲线

---

## 六、MATLAB 与 Simulink 的数据交互

### MATLAB → Simulink

```matlab
% 在 MATLAB 工作区定义参数
m = 1; c = 0.5; k = 2;

% 在 Simulink 中用 Gain 模块引用这些变量
% 或用 From Workspace 模块读取时间序列数据
t = 0:0.01:20;
u = sin(t);
simin = timeseries(u, t);  % 创建时间序列
```

### Simulink → MATLAB

```matlab
% 用 To Workspace 模块将仿真数据导出到 MATLAB
% 仿真结束后在 MATLAB 中处理
plot(tout, yout);
xlabel('Time (s)');
ylabel('Output');
```

---

## 七、Simulink 项目组织

### 模型层级

复杂系统可以用**子系统（Subsystem）**分层组织：

```
顶层模型 (top_model.slx)
├── 子系统1：控制器 (controller.slx)
├── 子系统2：被控对象 (plant.slx)
└── 子系统3：传感器 (sensor.slx)
```

选中一组模块 → 右键 → `Create Subsystem from Selection`

### 文件类型

| 文件 | 说明 |
|------|------|
| `.slx` | Simulink 模型文件（压缩 XML） |
| `.mlx` | 实时脚本 |
| `.m` | MATLAB 脚本/函数 |
| `.mat` | MATLAB 数据文件 |

---

## 八、Stateflow：状态机建模

Stateflow 是 Simulink 的扩展，用于设计**状态机**和**流程图**，适合描述事件驱动的逻辑。

### 典型应用

- 交通灯控制逻辑
- 汽车变速箱换挡逻辑
- 通信协议状态机
- 自动驾驶决策逻辑

### 基本概念

| 概念 | 说明 |
|------|------|
| **State（状态）** | 系统的某个运行模式 |
| **Transition（转移）** | 状态之间的跳转条件 |
| **Event（事件）** | 触发状态变化的信号 |
| **Action（动作）** | 进入/退出状态时执行的操作 |

---

## 九、Simulink vs 纯 MATLAB 代码

| 对比项 | Simulink | MATLAB 代码 |
|--------|----------|-------------|
| **建模方式** | 图形化拖拽 | 写代码 |
| **适合场景** | 动态系统仿真、控制系统 | 数值计算、数据处理 |
| **直观性** | 系统结构一目了然 | 需要读懂代码 |
| **调试** | 可视化信号流 | 断点调试 |
| **代码生成** | 可生成 C/C++ 代码（Embedded Coder） | 不支持 |
| **学习曲线** | 初期较低，复杂模型较高 | 取决于编程基础 |

> **建议**：动态系统、控制系统、信号处理用 Simulink；数据分析、算法原型用 MATLAB 代码。两者经常配合使用。
