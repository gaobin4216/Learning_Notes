# Qt 开发指南

> **一句话：跨平台 C++ GUI 框架，一套源码编译到 Windows/macOS/Linux/嵌入式/移动端。**

---

## 一、Qt 简介

Qt（发音同"cute"）是 1991 年诞生的跨平台 C++ 应用开发框架，最初用于 GUI 开发，现已发展为覆盖桌面、移动、嵌入式、物联网的完整平台。

**核心特点：**

- **真正的跨平台**：一份源码 + CMakeLists.txt，各平台分别编译，通过 QPA（Qt Platform Abstraction）屏蔽系统差异
- **信号与槽（Signals & Slots）**：Qt 独创的对象通信机制。信号 = 状态变化时发出通知（如按钮被点击），槽 = 监听到信号后执行的函数。解耦组件，安全简洁
- **丰富的模块**：GUI（按钮、表格）、网络（HTTP、WebSocket）、数据库（SQLite、MySQL）、多线程、XML、OpenGL 等
- **QML / Qt Quick**：声明式 UI 语言，适合流畅动画和现代界面，在移动端和嵌入式上表现尤佳
- **Qt Creator**：官方 IDE，集代码编辑、UI 可视化设计、调试于一体

---

## 二、Qt 5 vs Qt 6

Qt 6 是底层架构的重大升级，不仅仅是功能增加。

| 特性 | Qt 5 | Qt 6 | 影响 |
|------|------|------|------|
| C++ 标准 | C++11/14 | C++17（最低） | 利用结构化绑定等现代特性 |
| 构建工具 | qmake（主导） | CMake（主导） | qmake 仅维护模式，新项目用 CMake |
| 图形渲染 | 依赖 OpenGL | RHI（渲染硬件接口） | 自动适配 Vulkan/Metal/Direct3D |
| 3D 支持 | 独立 Qt 3D 模块 | Qt Quick 3D | 2D UI 和 3D 内容融合在同一场景图 |

---

## 三、qmake 与 CMake

| | qmake | CMake |
|---|---|---|
| 定位 | Qt 专用构建工具 | C/C++ 工业标准构建系统 |
| 配置文件 | `.pro`（简单） | `CMakeLists.txt`（强大） |
| 跨平台 | 较弱，主要生成 Makefile | 极强，生成 VS/Xcode/Ninja/Makefile |
| 第三方库 | 手动指定路径 | `find_package` 自动查找，生态极好 |
| Qt 官方态度 | 维护模式 | 官方推荐（Qt 6 默认） |
| 上手难度 | 低 | 中高 |

**qmake**：很懂 Qt（自动处理 moc/uic/rcc），但除了 Qt 什么都不懂，链接 OpenCV 等库要手动写路径。

**CMake**：整个 C++ 界的工业标准，绝大多数第三方库（vcpkg、conan）优先提供 CMake 支持。

---

## 四、Qt Widgets vs Qt Quick (QML)

| | Qt Widgets | Qt Quick (QML) |
|---|---|---|
| 核心语言 | C++（逻辑与 UI 耦合） | QML（声明式）+ JS/C++ |
| 渲染 | CPU 光栅化，依赖系统原生控件 | GPU 加速（OpenGL/Vulkan/Metal） |
| 界面风格 | 传统桌面外观 | 现代扁平化，高度可定制 |
| 开发模式 | 命令式（代码控制流程） | 声明式（描述 UI 状态，支持热重载） |
| 数据绑定 | 手动（信号与槽） | 自动属性绑定（类似 Vue/React） |
| 动画特效 | 弱 | 极强（原生支持平滑动画、粒子、3D） |
| 触摸支持 | 一般（针对鼠标键盘优化） | 完美（多点触控、手势、惯性滚动） |
| 资源占用 | 低 | 较高（需加载 QML 引擎） |
| 适合平台 | 桌面端 | 全平台（桌面+移动端+嵌入式） |

---

## 五、跨平台编译与编译器要求

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

> **踩坑**：Qt 安装器（MaintenanceTool）按编译器版本分组列出组件，一定要选对。用 Qt 6.8 的 MSVC 2022 包却用 MSVC 2019 编译，会直接报错。

**环境配置**：Windows 开发时，环境变量中 Qt 的 MinGW 路径要排在其他 MinGW 之前，否则 exe 可能加载到错误版本的库。

**Qt Creator 中切换编译器**：工具 → 选项 → Kits → 选择 Kit（Qt Version / Compiler / Debugger）。

### macOS

| 要求 | 说明 |
|------|------|
| 编译器 | Apple Clang（随 Xcode 或 Command Line Tools 安装） |
| 最低系统 | Qt 6 要求 macOS 11+ |
| Xcode 版本 | Qt 6.5+ 要求 Xcode 14+，Qt 6.8 要求 Xcode 15+ |
| 架构 | Qt 6.2+ 支持 Apple Silicon (arm64)，可构建 Universal Binary |

macOS 没有编译器版本选择困扰——只有 Apple Clang，但注意 Xcode 版本和系统版本的对应关系。

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

### 编译器选择建议

| 场景 | 推荐 |
|------|------|
| Windows 个人学习 | Qt + MinGW（免装 VS，开箱即用） |
| Windows 正式开发 | Qt + MSVC 2022（装 VS Community，调试能力强） |
| macOS | 装 Xcode Command Line Tools，Qt 自动检测 |
| Linux | 装 GCC 11+ 和相关依赖库 |
| 跨平台部署 | 每个平台各编译一份，CI/CD 自动化构建 |
