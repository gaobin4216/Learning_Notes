# Simulink：图形化建模与仿真

## 一、什么是 Simulink？

Simulink 是 MATLAB 的**图形化仿真环境**，用拖拽模块 + 连线的方式搭建系统模型，替代纯代码编程。

### MATLAB 与 Simulink 的关系

| 工具 | 工作方式 | 适用场景 |
|------|----------|----------|
| **MATLAB** | 写代码做数值计算 | 数据分析、算法原型、信号处理 |
| **Simulink** | 拖模块搭系统模型 | 动态系统仿真、控制系统、通信系统 |

两者经常配合使用：在 Simulink 中搭建系统模型，在 MATLAB 中处理仿真数据。

> **注意**：Simulink 不是免费的，需要单独的许可证（通常和 MATLAB 一起购买或由学校/单位提供）。

---

## 二、Simulink 能做什么

| 领域 | 典型应用 |
|------|----------|
| **控制系统** | PID 控制器设计、系统响应仿真、稳定性分析 |
| **信号处理** | 滤波器设计、信号分析、调制解调 |
| **通信系统** | 信道建模、编码解码、OFDM 系统 |
| **电力电子** | 电机驱动、逆变器仿真、电网建模 |
| **汽车工程** | 自动驾驶算法、整车模型、动力总成 |
| **机器人** | 运动学/动力学仿真、路径规划 |
| **航空航天** | 飞行控制系统、卫星轨道仿真 |
| **深度学习** | 与 MATLAB 深度学习工具箱结合 |

---

## 三、Simulink 基本操作

### 打开 Simulink

```matlab
simulink          % 在 MATLAB 命令窗口输入
```

或在 MATLAB 主页点击 `Simulink` 按钮。

### 界面组成

| 区域 | 功能 |
|------|------|
| **Library Browser** | 模块库，所有可用模块的浏览器 |
| **模型窗口** | 搭建模型的画布 |
| **工具栏** | 运行仿真、配置参数、调试等 |
| **状态栏** | 显示仿真进度和状态 |

### 搭建模型的基本流程

```
1. 打开 Simulink → 新建空白模型（Blank Model）
       ↓
2. 从 Library Browser 拖入模块（信号源、运算、输出等）
       ↓
3. 连接模块的输入输出端口（拖拽连线）
       ↓
4. 双击模块设置参数（增益值、传递函数系数等）
       ↓
5. 添加 Scope（示波器）等观测模块
       ↓
6. 配置仿真参数（仿真时间、求解器等）
       ↓
7. 点击 Run 运行仿真
       ↓
8. 查看 Scope 输出，分析结果
```

---

## 四、常用模块

### Sources（信号源）

| 模块 | 功能 |
|------|------|
| **Sine Wave** | 正弦波信号 |
| **Step** | 阶跃信号（突然从 0 跳到 1） |
| **Constant** | 常量输入 |
| **Clock** | 输出当前仿真时间 |
| **Ramp** | 斜坡信号（线性增长） |
| **From Workspace** | 从 MATLAB 工作区读取数据 |
| **Signal Builder** | 自定义信号波形 |

### Sinks（输出/观测）

| 模块 | 功能 |
|------|------|
| **Scope** | 示波器，实时显示波形（最常用） |
| **Display** | 显示当前数值 |
| **To Workspace** | 将仿真数据写回 MATLAB 工作区 |
| **To File** | 保存数据到 MAT 文件 |
| **Stop Simulation** | 当输入满足条件时停止仿真 |

### Math Operations（数学运算）

| 模块 | 功能 |
|------|------|
| **Sum** | 加减运算（可配置输入个数和符号） |
| **Gain** | 增益（乘法，y = K * u） |
| **Product** | 乘法/除法 |
| **Integrator** | 积分 |
| **Derivative** | 微分 |
| **Math Function** | 数学函数（sin、cos、log、exp 等） |
| **Trigonometric Function** | 三角函数 |

### Continuous（连续系统）

| 模块 | 功能 |
|------|------|
| **Transfer Fcn** | 传递函数 G(s) = N(s)/D(s) |
| **State-Space** | 状态空间模型 |
| **PID Controller** | PID 控制器（可配置 P、I、D 参数） |
| **Zero-Pole** | 零极点形式的传递函数 |

### Discrete（离散系统）

| 模块 | 功能 |
|------|------|
| **Unit Delay** | 延迟一个采样周期 |
| **Discrete Transfer Fcn** | 离散传递函数 |
| **Discrete PID Controller** | 离散 PID 控制器 |
| **Zero-Order Hold** | 零阶保持器 |

---

## 五、一个简单的例子：弹簧-阻尼系统

### 系统描述

一个质量-弹簧-阻尼系统：

```
外力 F(t) → [弹簧 k] → [阻尼 c] → 质量 m → 位移 x(t)
```

运动方程：`m*x'' + c*x' + k*x = F(t)`

变形为：`x'' = (F(t) - c*x' - k*x) / m`

### Simulink 模型搭建

1. **拖入模块**：
   - `Step`（阶跃力输入 F(t)）
   - `Sum`（求和，设置为 `+--`，表示 F - c*x' - k*x）
   - `Gain` × 2（分别代表 c/m 和 k/m）
   - `Integrator` × 2（两次积分：x'' → x' → x）
   - `Scope`（查看位移曲线）

2. **连线**：按方程连接各模块

3. **设置参数**：
   - m = 1, c = 0.5, k = 2
   - 仿真时间 0~20s

4. **运行仿真** → Scope 中看到位移响应曲线

### 对应的 MATLAB 代码

```matlab
% 用 MATLAB 代码做同样的仿真
m = 1; c = 0.5; k = 2;
sys = tf(1, [m c k]);           % 传递函数
step(sys, 20);                   % 阶跃响应
title('弹簧-阻尼系统阶跃响应');
```

> **选择建议**：简单系统用 MATLAB 代码更简洁；复杂系统（多子系统、非线性、混合信号）用 Simulink 更直观。

---

## 六、MATLAB 与 Simulink 的数据交互

### MATLAB → Simulink

```matlab
% 在 MATLAB 工作区定义参数
m = 1; c = 0.5; k = 2;

% 在 Simulink 中可以直接引用这些变量名
% （Gain 模块的参数设为变量名而不是数值）

% 用 From Workspace 模块读取时间序列数据
t = 0:0.01:20;
u = sin(t);
simin = timeseries(u, t);  % 创建时间序列
```

### Simulink → MATLAB

```matlab
% 用 To Workspace 模块将仿真数据导出到 MATLAB 工作区
% 仿真结束后在 MATLAB 中处理
plot(tout, yout);
xlabel('Time (s)');
ylabel('Output');
title('仿真结果');
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
| `.slx` | Simulink 模型文件（压缩 XML 格式） |
| `.mlx` | 实时脚本 |
| `.m` | MATLAB 脚本/函数 |
| `.mat` | MATLAB 数据文件 |
| `.mdl` | 旧版 Simulink 模型文件（R2014b 之前） |

---

## 八、Stateflow：状态机建模

### 什么是 Stateflow？

Stateflow 是 Simulink 的扩展，用于设计**状态机**和**流程图**，适合描述事件驱动的逻辑。

### 典型应用

- 交通灯控制逻辑
- 汽车变速箱换挡逻辑
- 通信协议状态机
- 自动驾驶决策逻辑
- 电梯控制系统

### 基本概念

| 概念 | 说明 |
|------|------|
| **State（状态）** | 系统的某个运行模式（如"红灯"、"绿灯"） |
| **Transition（转移）** | 状态之间的跳转条件（如"定时 30 秒"） |
| **Event（事件）** | 触发状态变化的信号（如"按钮按下"） |
| **Action（动作）** | 进入/退出状态时执行的操作（如"启动计时器"） |

---

## 九、Simulink vs 纯 MATLAB 代码

| 对比项 | Simulink | MATLAB 代码 |
|--------|----------|-------------|
| **建模方式** | 图形化拖拽模块 | 写代码 |
| **适合场景** | 动态系统仿真、控制系统 | 数值计算、数据处理 |
| **直观性** | 系统结构一目了然 | 需要读懂代码 |
| **调试** | 可视化信号流，实时观察 | 断点调试 |
| **代码生成** | 可生成 C/C++ 代码（Embedded Coder） | 需要 MATLAB Coder |
| **学习曲线** | 初期较低，复杂模型较高 | 取决于编程基础 |
| **版本控制** | .slx 是二进制文件，diff 不方便 | .m 是文本文件，Git 友好 |

> **选择建议**：
> - 动态系统、控制系统、信号处理 → Simulink
> - 数据分析、算法原型、统计计算 → MATLAB 代码
> - 复杂项目 → 两者配合使用
