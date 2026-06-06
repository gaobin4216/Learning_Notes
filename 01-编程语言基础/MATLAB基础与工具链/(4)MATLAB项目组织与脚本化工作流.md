# MATLAB 项目组织与脚本化工作流

## 一、M 文件类型总览

| 类型 | 特点 | 用途 | 文件名示例 |
|------|------|------|-----------|
| **脚本（Script）** | 无输入输出参数，共享工作区变量 | 数据分析流程、批处理 | `analyze_data.m` |
| **函数（Function）** | 有独立输入输出，局部变量 | 封装可复用逻辑 | `myadd.m` |
| **类（Class）** | 面向对象，封装属性和方法 | 复杂数据结构 | `MyClass.m` |
| **实时脚本（Live Script）** | 代码 + 文本 + 公式 + 图形 | 教学、报告 | `report.mlx` |

### 脚本 vs 函数的选择

| 场景 | 推荐类型 | 原因 |
|------|----------|------|
| 一次性数据分析 | 脚本 | 简单直接，变量可见 |
| 可复用的算法 | 函数 | 封装输入输出，不污染工作区 |
| 复杂项目 | 函数 + 类 | 模块化、可测试、可维护 |
| 教学/报告 | 实时脚本 | 代码和说明混排 |

---

## 二、推荐项目结构

```
myproject/
├── src/                      % 主代码
│   ├── main_script.m         % 主脚本（入口）
│   ├── process_data.m        % 数据处理函数
│   ├── calculate_stats.m     % 统计计算函数
│   └── generate_report.m     % 报告生成函数
│
├── lib/                      % 第三方/复用函数
│   ├── utils/
│   │   ├── plot_helper.m     % 绑图辅助函数
│   │   └── data_loader.m     % 数据加载函数
│   └── external_toolbox/     % File Exchange 下载的工具
│
├── data/                     % 数据文件
│   ├── raw/                  % 原始数据（不修改）
│   └── processed/            % 处理后数据
│
├── results/                  % 输出结果
│   ├── figures/              % 生成的图形
│   └── tables/               % 生成的表格
│
├── tests/                    % 测试脚本
│   ├── test_process_data.m
│   └── test_calculate_stats.m
│
├── docs/                     % 文档
├── setup_paths.m             % 路径初始化
├── config.m                  % 配置参数
└── README.md
```

### 为什么要这样组织？

| 目录 | 作用 | 好处 |
|------|------|------|
| `src/` | 存放主代码 | 与第三方库分离，便于管理 |
| `lib/` | 存放第三方库 | 不修改第三方代码，方便更新 |
| `data/raw/` | 原始数据 | 保证原始数据不被意外修改 |
| `results/` | 输出结果 | 与源码分离，可以加入 .gitignore |
| `tests/` | 测试脚本 | 保证代码修改后不会出问题 |

---

## 三、脚本化工作流最佳实践

### 1. 使用主脚本串联完整流程

```matlab
% run_all.m — 一键执行完整分析流程
% 团队任何人运行这个脚本，都能得到相同的结果

setup_paths;                                    % 初始化路径
cfg = config();                                 % 加载配置

data = load_data(cfg.data_path);                % 加载数据
cleaned = clean_data(data);                     % 清洗数据
result = analyze(cleaned, cfg);                 % 分析数据
generate_report(result, cfg.output_path);       % 生成报告

disp('分析完成！');
```

### 2. 配置参数集中管理

```matlab
% config.m — 所有可调参数集中在一个文件
function cfg = config()
    % 数据路径
    cfg.data_path = 'data/raw/';
    cfg.output_path = 'results/';

    % 分析参数
    cfg.sample_rate = 44100;      % 采样率
    cfg.threshold = 0.5;          % 阈值
    cfg.window_size = 1024;       % 窗口大小
    cfg.max_iterations = 1000;    % 最大迭代次数

    % 绘图参数
    cfg.figure_format = 'png';    % 图形保存格式
    cfg.figure_dpi = 300;         % 分辨率
end
```

**好处**：需要修改参数时，只改 `config.m` 一个文件，不用在多个脚本中到处找。

### 3. 函数文件写帮助注释

```matlab
function [mean_val, std_val] = compute_stats(data)
    % COMPUTE_STATS 计算数据的均值和标准差
    %
    %   [mean_val, std_val] = compute_stats(data)
    %
    %   输入：
    %       data - 数值向量或矩阵
    %
    %   输出：
    %       mean_val - 均值
    %       std_val  - 标准差
    %
    %   示例：
    %       [m, s] = compute_stats([1, 2, 3, 4, 5])

    mean_val = mean(data);
    std_val = std(data);
end
```

> **为什么写帮助注释？** 输入 `help compute_stats` 时，MATLAB 会显示函数开头的注释。这是最快速的文档方式。

### 4. 善用 `publish` 自动生成文档

```matlab
% 将脚本发布为 HTML 报告
publish('my_script.m', 'format', 'html');

% 发布为 PDF
publish('my_script.m', 'format', 'pdf');
```

`publish` 会把脚本中的代码、注释和输出（包括图形）整合成一份格式化的文档。

---

## 四、面向对象编程（OOP）

### 什么时候用 OOP？

| 场景 | 是否需要 OOP |
|------|-------------|
| 简单数据处理 | 不需要，用函数就够了 |
| 需要保存状态 | 适合用类 |
| 多个相关函数操作同一组数据 | 适合用类 |
| 需要继承和多态 | 必须用类 |

### 类的基本结构

```matlab
% Rectangle.m
classdef Rectangle
    properties
        Width double
        Height double
    end

    methods
        function obj = Rectangle(w, h)
            obj.Width = w;
            obj.Height = h;
        end

        function area = getArea(obj)
            area = obj.Width * obj.Height;
        end
    end
end
```

```matlab
% 使用
r = Rectangle(3, 4);
r.getArea()   % 12
```

### OOP 要点

| 概念 | 关键字 | 说明 |
|------|--------|------|
| 类定义 | `classdef` | 定义一个类 |
| 属性 | `properties` | 类的数据成员 |
| 方法 | `methods` | 类的函数成员 |
| 构造函数 | 与类同名 | 创建对象时自动调用 |
| 继承 | `classdef Child < Parent` | 子类继承父类 |
| 抽象类 | `Abstract = true` | 不能直接实例化 |

---

## 五、调试技巧

### 常用调试操作

| 操作 | 方法 |
|------|------|
| 设置断点 | 点击编辑器行号左侧（红色圆点） |
| 运行到断点 | 按 `F5` 运行脚本 |
| 逐步执行 | `F10`（Step Over）、`F11`（Step Into） |
| 查看变量 | 工作区窗口，或在命令窗口输入变量名 |
| 条件断点 | 右键断点 → 设置条件 |
| 继续运行 | `F5`（Continue） |
| 停止调试 | `Shift + F5` |

### 调试命令

```matlab
dbstop if error          % 出错时自动进入调试模式
dbstop if warning        % 警告时进入调试模式
dbstop in myfunc at 10   % 在 myfunc 第 10 行设断点
dbclear all              % 清除所有断点
dbstep                   % 执行一行
dbstep in                % 进入函数内部
dbstep out               % 执行到当前函数返回
dbcont                   % 继续执行
dbquit                   % 退出调试模式
dbstack                  % 查看调用栈
dbup                     % 切换到上层调用栈
dbdown                   % 切换到下层调用栈
```

### 调试工作流

```
代码出错
    ↓
在出错行设置断点（或用 dbstop if error）
    ↓
运行脚本，自动停在断点
    ↓
检查变量值（工作区窗口或命令窗口）
    ↓
逐步执行（F10），观察变量变化
    ↓
找到问题，修改代码
    ↓
清除断点，重新运行
```
