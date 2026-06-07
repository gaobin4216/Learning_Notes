# Qt 开发指南

> **Qt = 跨平台应用开发框架，支持 C++ 和 Python 两种开发方式。**

---

# 第一部分：Qt 通用基础

## 1. Qt 是什么

Qt（发音同"cute"）是 1991 年诞生的跨平台应用开发框架，覆盖桌面、移动、嵌入式、物联网。

**核心特点：**
- **真正的跨平台**：一份源码，各平台分别编译，通过 QPA（Qt Platform Abstraction）屏蔽系统差异
- **信号与槽（Signals & Slots）**：Qt 独创的对象通信机制，解耦组件
- **丰富的模块**：GUI、网络、数据库、多线程、XML、OpenGL 等
- **两种 UI 技术**：Qt Widgets（传统桌面）和 Qt Quick/QML（现代声明式）

## 2. Qt Widgets vs Qt Quick (QML)

| | Qt Widgets | Qt Quick (QML) |
|---|---|---|
| 核心语言 | C++/Python（逻辑与 UI 耦合） | QML（声明式）+ JS/C++/Python |
| 渲染 | CPU 光栅化，依赖系统原生控件 | GPU 加速（OpenGL/Vulkan/Metal） |
| 界面风格 | 传统桌面外观 | 现代扁平化，高度可定制 |
| 开发模式 | 命令式（代码控制流程） | 声明式（描述 UI 状态，支持热重载） |
| 数据绑定 | 手动（信号与槽） | 自动属性绑定（类似 Vue/React） |
| 动画特效 | 弱 | 极强（原生支持平滑动画、粒子、3D） |
| 触摸支持 | 一般（针对鼠标键盘优化） | 完美（多点触控、手势、惯性滚动） |
| 适合平台 | 桌面端 | 全平台（桌面+移动端+嵌入式） |

**选择建议**：桌面传统应用 → Qt Widgets；移动端/嵌入式/现代 UI → Qt Quick。

## 3. Qt 5 vs Qt 6

Qt 6 是底层架构的重大升级，**新项目应直接用 Qt 6**。

| 特性 | Qt 5 | Qt 6 | 影响 |
|------|------|------|------|
| C++ 标准 | C++11/14 | C++17（最低） | 利用结构化绑定等现代特性 |
| 构建工具 | qmake（主导） | CMake（主导） | qmake 仅维护模式 |
| 图形渲染 | 依赖 OpenGL | RHI（渲染硬件接口） | 自动适配 Vulkan/Metal/Direct3D |
| Python 绑定 | PyQt5 / PySide2 | PyQt6 / PySide6 | API 基本一致，推荐用 6 |

## 4. 信号与槽（核心机制）

信号与槽是 Qt 的灵魂，所有 UI 交互都基于它：

```
信号（Signal）= 某件事发生时发出的通知（如按钮被点击）
槽（Slot）    = 收到信号后执行的函数

发送者.信号.connect(接收者.槽)
```

**特点**：发送者和接收者完全解耦，一个信号可以连接多个槽，多个信号也可以连接同一个槽。

---

# 第二部分：.ui 文件与代码的关系（核心）

> **理解这一部分，就理解了 Qt 开发的核心工作流。**

## 1. .ui 文件是什么

`.ui` 文件是 Qt Designer 生成的 **XML 格式文件**，描述了窗口的布局、控件、属性。它不是代码，而是 UI 的"设计图纸"。

```
.ui 文件（XML）= 控件列表 + 布局 + 属性 + 信号槽声明
```

## 2. C++ 中 .ui 文件的处理

C++ Qt 使用 **uic 编译器** 将 `.ui` 文件编译为 C++ 头文件：

```
设计阶段：  Qt Designer → mainwindow.ui（XML）
构建阶段：  uic mainwindow.ui → ui_mainwindow.h（C++ 头文件）
编译阶段：  #include "ui_mainwindow.h" → 生成的类被编译进可执行文件
```

### 具体机制

uic 生成的 `ui_mainwindow.h` 中包含一个 `Ui_MainWindow` 类：
- 该类有 `setupUi(QWidget*)` 方法，负责创建所有控件并布局
- 该类有 `retranslateUi(QWidget*)` 方法，负责翻译文本
- 控件以**指针成员**形式存在（如 `QPushButton *pushButton`）

### C++ 项目中两种使用 .ui 文件的方式

**方式一：直接使用（推荐）**

在代码中通过 `Ui::MainWindow` 类访问控件：
- 生成的类名规则：`Ui_` + 类名（`Ui_MainWindow`）
- 命名空间：`Ui`
- 用法：继承 `Ui_MainWindow`，调用 `setupUi(this)`

**方式二：QUiLoader 运行时加载**

使用 `QUiLoader` 在运行时动态加载 `.ui` 文件，无需编译：
- 需要 `QtUiTools` 模块
- 用 `findChild<T*>()` 获取控件指针
- 适合插件化、动态 UI 场景

### C++ 中 .ui 文件的构建集成

CMake 中处理 `.ui` 文件的关键配置：
- `set(CMAKE_AUTOUIC ON)` — 自动调用 uic 处理 `.ui` 文件
- `set(CMAKE_AUTOMOC ON)` — 自动处理 Qt 元对象系统（信号槽等）
- 将 `.ui` 文件加入 `add_executable()` 的源文件列表
- CMake 会自动将生成的 `ui_*.h` 加入 include 路径

qmake 中：
- `.ui` 文件加入 `FORMS` 变量
- qmake 自动生成 uic 调用规则

## 3. Python 中 .ui 文件的处理

Python 没有编译阶段，有**两种方式**使用 `.ui` 文件：

### 方式一：运行时加载（推荐初学者）

直接在 Python 中加载 `.ui` 文件，不生成 Python 代码：
- 使用 `QUiLoader` 或 `uic.loadUi()`
- `.ui` 文件修改后无需重新转换，直接生效
- 用 `findChild()` 或 `getattr` 获取控件

**PySide6 的加载方式**：
- `QUiLoader().load("mainwindow.ui")` — 返回窗口对象
- 控件通过 `window.findChild(QPushButton, "pushButton")` 获取

**PyQt6 的加载方式**：
- `uic.loadUi("mainwindow.ui", self)` — 直接加载到当前窗口类
- 控件通过 `self.pushButton` 直接访问（按 objectName 自动绑定）

### 方式二：转换为 Python 代码

使用 `pyside6-uic` 或 `pyuic6` 将 `.ui` 转为 `.py` 文件：
- 转换后生成一个 `Ui_MainWindow` 类
- 在主窗口类中继承并调用 `setupUi(self)`
- 控件以 `self.ui.pushButton` 方式访问

**转换命令**：
```bash
# PySide6
pyside6-uic mainwindow.ui -o ui_mainwindow.py

# PyQt6
pyuic6 mainwindow.ui -o ui_mainwindow.py
```

### 两种方式对比

| | 运行时加载 | 转换为 Python 代码 |
|---|---|---|
| 修改 UI 后 | 直接生效，无需转换 | 需重新运行 uic 命令 |
| IDE 补全 | 无（需 findChild） | 有（生成的类有类型提示） |
| 性能 | 启动时解析 XML，略慢 | 直接执行 Python，略快 |
| 调试 | 控件名在运行时才确定 | 编译时已知 |
| 推荐场景 | 快速迭代、原型开发 | 正式项目、需要补全 |

## 4. C++ 与 Python 的完整工具链对比

### C++ Qt 工具链

| 环节 | 工具 | 输入 | 输出 |
|------|------|------|------|
| UI 设计 | Qt Creator 设计器 / Qt Designer | 拖拽控件 | `.ui` 文件（XML） |
| UI 编译 | uic（CMake 自动调用） | `.ui` 文件 | `ui_*.h`（C++ 头文件） |
| 元对象编译 | moc（CMake 自动调用） | 含 `Q_OBJECT` 的头文件 | `moc_*.cpp` |
| 资源编译 | rcc | `.qrc` 文件 + 图片等 | `qrc_*.cpp` |
| 构建 | CMake + 编译器 | 所有源文件 | 可执行文件 |
| 部署 | windeployqt / macdeployqt | 可执行文件 | 带依赖的分发包 |

### Python Qt 工具链

| 环节 | 工具 | 输入 | 输出 |
|------|------|------|------|
| UI 设计 | Qt Designer（`pyside6-designer`） | 拖拽控件 | `.ui` 文件（XML） |
| UI 转代码（可选） | `pyside6-uic` | `.ui` 文件 | `ui_*.py`（Python 代码） |
| 资源编译（可选） | `pyside6-rcc` | `.qrc` 文件 + 图片等 | `qrc_*.py` |
| 运行 | Python 解释器 | `.py` 文件 | 直接运行 |
| 打包 | PyInstaller / Nuitka | `.py` 文件 | 可执行文件 |

### 关键区别

| | C++ Qt | Python Qt |
|---|---|---|
| `.ui` 文件处理 | **必须**编译为 C++ 头文件 | 可选：运行时加载 或 转为 .py |
| moc | **必须**（处理信号槽元对象） | 不需要（PySide6 内部处理） |
| rcc | **必须**（打包资源到二进制） | 可选（也可以直接引用文件路径） |
| 构建步骤 | 设计 → uic → moc → rcc → 编译 → 链接 | 设计 → 运行（或 uic → 运行） |

## 5. .ui 文件的本质结构

`.ui` 文件是标准 XML，核心结构：

```
<ui version="4.0">
  <class>MainWindow</class>          ← 窗口类名
  <widget class="QMainWindow">      ← 根控件
    <property name="geometry">       ← 属性（位置、大小等）
    <widget class="QPushButton">    ← 子控件
      <property name="text">        ← 控件属性
      <signal name="clicked"/>      ← 信号声明
    </widget>
  </widget>
  <connections/>                     ← 信号槽连接声明
  <customwidgets/>                   ← 自定义控件
</ui>
```

**objectName 的重要性**：每个控件的 `objectName` 是代码中访问它的唯一标识。在 C++ 中对应成员变量名，在 Python 中对应 `findChild()` 的参数。

---

# 第三部分：C++ Qt 开发

## 1. 开发环境搭建

### 安装 Qt

1. 下载 Qt 在线安装器：https://www.qt.io/download-qt-installer
2. 登录 Qt 账号（需注册）
3. 选择组件：
   - **Qt 版本**：选 Qt 6.x（如 Qt 6.8）
   - **编译器**：根据你的平台选择（见下文）
   - **Qt Creator**：官方 IDE，建议勾选
   - **可选模块**：Qt Quick、Qt 3D 等按需选择

### Qt Creator（官方 IDE）

Qt Creator 集成了代码编辑、UI 可视化设计、调试、构建于一体：
- **项目管理**：自动识别 CMake/qmake 项目
- **UI 设计器**：拖拽设计 Qt Widgets 界面，生成 `.ui` 文件
- **调试器**：集成 GDB/LLDB/MSVC 调试器
- **Kits 配置**：工具 → 选项 → Kits，配置 Qt 版本、编译器、调试器的组合

## 2. 构建系统：qmake vs CMake

| | qmake | CMake |
|---|---|---|
| 定位 | Qt 专用构建工具 | C/C++ 工业标准构建系统 |
| 配置文件 | `.pro`（简单） | `CMakeLists.txt`（强大） |
| 第三方库 | 手动指定路径 | `find_package` 自动查找 |
| Qt 官方态度 | 维护模式 | 官方推荐（Qt 6 默认） |

**选择建议**：新项目一律用 CMake。

## 3. 跨平台编译与编译器要求

Qt 的跨平台是**"一份源码，各平台分别编译"**，不是"一次编译到处运行"。

### Windows

Qt 支持 MSVC 和 MinGW 两种编译器，**官方预编译包严格绑定编译器版本**，混用会链接失败。

| Qt 版本 | MSVC | MinGW |
|---------|------|-------|
| Qt 6.8 | MSVC 2022 | MinGW 13.1+ |
| Qt 6.7 | MSVC 2022 | MinGW 13.1+ |
| Qt 6.5 LTS | MSVC 2019/2022 | MinGW 11.2+ |

- 个人学习 → MinGW（免装 VS，开箱即用）
- 正式开发 → MSVC 2022（装 VS Community，调试能力强）

> **踩坑**：Qt 安装器按编译器版本分组列出组件，一定要选对。Qt 的 MinGW 路径要排在其他 MinGW 之前。

### macOS

- 编译器：Apple Clang（随 Xcode 或 Command Line Tools 安装）
- Qt 6 要求 macOS 11+，Xcode 14+（Qt 6.8 要求 Xcode 15+）
- Qt 6.2+ 支持 Apple Silicon (arm64)，可构建 Universal Binary

### Linux

- GCC 9+（推荐 GCC 11+）或 Clang 10+
- 需安装 X11/XCB 开发库（Ubuntu: `sudo apt install build-essential libgl1-mesa-dev libx11-dev ...`）

> **glibc 兼容性**：Qt 预编译包依赖特定 glibc 版本。在高版本系统编译的程序可能无法在低版本系统运行。解决办法：Docker 或在目标系统上从源码编译 Qt。

---

# 第四部分：Python Qt 开发

## 1. 两套绑定对比

| | PyQt6 | PySide6 |
|---|---|---|
| 维护方 | Riverbank Computing | Qt 官方（The Qt Company） |
| 许可证 | GPL v3（商用需购买商业许可） | LGPL（可商用，无需付费） |
| API 完整度 | 完整 | 完整 |
| 生态成熟度 | 更老，资料多 | Qt 官方维护，更新更快 |

**选择建议**：商用项目 → PySide6（LGPL）；个人学习/开源 → 都行，PySide6 是趋势。

## 2. 安装 PySide6

```bash
# 基础安装
pip install PySide6

# 附带开发工具（Qt Designer、UIC 编译器等）
pip install PySide6-Addons
```

> 安装包约 100-200MB，包含 Qt 运行时库，无需单独安装 Qt。

## 3. 虚拟环境管理

每个项目应使用独立虚拟环境，避免包版本冲突：

```bash
# 方式一：venv（Python 内置，轻量）
python -m venv .venv
# Windows 激活：.venv\Scripts\activate
# macOS/Linux 激活：source .venv/bin/activate

# 方式二：conda（适合数据科学）
conda create -n myqt python=3.11
conda activate myqt

# 方式三：uv（极快的包管理器，推荐）
pip install uv
uv venv
uv pip install PySide6
```

**项目目录结构**：
```
my_project/
├── .venv/              # 虚拟环境（不提交到 git）
├── main.py
├── mainwindow.ui
├── ui_mainwindow.py    # uic 生成的（可选）
├── requirements.txt
└── .gitignore
```

## 4. PySide6 开发工具链

| 工具 | 命令 | 用途 |
|------|------|------|
| Qt Designer | `pyside6-designer` | 可视化 UI 设计，生成 `.ui` 文件 |
| UIC 编译器 | `pyside6-uic` | `.ui` → Python 代码 |
| 资源编译器 | `pyside6-rcc` | `.qrc` → Python 代码（打包图片等资源） |
| 翻译工具 | `pyside6-lupdate` | 提取代码中的可翻译字符串 |
| 帮助文档 | `pyside6-assistant` | Qt 文档浏览器 |

## 5. IDE 选择

| IDE/编辑器 | 特点 | 推荐场景 |
|------------|------|----------|
| **PyCharm** | 最强 Python IDE，自动补全、调试、重构一体 | 专业 Python 开发 |
| **VS Code** | 轻量、免费、扩展丰富，搭配 Pylance 补全能力强 | 日常开发、多语言项目 |
| **Qt Creator** | 官方 IDE，UI 设计器集成最好，但 Python 支持较弱 | 以 UI 设计为主时 |

**推荐组合**：VS Code + Python 扩展 + Pylance + Qt Designer

## 6. 打包分发

### PyInstaller（最常用）

```bash
pip install pyinstaller
pyinstaller --windowed --onefile main.py
```

| 参数 | 说明 |
|------|------|
| `--windowed` | 无控制台窗口（GUI 应用必加） |
| `--onefile` | 单个文件（启动略慢，分发方便） |
| `--add-data` | 附加资源文件（`.ui`、图片等） |

### Nuitka（性能更好）

```bash
pip install nuitka
nuitka --standalone --enable-plugin=pyside6 --windows-console-mode=disable main.py
```

各平台打包注意：Windows 需 VC++ 运行时；macOS 需签名公证；Linux 注意 glibc 兼容。

---

# 选型指南

| | C++ Qt | Python Qt |
|---|---|---|
| 性能 | 原生性能，适合大型应用 | 略慢，但 GUI 应用够用 |
| 开发速度 | 较慢（编译、链接） | 快（解释执行，热重载） |
| 部署 | 需编译，分发二进制 | 打包成 exe / app |
| 适用场景 | 性能敏感、嵌入式、大型应用 | 快速原型、工具开发、中小型应用 |
| 学习曲线 | 高（C++ + Qt） | 中（Python + Qt API） |

**选择建议**：
- **嵌入式/性能敏感/大型项目** → C++ Qt（Qt Creator + CMake）
- **快速开发/工具/脚本/中小型应用** → Python Qt（VS Code + PySide6）
- **学习 Qt 概念** → 建议从 Python 开始，熟悉后再学 C++
