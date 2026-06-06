# MATLAB 开发环境选择：MATLAB Desktop、VS Code 与在线平台

## 一、MATLAB 的开发环境

MATLAB 有三种主要的开发环境，适用于不同场景：

| 工具 | 一句话定位 | 适合人群 |
|------|-----------|----------|
| **MATLAB Desktop** | 官方集成开发环境 | MATLAB 开发者（推荐） |
| **VS Code + 插件** | 轻量级代码编辑器 | 跨语言开发者 |
| **MATLAB Online** | 浏览器版 MATLAB | 学生、轻量使用 |

---

## 二、MATLAB Desktop：官方 IDE

### 组成部分

MATLAB Desktop 是一个高度集成的开发环境，包含多个核心窗口：

| 窗口 | 功能 |
|------|------|
| **命令窗口（Command Window）** | 交互式执行命令，查看输出结果 |
| **编辑器（Editor）** | 编写和调试 M 文件，设置断点 |
| **工作区（Workspace）** | 查看和管理当前内存中的变量 |
| **当前文件夹（Current Folder）** | 文件浏览器，管理项目文件 |
| **路径搜索（Path）** | 管理 MATLAB 搜索路径 |
| **帮助浏览器（Help）** | 内置文档、示例和教程 |

### 核心功能

| 功能 | 说明 |
|------|------|
| **代码补全** | 输入函数名时智能提示，Tab 确认 |
| **调试器** | 断点、单步执行、变量监视、调用栈查看 |
| **性能分析器（Profiler）** | 分析代码运行时间，找出性能瓶颈 |
| **发布功能（publish）** | 将脚本发布为 HTML/PDF 报告 |
| **App Designer** | 图形界面（GUI）设计工具 |
| **实时编辑器（Live Editor）** | 混合代码、文本、公式和图形输出 |

### 常用快捷键

| 操作 | 快捷键 | 说明 |
|------|--------|------|
| 运行脚本 | `F5` | 保存并运行当前脚本 |
| 运行选中代码 | `F9` | 只运行选中的代码段 |
| 注释 | `Ctrl + R` | 注释选中行 |
| 取消注释 | `Ctrl + T` | 取消注释选中行 |
| 自动补全 | `Tab` | 触发代码补全 |
| 中断执行 | `Ctrl + C` | 中止正在运行的代码 |
| 查找替换 | `Ctrl + F` | 查找/替换文本 |
| 跳转到行 | `Ctrl + G` | 跳转到指定行号 |
| 查看帮助 | `F1` | 打开选中函数的帮助文档 |
| 设置/清除断点 | `F12` | 在当前行设置或清除断点 |

### 实时脚本（Live Script）

`.mlx` 文件是 MATLAB 的实时脚本格式，类似 Jupyter Notebook：

- 支持富文本格式化（标题、粗体、列表）
- 内嵌数学公式（LaTeX 语法）
- 代码输出内嵌显示（图形、表格）
- 可导出为 PDF、Word、HTML

适用场景：教学课件、实验报告、交互式数据分析。

### 工作区变量的可视化

MATLAB Desktop 的一大优势是工作区窗口可以**直接查看和编辑变量**：

- 双击工作区中的变量，打开变量编辑器
- 可以查看矩阵的每个元素
- 可以直接修改变量值
- 支持按列排序、筛选

---

## 三、VS Code + MATLAB 插件

### 为什么选择 VS Code？

- 免费开源
- 启动速度快（秒开）
- 内存占用小
- 支持多种语言（MATLAB + Python + C++ 混合开发）

### 安装与配置

#### 1. 安装 MATLAB 扩展

打开 VS Code，按 `Ctrl+Shift+X`，搜索并安装：

| 扩展 | 说明 |
|------|------|
| **MATLAB** | MathWorks 官方扩展（必装） |
| **MATLAB Snippets** | 代码片段，快速插入常用代码 |
| **MATLAB Extension Pack** | 扩展合集 |

#### 2. 配置 MATLAB 路径

`.vscode/settings.json`：

```json
{
    "matlab.matlabpath": "C:/Program Files/MATLAB/R2024a/bin/matlab.exe",
    "matlab.linting.enabled": true,
    "matlab.linting.RunCodeAnalysis": true,
    "matlab.editor.enableVariableHighlighting": true
}
```

> **注意**：`matlab.matlabpath` 需要改成你实际安装的 MATLAB 路径。

### VS Code vs MATLAB Desktop

| 特性 | MATLAB Desktop | VS Code |
|------|---------------|---------|
| **启动速度** | 慢（~30 秒） | 快（秒开） |
| **内存占用** | 大（2-4GB） | 小（~300MB） |
| **代码补全** | 强大（了解 MATLAB 语义） | 基础（依赖插件） |
| **调试功能** | 完整 | 有限 |
| **工作区变量** | 可视化查看和编辑 | 不支持 |
| **图形绘制** | 交互式窗口 | 需要 MATLAB 后端 |
| **跨语言支持** | 仅 MATLAB | 多语言 |
| **价格** | 商业授权 | 免费 |

> **选择建议**：
> - 纯 MATLAB 开发 → MATLAB Desktop
> - MATLAB + 其他语言混合开发 → VS Code
> - 临时查看/编辑代码 → VS Code

---

## 四、MATLAB Online

### 什么是 MATLAB Online？

MATLAB Online 是基于浏览器的 MATLAB 版本，无需本地安装，直接在浏览器中使用完整的 MATLAB 功能。

### 使用方式

1. 访问 [https://matlab.mathworks.com](https://matlab.mathworks.com)
2. 使用 MathWorks 账号登录
3. 在浏览器中使用 MATLAB

### 要求

- 需要有效的 MATLAB 许可证（学生版、学术版或商业版）
- 部分大学提供校园许可证，学生可免费使用

### 优缺点

| 优点 | 缺点 |
|------|------|
| 无需安装，打开浏览器就能用 | 需要网络连接 |
| 跨平台（包括平板） | 性能受限于服务器 |
| 自动更新到最新版本 | 部分工具箱不可用 |
| 便于协作和分享 | 文件管理不如本地方便 |
| 不占用本地资源 | 无法使用本地硬件加速 |

---

## 五、MATLAB 与其他工具的集成

### MATLAB + Python 互操作

MATLAB 可以直接调用 Python 函数，Python 也可以调用 MATLAB：

```matlab
% 在 MATLAB 中调用 Python
result = py.math.sqrt(16);      % 4.0
py.numpy.array([1, 2, 3]);      % 调用 NumPy
```

```python
# 在 Python 中调用 MATLAB
import matlab.engine
eng = matlab.engine.start_matlab()
result = eng.sqrt(4.0)  # 2.0
eng.quit()
```

### MATLAB + C/C++ 互操作

- **MEX 文件**：用 C/C++ 编写高性能函数，在 MATLAB 中直接调用
- **MATLAB Coder**：将 MATLAB 代码自动转换为 C/C++ 代码
- **MATLAB Engine for C++**：在 C++ 程序中调用 MATLAB

### MATLAB + Excel 互操作

MATLAB 可以直接读写 Excel 文件，也提供 Excel 插件（Spreadsheet Link）在 Excel 中调用 MATLAB 函数。

---

## 六、环境选择总结

| 场景 | 推荐工具 | 原因 |
|------|----------|------|
| **日常 MATLAB 开发** | MATLAB Desktop | 功能最全，调试最方便 |
| **教学与报告** | MATLAB Desktop 实时脚本 | 富文本 + 代码 + 图形 |
| **跨语言开发** | VS Code + MATLAB 插件 | 支持多种语言 |
| **轻量查看/编辑** | VS Code | 启动快，免费 |
| **学生/无本地安装** | MATLAB Online | 免费，无需安装 |
| **代码生成/嵌入式** | MATLAB Desktop + MATLAB Coder | 生成 C/C++ 代码 |
