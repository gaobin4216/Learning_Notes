# WinUI3

## 吐槽

**他妈的，为什么不直接叫Windows App UI，这样就和windows app sdk一致了，也好理解一个UI库，一个SDK工具集合，SDK中包含这个UI，真傻逼，就把WinUI3当成Windows App UI就行。**

WinUI 3 不是纯 Win32。它依赖 Windows App SDK、WinRT、XAML 框架等运行时。

---

## 介绍

WinUI 3 是微软推出的、用于构建 Windows 桌面应用的现代原生 UI 框架，是 Windows App SDK 的核心组件，也是 Windows 11 系统界面的底层技术。

**WinUI 3 就是 Windows 桌面应用的 "现代 UI 标准"，让你用最新技术写出和系统一样好看、流畅的原生界面**

**核心定位与本质**
* 它是新一代 Windows 原生界面引擎，用来替代老旧的 Win32、MFC、WPF、WinForm、UWP 等 UI 技术栈。
* 最大突破：把 UI 层从 Windows 系统中解耦，以 NuGet 包独立分发、独立更新，不再依赖系统升级。
* 命名空间：Microsoft.UI.Xaml（区别于旧 UWP 的 Windows.UI.Xaml）。
* 支持语言：C#（.NET 6+）、C++，用 XAML 写界面、代码写逻辑。

---

## 使用说明

安装VS2022以上，安装C#和windows应用开发

新建winui项目，安装调试成功后右键项目发布成exe

**注意**
安装Windows App SDK运行时，需要同时在项目中禁止 Windows自动初始化。很难用，发布的exe总是跑不起来，垃圾，我的评价是，应该是好东西，但是不会用的，垃圾，不如QT+Cmake一根

---

# 基础概念：WinRT、Windows SDK、Windows App SDK

## 一、WinRT（Windows Runtime）

WinRT 是理解 Windows 现代开发的基础，先搞懂它，后面的 Windows App SDK 才能理解。

### 核心逻辑

* 不是传统意义上的 "运行时环境"，而是一套语言无关的应用二进制接口（ABI），本质是基于 COM 扩展的 "API 交付系统"。
* 底层依赖 Win32 API，用 C++ 实现，提供比传统 Win32 更现代、更安全、更统一的系统调用能力。

**在现代 Windows 里的定位：**
- Win32：传统桌面 API，最底层、最强大、兼容性最好
- WinRT：现代系统 API，更安全、更现代、跨语言、沙箱友好

同一套 Windows 生态里的两层/两类 API。
不是二选一：WinUI 3 桌面应用通常同时用 Win32 和 WinRT。

**Windows SDK 包含两大部分：**
- 传统 Win32 部分：C 风格函数（CreateWindow、WriteFile 等），头文件：windows.h 等
- 现代 WinRT 部分：面向对象 API（Windows.Storage、Windows.UI 等），元数据：.winmd，语言投影：C++/WinRT、C#/WinRT 等
 
Windows SDK
├─ Win32 API
│  ├─ 传统桌面程序核心
│  ├─ HWND、消息循环、进程、线程、文件、注册表
│  └─ C/C++ 风格 API，历史最久，能力最全
│
├─ WinRT API
│  ├─ 现代 Windows Runtime API
│  ├─ 通知、设备、蓝牙、应用生命周期、现代权限
│  └─ 可被 C++、C#、JS 等语言投影调用
│
└─ 其他工具和头文件
   ├─ 编译/链接支持
   ├─ Manifest、资源、调试工具
   └─ 系统库、IDL、元数据等
   
**核心目标**：让同一套 API 可被 C++/WinRT、C#、VB.NET、JavaScript/TypeScript、Rust、Python 等多种语言调用，实现跨设备、跨架构（x86/x64/ARM）的应用开发。

API 定义存储在 .winmd（Windows Metadata）文件中，类似 .NET 元数据，支持跨语言无缝调用。不同语言通过各自投影（Projection）访问同一套 WinRT API，行为一致。

> **重点**：WinRT 是 Windows 推出的一套现代化、面向对象、跨语言的新 API 体系，底层依赖 Win32，但不是简单封装；它和 Win32 并列，共同组成完整的 Windows SDK。

---

## 二、Windows App SDK

理解了 WinRT 之后，Windows App SDK 就好理解了——它是基于 WinRT 之上的增强层。

### 是什么

Windows App SDK（以前代号为 Project Reunion）是微软推出的一套现代化的开发工具和 API 集合，旨在帮助开发者构建美观、高性能且功能强大的 Windows 桌面应用。简单来说，你可以把它理解为 Windows 开发的"现代化插件包"。它允许开发者在不依赖特定操作系统版本的情况下，为 Windows 10 和 Windows 11 设备添加最新的功能和界面。

**核心特点：**
- 一套统一的 API：无论你是使用 WinUI 3、WPF 还是 Windows Forms 开发，都可以通过它来调用现代化的 Windows 功能（如通知、窗口管理、应用生命周期控制等）。
- 与操作系统解耦：传统的 Windows SDK 是绑定在操作系统里的，而 Windows App SDK 通过 NuGet 包的形式发布，可以独立于 Windows 系统更新。
- 包含 WinUI 3：内置了 WinUI 3，这是微软推荐的最新原生 UI 框架，用于构建具有 Fluent Design（流畅设计）风格的现代化界面。

| 优势 | 说明 |
| :--- | :--- |
| 跨版本兼容 | 你的应用可以运行在 Windows 10 (1809) 到 Windows 11 的所有设备上，且能保持一致的体验，无需为不同系统写两套代码。 |
| 更新频率快 | 它不随 Windows 系统每年更新一次，而是每年发布多次。这意味着你可以更快地用上微软的新功能，不用等系统大版本升级。 |
| 现代化 UI | 开箱即用地支持 WinUI 3，让你轻松打造具有圆角、阴影、亚克力材质等现代视觉效果的界面。 |
| 兼容旧项目 | 它不仅用于新项目，还可以集成到现有的 WPF 或 Windows Forms 项目中，帮助老应用实现现代化改造。 |

**包含的功能组件：**
- WinUI 3：用于构建用户界面的核心框架。
- 应用生命周期管理：控制应用是单实例运行还是多实例运行，处理激活方式等。
- 通知系统：支持现代化的 Toast 通知和推送通知。
- 窗口管理：提供更灵活的窗口创建和调整功能。
- 资源管理 (MRT Core)：更好地管理多语言字符串、图片等资源。
- 文本渲染 (DWriteCore)：提供高质量的文本排版和渲染。

### 本质：WinRT 的增强层

Windows App SDK 是一套基于 WinRT 规范、构建在系统 WinRT 之上的「现代增强型 API 库 + 框架集合」。

**三层架构：**
1. **底层：系统 WinRT（Windows SDK 里的）**
   系统自带，负责和内核打交道。
2. **上层：Windows App SDK**
   复用、扩展系统 WinRT，提供更现代、更统一、更适合桌面的 API，自带 WinUI 3（现代 UI），独立更新，不绑死系统版本。
3. **语言层**
   C#：.NET 投影封装
   C++/WinRT：直接调用

**简单理解：**
- WinRT 是接口标准 + 系统底层能力
- Windows App SDK 是基于这个标准做的一套 "超级功能库"
- 它不是简单封装，而是扩展、增强、统一、现代化了 WinRT
- 你用 C# 调用它，和调用系统 WinRT 的逻辑一模一样

**三个关键点：**
1. 它是 WinRT 的 "扩展集"，遵循 WinRT ABI / 元数据规范，不是新架构。把系统 WinRT 里分散/难用的能力，做成统一、易用的 API（如窗口管理、通知、启动）。自带 WinUI 3（现代 UI 框架，替代 UWP XAML）。
2. 解耦 OS、独立更新：不用等 Windows 大更，NuGet 直接更 App SDK，新功能马上用。1套代码兼容多版本 Windows（1809+）。
3. 语言调用和之前一样：C# 通过 .NET 做投影封装，直接调 App SDK 的 WinRT API；C++/WinRT 头文件直接调，几乎无开销。底层还是走系统 WinRT/Windows SDK。

**一句话总结：Windows App SDK = 基于 WinRT、独立于 OS、带 WinUI 3 的现代桌面统一 API 层，C#/.NET、C++/WinRT 调用逻辑不变，只是多了一层现代增强 API。**

---

## 三、Windows App SDK 与 Windows SDK 区别

| 对比 | Windows SDK（系统 SDK） | Windows App SDK（应用 SDK） |
| :--- | :--- | :--- |
| 定位 | 系统自带、随 Windows 更新 | 独立发布、NuGet 安装 |
| 功能 | 提供底层 WinRT/Win32 API | 在 Windows SDK 之上，提供统一现代 API（含 WinUI 3） |
| 兼容性 | 绑定 OS 版本 | 兼容 Win10 1809+/Win11，不绑定 OS 版本 |

**Windows SDK 是地基，而 Windows App SDK 是建立在上面的现代化精装修包。**

### 1. 依赖关系与更新频率（最关键的区别）

Windows SDK 是与操作系统强耦合的。如果你想用 Windows 11 特有的某个 API，你必须安装对应版本的 SDK，而且你的程序只能在 Windows 11 上运行（或者需要写复杂的兼容代码）。它的更新通常伴随着 Windows 大版本更新。

Windows App SDK 是与操作系统解耦的。它通过 NuGet 包的形式发布。这意味着微软可以一年发布多次更新，你只需更新 NuGet 包就能获得新功能，而不需要用户升级操作系统。它通过一层"抽象"，让新 API 也能在旧版 Windows 10 上运行。

### 2. 功能覆盖范围

Windows SDK 是"大而全"的底层工具箱。它包含了 Windows 诞生以来积累的所有底层接口（Win32 API）、COM 组件、DirectX 图形接口等。它是所有 Windows 程序运行的基石。

Windows App SDK 是"精而美"的现代化工具箱。它专注于应用开发体验。它包含了 WinUI 3（现代化 UI 框架）、现代化的通知系统、窗口管理 API、以及资源管理系统。它把复杂的底层逻辑封装成了更好用的接口。

### 3. 并不是"取代"关系，而是"互补"

这是一个常见的误区。Windows App SDK 不会取代 Windows SDK。

- 互补共存：当你使用 Windows App SDK 开发应用时，你的项目底层依然依赖 Windows SDK。
- 实际开发场景：你会用 Windows App SDK 来画界面（WinUI 3）、发通知、管理窗口。但在某些极端底层的需求下（比如直接操作硬件、使用特定的 DirectX 功能），你依然需要调用 Windows SDK 提供的原生 API。

---

## 四、语言调用方式
✅ Windows App SDK = 对系统 WinRT 的「封装 + 增强 + 兼容 + 统一」
✅ Windows App SDK 就是：更好用、更强大、桌面能随便用的 WinRT

**C++/WinRT、C#/.NET 都是用自己的方式调用这套统一的 WinRT API，只是调用方式不一样。**

### C++：通过 C++/WinRT 直接调用

C++/WinRT 是头文件库，让 C++ 直接、原生调用 WinRT API，几乎没有额外层，效率很高。

C++/WinRT 的本质：它不是运行时库，而是一套现代 C++ 语法投影层（Projection）。它的作用只有一个：把 Windows 运行时（WinRT）的 COM 接口，转换成干净、现代、类型安全的 C++ 代码。所有转换逻辑、智能指针、模板、包装类……全部在头文件里实现。

### C#：通过 .NET 层调用

.NET 自带了对 WinRT 的绑定/包装，C# 写的代码 → .NET 层 → 直接调用 WinRT。本质还是 C# 直接用 WinRT API，只是走了 .NET 的封装，.NET 做了一层包装/投影（Projection），把 WinRT 转成 C# 熟悉的类、接口、异步方法。C# 调用的是 .NET 封装后的 WinRT，但底层还是同一套系统 API。

### 调用关系图

**C#/.NET：**
```
C# 代码
   ↓（你写的代码）
.NET 投影封装
   ↓（.NET 自动生成：把 WinRT/App SDK 转成 C# 类）
Windows App SDK API（基于 WinRT 规范）
   ↓（封装、增强功能、WinUI3、统一桌面 API）
系统 WinRT API（Windows SDK）
   ↓（系统原生接口）
Windows 系统底层
```

Windows App SDK 本身就是一套遵循 WinRT 规范的 API，所以 .NET 对它的处理方式，和对系统 WinRT 完全一样：自动生成一层 C# 包装，让你直接用。

*简单理解：*
- 系统 WinRT = 电脑自带的基础接口
- Windows App SDK = 在基础接口上做的高级功能套件
- .NET 投影 = 一个万能翻译器，既能翻译系统 WinRT，也能翻译 Windows App SDK

**最终结论（你可以牢牢记住）**
- ✅ C# 不直接碰 WinRT / App SDK
- ✅ .NET 负责把它们全部翻译成 C# 能看懂的代码
- ✅ Windows App SDK 是增强库，.NET 照样给它套封装

**C++/WinRT：**
```
C++/WinRT 代码
   ↓（直接调用，无包装）
Windows App SDK API
   ↓（App SDK 内部调用/封装了）
系统 WinRT API（Windows SDK）
   ↓
Windows 系统内核
```

---

# 附录：Microsoft Visual C++ Redistributable

## 是什么

**Microsoft Visual C++ Redistributable（简称 VC++ 运行库） 是微软提供的一组运行时 DLL 库，专门用来让用 Visual C++（MSVC） 开发的程序（包括 MFC、C++ 游戏、桌面软件、驱动工具等），在没装 Visual Studio 的普通电脑上正常运行**

- 本质：C++ 运行时 + 框架库的集合，以 DLL 形式提供
- 包含核心库：
  - CRT（C Runtime）：内存管理、字符串、IO、异常等基础能力
  - STL（C++ 标准库）：vector、string、map 等容器与算法
  - MFC/ATL：MFC 框架依赖的核心库
  - OpenMP、GDI+、安全/调试支持等
- 作用：共享运行库，让多个程序共用一套 DLL，不用每个软件都自带一份

## 为什么电脑里会有好几个版本

- 版本不互相替代：2005、2008、2010、2012、2013、2015–2022 是不同主版本，不能互相覆盖
- 2015–2022 是累积更新：装最新版（如 2022）就包含 2015/2017/2019 的所有功能
- 架构要匹配：x86（32 位）、x64（64 位）、ARM64 要分开装，64 位系统通常同时需要 x86 和 x64

## 作用

**它们是 Windows 生态的基石，虽然看着乱，但为了保证你电脑里各种新老软件都能和平共处，请保留它们，不要动。**

**1. 为什么需要它们？（翻译官的作用）**
很多软件（比如游戏、Photoshop、Office）是用微软的 Visual C++ 工具开发的。这些软件在运行时，需要调用一些基础的代码库（比如数学计算、文件读写功能）。为了不把这些基础代码重复打包在每个软件里，微软把这些基础代码做成了公共组件，也就是 Redistributable 包。如果不安装：当你打开软件时，系统找不到这些基础功能，就会报错（比如经典的"找不到 msvcp140.dll"）。

**2. 为什么会有这么多不同的年份版本？（版本不兼容）**
你可能会问："装了最新的 2022 版，为什么还需要 2012 或 2015 版？"
这是因为软件开发的"代沟"：
- 老软件用老零件：一个在 2012 年开发的游戏，它是基于当年的 C++ 2012 标准构建的。它只认识 2012 版的"翻译官"。
- 新软件用新零件：2024 年开发的软件，可能依赖最新的 C++ 2022 组件。
- 互不替代：微软的 C++ 运行库不是完全向下兼容的。你不能指望用 2022 版的库去运行 2012 年的程序。
