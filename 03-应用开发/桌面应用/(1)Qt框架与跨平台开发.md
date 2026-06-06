# Qt 开发指南

> **Qt = 跨平台应用开发框架，支持 C++ 和 Python 两种开发方式。**

---

# 第一部分：Qt 通用基础

无论用 C++ 还是 Python，以下概念都是共通的。

## 1. Qt 是什么

Qt（发音同"cute"）是 1991 年诞生的跨平台应用开发框架，最初用于 GUI 开发，现已发展为覆盖桌面、移动、嵌入式、物联网的完整平台。

**核心特点：**

- **真正的跨平台**：一份源码，各平台分别编译，通过 QPA（Qt Platform Abstraction）屏蔽系统差异
- **信号与槽（Signals & Slots）**：Qt 独创的对象通信机制，解耦组件，安全简洁
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
| 3D 支持 | 独立 Qt 3D 模块 | Qt Quick 3D | 2D UI 和 3D 内容融合 |
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

# 第二部分：C++ Qt 开发

适合性能敏感、嵌入式、大型应用开发。

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
| 跨平台 | 较弱，主要生成 Makefile | 极强，生成 VS/Xcode/Ninja/Makefile |
| 第三方库 | 手动指定路径 | `find_package` 自动查找 |
| Qt 官方态度 | 维护模式 | 官方推荐（Qt 6 默认） |
| 上手难度 | 低 | 中高 |

**选择建议**：新项目一律用 CMake。

### CMake 基础配置

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)  # 自动处理 Qt 元对象系统

find_package(Qt6 REQUIRED COMPONENTS Widgets)
add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE Qt6::Widgets)
```

### qmake 基础配置（旧项目维护）

```pro
QT += widgets
SOURCES += main.cpp
TARGET = MyApp
```

## 3. 跨平台编译与编译器要求

Qt 的跨平台是**"一份源码，各平台分别编译"**，不是"一次编译到处运行"。

```
同一份源码 + CMakeLists.txt
  ├── Windows: MSVC/MinGW → .exe
  ├── macOS:   Apple Clang → .app
  └── Linux:   GCC/Clang  → ELF
```

### Windows

Qt 支持 MSVC 和 MinGW 两种编译器，**官方预编译包严格绑定编译器版本**，混用会链接失败或运行时崩溃。

| Qt 版本 | MSVC | MinGW |
|---------|------|-------|
| Qt 6.8 | MSVC 2022 | MinGW 13.1+ |
| Qt 6.7 | MSVC 2022 | MinGW 13.1+ |
| Qt 6.5 LTS | MSVC 2019/2022 | MinGW 11.2+ |
| Qt 6.2 LTS | MSVC 2019 | MinGW 8.1+ |
| Qt 5.15 | MSVC 2015–2019 | MinGW 8.1 |

> **踩坑**：Qt 安装器按编译器版本分组列出组件，一定要选对。

**编译器选择**：
- 个人学习 → MinGW（免装 VS，开箱即用）
- 正式开发 → MSVC 2022（装 VS Community，调试能力强）

**环境配置**：Qt 的 MinGW 路径要排在其他 MinGW 之前，否则 exe 可能加载到错误版本的库。

### macOS

| 要求 | 说明 |
|------|------|
| 编译器 | Apple Clang（随 Xcode 或 Command Line Tools 安装） |
| 最低系统 | Qt 6 要求 macOS 11+ |
| Xcode 版本 | Qt 6.5+ 要求 Xcode 14+，Qt 6.8 要求 Xcode 15+ |
| 架构 | Qt 6.2+ 支持 Apple Silicon (arm64)，可构建 Universal Binary |

```bash
xcode-select --install   # 安装命令行工具
clang --version           # 验证版本
```

### Linux

| 编译器 | 最低版本 | 说明 |
|--------|---------|------|
| GCC | GCC 9+ | 推荐 GCC 11+ |
| Clang | Clang 10+ | 部分发行版默认提供 |

```bash
# Ubuntu/Debian 安装依赖
sudo apt install build-essential libgl1-mesa-dev libglu1-mesa-dev \
    libfontconfig1-dev libfreetype6-dev libx11-dev libx11-xcb-dev \
    libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev \
    libxcb-glx0-dev libxcb-icccm4-dev libxcb-image0-dev \
    libxcb-keysyms1-dev libxcb-randr0-dev libxcb-render-util0-dev \
    libxcb-shape0-dev libxcb-shm0-dev libxcb-sync-dev \
    libxcb-util-dev libxcb-xfixes0-dev libxcb-xinerama0-dev \
    libxcb-xkb-dev libxkbcommon-dev
```

> **glibc 兼容性**：Qt 预编译包依赖特定 glibc 版本。在 Ubuntu 22.04 上编译的程序可能无法在 CentOS 7 上运行。解决办法：Docker 或在目标系统上从源码编译 Qt。

### 交叉编译

| 场景 | 工具 | 难度 |
|------|------|------|
| Windows → Linux | Docker / WSL | 中 |
| x86 → ARM 嵌入式 | GCC ARM 交叉编译器 + 手动编译 Qt 源码 | 高 |
| 桌面 → Android | Android NDK + Qt for Android | 中高 |
| 桌面 → iOS | Xcode + Qt for iOS | 中高 |

> 非嵌入式场景，最简单的方式是在每个目标平台上分别编译，用 CI/CD 自动化。

## 4. C++ Qt 示例代码

```cpp
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Hello Qt");
    window.resize(400, 300);

    auto *layout = new QVBoxLayout(&window);
    auto *label = new QLabel("点击按钮试试");
    auto *btn = new QPushButton("点我");

    // 信号与槽：按钮点击 → 修改标签文字
    QObject::connect(btn, &QPushButton::clicked, [label]() {
        label->setText("Hello from C++ Qt!");
    });

    layout->addWidget(label);
    layout->addWidget(btn);
    window.show();

    return app.exec();
}
```

---

# 第三部分：Python Qt 开发

适合快速原型、工具开发、中小型应用，无需编译，开发效率高。

## 1. 两套绑定对比

| | PyQt6 | PySide6 |
|---|---|---|
| 维护方 | Riverbank Computing | Qt 官方（The Qt Company） |
| 许可证 | GPL v3（商用需购买商业许可） | LGPL（可商用，无需付费） |
| API 完整度 | 完整 | 完整 |
| 生态成熟度 | 更老，资料多 | Qt 官方维护，更新更快 |

**选择建议**：
- **商用项目** → PySide6（LGPL，无授权烦恼）
- **个人学习/开源项目** → 都行，PySide6 是趋势

## 2. 安装 PySide6

```bash
# 基础安装
pip install PySide6

# 附带开发工具（Qt Designer、UIC 编译器等）
pip install PySide6-Addons
```

> 安装包约 100-200MB，包含 Qt 运行时库，无需单独安装 Qt。

## 3. IDE 与编辑器选择

| IDE/编辑器 | 特点 | 推荐场景 |
|------------|------|----------|
| **PyCharm** | 最强 Python IDE，自动补全、调试、重构、虚拟环境管理一体 | 专业 Python 开发 |
| **VS Code + Python 扩展** | 轻量、免费、扩展丰富，搭配 Pylance 补全能力强 | 日常开发、多语言项目 |
| **Qt Creator** | 官方 IDE，UI 设计器集成最好，但 Python 支持较弱 | 以 UI 设计为主时 |
| **Cursor / Windsurf** | AI 辅助编程，适合快速原型开发 | 追求开发效率 |

**推荐组合**：VS Code + Python 扩展 + Pylance + Qt Designer

### VS Code 配置

安装扩展：
- **Python**（微软官方）：语法高亮、调试、虚拟环境
- **Pylance**：智能补全、类型检查
- **Qt for Python**：`.ui` 文件预览

```json
// settings.json 推荐配置
{
    "python.languageServer": "Pylance",
    "python.analysis.typeCheckingMode": "basic",
    "python.terminal.activateEnvironment": true
}
```

### PyCharm 配置

- 自动识别虚拟环境
- 内置终端直接 `pip install`
- 右键 `.ui` 文件可直接打开 Qt Designer
- 调试器支持断点、变量查看、表达式求值

## 4. 虚拟环境管理

每个项目应使用独立虚拟环境，避免包版本冲突：

```bash
# 方式一：venv（Python 内置，轻量）
python -m venv .venv
# Windows 激活
.venv\Scripts\activate
# macOS/Linux 激活
source .venv/bin/activate

# 方式二：conda（适合数据科学、需要管理 Python 版本）
conda create -n myqt python=3.11
conda activate myqt

# 方式三：uv（极快的包管理器，推荐）
pip install uv
uv venv
uv pip install PySide6
```

**虚拟环境目录结构**：

```
my_project/
├── .venv/              # 虚拟环境（不要提交到 git）
├── main.py
├── mainwindow.ui
├── requirements.txt    # 依赖列表
└── .gitignore          # 忽略 .venv/
```

**依赖管理**：

```bash
# 生成依赖列表
pip freeze > requirements.txt

# 从依赖列表安装
pip install -r requirements.txt
```

## 5. Qt Designer（可视化 UI 设计）

Qt Designer 是拖拽式 UI 设计工具，生成 `.ui` 文件（XML 格式），Python 直接加载。

### 启动方式

```bash
# 安装工具
pip install PySide6-Addons

# 启动 Qt Designer
pyside6-designer
```

### 工作流程

```
Qt Designer 拖拽设计
        ↓
    保存 .ui 文件
        ↓
    ┌───────────────────────┐
    │ 方式一：运行时加载     │  方式二：转 Python 代码
    │ QUiLoader().load()    │  pyside6-uic xxx.ui -o xxx.py
    └───────────────────────┘
```

**方式一：运行时加载**（适合快速迭代，UI 修改后无需重新编译）

```python
from PySide6.QtUiTools import QUiLoader
loader = QUiLoader()
window = loader.load("mainwindow.ui")
```

**方式二：转换为 Python 代码**（性能更好，支持 IDE 补全）

```bash
pyside6-uic mainwindow.ui -o ui_mainwindow.py
```

## 6. PySide6 开发工具链

PySide6 提供一套完整的命令行工具：

| 工具 | 命令 | 用途 |
|------|------|------|
| Qt Designer | `pyside6-designer` | 可视化 UI 设计 |
| UIC 编译器 | `pyside6-uic` | `.ui` → Python 代码 |
| 资源编译器 | `pyside6-rcc` | `.qrc` → Python 代码（打包图片等资源） |
| 翻译工具 | `pyside6-lupdate` | 提取代码中的可翻译字符串 |
| 帮助生成 | `pyside6-assistant` | Qt 文档浏览器 |

## 7. 打包分发

Python Qt 应用需要打包成可执行文件才能在没有 Python 环境的机器上运行。

### PyInstaller（最常用）

```bash
pip install pyinstaller

# 基础打包
pyinstaller --windowed --onefile main.py

# 指定图标
pyinstaller --windowed --onefile --icon=app.ico main.py

# 输出目录
# Windows → dist/main.exe
# macOS   → dist/main.app
# Linux   → dist/main
```

| 参数 | 说明 |
|------|------|
| `--windowed` | 无控制台窗口（GUI 应用必加） |
| `--onefile` | 打包成单个文件（启动稍慢，但分发方便） |
| `--icon` | 指定图标 |
| `--add-data` | 附加资源文件（如 .ui、图片） |

### Nuitka（性能更好）

Nuitka 将 Python 编译为 C++，性能更好，体积更小，反编译难度更高：

```bash
pip install nuitka

# 打包
nuitka --standalone --enable-plugin=pyside6 --windows-console-mode=disable main.py
```

### 各平台打包注意事项

| 平台 | 注意 |
|------|------|
| Windows | 需目标机器装 VC++ 运行时（或用 Nuitka 静态打包） |
| macOS | 打包成 .app 后需签名和公证才能正常分发 |
| Linux | glibc 版本兼容问题，建议在目标系统上打包 |
| 全平台 | `.ui`、图片等资源文件需用 `--add-data` 一起打包 |

## 8. 调试技巧

| 方法 | 说明 |
|------|------|
| **IDE 调试器** | PyCharm/VS Code 断点调试，查看变量、调用栈 |
| **print 输出** | 最简单，信号槽连接处加 print 确认流程 |
| **Qt 日志** | `qDebug()`、`qWarning()` 输出到控制台 |
| **Qt Creator** | 可附加到 Python 进程，查看 Qt 对象树 |

**VS Code 调试配置**（`.vscode/launch.json`）：

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Python Qt App",
            "type": "debugpy",
            "request": "launch",
            "program": "${workspaceFolder}/main.py",
            "console": "integratedTerminal"
        }
    ]
}
```

---

# 选型指南：C++ Qt vs Python Qt

| | C++ Qt | Python Qt |
|---|---|---|
| 性能 | 原生性能，适合大型应用 | 略慢，但 GUI 应用够用 |
| 开发速度 | 较慢（编译、链接） | 快（解释执行，热重载） |
| 部署 | 需编译，分发二进制 | 打包成 exe / app |
| 生态 | 完整 Qt 模块 | 绑定 95%+ 的 Qt API |
| 适用场景 | 性能敏感、嵌入式、大型应用 | 快速原型、工具开发、中小型应用 |
| 学习曲线 | 高（C++ + Qt） | 中（Python + Qt API） |
| 跨平台方式 | 各平台分别编译 | 同一份代码直接运行 |

### 工具链对比

| | C++ Qt | Python Qt |
|---|---|---|
| IDE | Qt Creator（官方）、VS、CLion | PyCharm、VS Code |
| 构建工具 | CMake（主流）、qmake | pip、uv、conda |
| 包管理 | vcpkg、conan | PyPI（pip） |
| UI 设计 | Qt Creator 内置设计器 | Qt Designer（pyside6-designer） |
| 调试器 | GDB/LLDB/MSVC | IDE 内置调试器、print |
| 打包工具 | windeployqt、macdeployqt | PyInstaller、Nuitka |
| 虚拟环境 | 不需要 | venv/conda/uv（必须） |

**选择建议**：

- **嵌入式/性能敏感/大型项目** → C++ Qt（Qt Creator + CMake）
- **快速开发/工具/脚本/中小型应用** → Python Qt（VS Code + PySide6）
- **学习 Qt 概念** → 建议从 Python 开始，熟悉后再学 C++
