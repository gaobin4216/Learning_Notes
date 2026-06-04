# MATLAB 项目组织与脚本化工作流

## 一、M 文件类型

| 类型 | 特点 | 文件名示例 |
|------|------|-----------|
| **脚本（Script）** | 无输入输出，共享工作区变量 | `analyze_data.m` |
| **函数（Function）** | 有独立输入输出，局部变量 | `myadd.m` |
| **类（Class）** | 面向对象编程 | `MyClass.m` |
| **实时脚本（Live Script）** | 混合代码、文本、公式、图形 | `report.mlx` |

### 函数文件基本结构

```matlab
function [out1, out2] = myfunc(in1, in2)
    % MYFUNC 简要描述（help 文本）
    %   详细说明...
    %
    %   示例：
    %   [a, b] = myfunc(1, 2)

    out1 = in1 + in2;
    out2 = in1 * in2;
end
```

> 函数名必须与文件名一致。第一段注释会显示在 `help myfunc` 输出中。

---

## 二、推荐项目结构

```
myproject/
├── src/                  % 主代码
│   ├── main_script.m     % 主脚本
│   ├── myfunc1.m         % 函数
│   └── myfunc2.m
├── lib/                  % 第三方/复用函数
│   └── utils/
│       ├── plot_helper.m
│       └── data_loader.m
├── data/                 % 数据文件
│   ├── raw/              % 原始数据（不修改）
│   └── processed/        % 处理后数据
├── results/              % 输出结果（图、表）
├── tests/                % 测试脚本
│   └── test_myfunc1.m
├── docs/                 % 文档
├── setup_paths.m         % 路径初始化
└── README.md
```

```matlab
% setup_paths.m
function setup_paths()
    root = fileparts(mfilename('fullpath'));
    addpath(genpath(fullfile(root, 'src')));
    addpath(genpath(fullfile(root, 'lib')));
end
```

---

## 三、脚本化工作流最佳实践

### 1. 使用脚本串联流程

```matlab
% run_all.m — 一键执行完整分析流程
setup_paths;

data = load_data('data/raw/input.csv');
result = analyze(data);
generate_report(result, 'results/report.pdf');
```

### 2. 参数集中管理

```matlab
% config.m
function cfg = config()
    cfg.data_path = 'data/raw/';
    cfg.output_path = 'results/';
    cfg.fs = 44100;           % 采样率
    cfg.threshold = 0.5;      % 阈值
end
```

```matlab
% 使用
cfg = config();
data = load_data(cfg.data_path);
```

### 3. 善用 `publish` 自动生成文档

```matlab
% 将脚本发布为 HTML/PDF
publish('my_script.m', 'format', 'html');
```

---

## 四、面向对象编程（OOP）

MATLAB 支持基于类的面向对象编程：

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
r = Rectangle(3, 4);
r.getArea()   % 12
```

### OOP 要点

| 概念 | 关键字 |
|------|--------|
| 类定义 | `classdef` |
| 属性 | `properties` |
| 方法 | `methods` |
| 构造函数 | 与类同名的函数 |
| 继承 | `classdef Child < Parent` |
| 抽象类 | `Abstract = true` |

---

## 五、调试技巧

| 操作 | 方法 |
|------|------|
| 设置断点 | 点击编辑器行号左侧，或 `dbstop` |
| 逐步执行 | `F10`（Step Over）、`F11`（Step Into） |
| 查看变量 | 工作区窗口，或在命令窗口输入变量名 |
| 条件断点 | 右键断点 → 设置条件 |
| 错误后进入调试 | 出错后输入 `dbstop if error`，下次出错自动停在出错行 |

```matlab
dbstop if error          % 出错时自动进入调试
dbstop if warning        % 警告时进入调试
dbstop in myfunc at 10   % 在 myfunc 第10行设断点
dbclear all              % 清除所有断点
dbquit                   % 退出调试模式
```
