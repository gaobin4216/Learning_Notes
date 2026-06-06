# WinUI3 与 Windows 现代开发

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

## 基础概念：WinRT、Windows SDK、Windows App SDK

这三者的关系是理解 Windows 现代开发的关键：

```
Windows SDK（系统自带）
├── Win32 API        ← 传统桌面核心
├── WinRT API        ← 现代系统 API
└── 工具和头文件

         ↑ 上层封装

Windows App SDK（NuGet 独立发布）
├── WinUI 3          ← 现代 UI 框架
├── 通知、窗口管理、生命周期等增强 API
└── 遵循 WinRT 规范，解耦 OS

         ↑ 语言调用

C#（.NET 投影）或 C++/WinRT（直接调用）
```

### 一、WinRT（Windows Runtime）

WinRT 是理解 Windows 现代开发的基础，先搞懂它，后面的 Windows App SDK 才能理解。

**核心逻辑**
* 不是传统意义上的 "运行时环境"，而是一套语言无关的应用二进制接口（ABI），本质是基于 COM 扩展的 "API 交付系统"。
* 底层依赖 Win32 API，用 C++ 实现，提供比传统 Win32 更现代、更安全、更统一的系统调用能力。

**在现代 Windows 里的定位：**
- Win32：传统桌面 API，最底层、最强大、兼容性最好
- WinRT：现代系统 API，更安全、更现代、跨语言、沙箱友好

同一套 Windows 生态里的两层/两类 API。
不是二选一：WinUI 3 桌面应用通常同时用 Win32 和 WinRT。

**核心目标**：让同一套 API 可被 C++/WinRT、C#、VB.NET、JavaScript/TypeScript、Rust、Python 等多种语言调用。API 定义存储在 `.winmd`（Windows Metadata）文件中，不同语言通过各自投影（Projection）访问同一套 API，行为一致。

> **重点**：WinRT 和 Win32 并列，共同组成完整的 Windows SDK。不是简单封装，而是一套新的 API 体系。

---

### 二、Windows App SDK

理解了 WinRT 之后，Windows App SDK 就好理解了——它是基于 WinRT 之上的增强层。

Windows App SDK（以前代号为 Project Reunion）是微软推出的一套现代化的开发工具和 API 集合，你可以把它理解为 Windows 开发的"现代化插件包"。它允许开发者在不依赖特定操作系统版本的情况下，为 Windows 10 和 Windows 11 设备添加最新的功能和界面。

**核心特点：**
- 一套统一的 API：无论你是使用 WinUI 3、WPF 还是 Windows Forms 开发，都可以通过它来调用现代化的 Windows 功能（如通知、窗口管理、应用生命周期控制等）。
- 与操作系统解耦：传统的 Windows SDK 是绑定在操作系统里的，而 Windows App SDK 通过 NuGet 包的形式发布，可以独立于 Windows 系统更新。
- 包含 WinUI 3：内置了 WinUI 3，这是微软推荐的最新原生 UI 框架，用于构建具有 Fluent Design（流畅设计）风格的现代化界面。

| 优势 | 说明 |
|------|------|
| 跨版本兼容 | 应用可运行在 Windows 10 (1809) 到 Windows 11，无需为不同系统写两套代码 |
| 更新频率快 | 不随 Windows 系统每年更新一次，而是每年发布多次，新功能马上用 |
| 现代化 UI | 开箱即用支持 WinUI 3，圆角、阴影、亚克力材质等现代视觉效果 |
| 兼容旧项目 | 可集成到现有 WPF 或 Windows Forms 项目中，帮助老应用现代化改造 |

**包含的功能组件：** WinUI 3、应用生命周期管理、Toast/推送通知、窗口管理、资源管理 (MRT Core)、文本渲染 (DWriteCore)。

**本质：WinRT 的增强层**

Windows App SDK 是一套基于 WinRT 规范、构建在系统 WinRT 之上的「现代增强型 API 库 + 框架集合」。

**三层架构：**
1. **底层：系统 WinRT（Windows SDK 里的）** — 系统自带，负责和内核打交道
2. **上层：Windows App SDK** — 复用、扩展系统 WinRT，提供更现代、更统一的桌面 API，自带 WinUI 3，独立更新，不绑死系统版本
3. **语言层** — C#：.NET 投影封装；C++/WinRT：直接调用

**三个关键点：**
1. 它是 WinRT 的 "扩展集"，遵循 WinRT ABI / 元数据规范，不是新架构。把系统 WinRT 里分散/难用的能力，做成统一、易用的 API。自带 WinUI 3（替代 UWP XAML）。
2. 解耦 OS、独立更新：NuGet 直接更 App SDK，新功能马上用，1套代码兼容多版本 Windows（1809+）。
3. 语言调用和之前一样：C# 通过 .NET 做投影封装，C++/WinRT 头文件直接调，底层还是走系统 WinRT/Windows SDK。

**一句话总结：Windows App SDK = 基于 WinRT、独立于 OS、带 WinUI 3 的现代桌面统一 API 层。**

---

### 三、Windows App SDK 与 Windows SDK 区别

| 对比 | Windows SDK（系统 SDK） | Windows App SDK（应用 SDK） |
|------|------------------------|---------------------------|
| 定位 | 系统自带、随 Windows 更新 | 独立发布、NuGet 安装 |
| 功能 | 底层 WinRT/Win32 API | 在 SDK 之上，统一现代 API（含 WinUI 3） |
| 兼容性 | 绑定 OS 版本 | 兼容 Win10 1809+/Win11，不绑定 OS |

**Windows SDK 是地基，Windows App SDK 是上面的现代化精装修包。**

**依赖关系（最关键的区别）：**
- Windows SDK 与 OS 强耦合：用 Win11 特有 API → 必须装对应版本 SDK → 程序只能跑在 Win11
- Windows App SDK 与 OS 解耦：NuGet 发布，一年多次更新，新 API 也能在旧版 Win10 上运行

**不是"取代"，而是"互补"：** 用 Windows App SDK 开发时，底层依然依赖 Windows SDK。画界面、发通知用 App SDK；直接操作硬件、用特定 DirectX 功能，仍需调用 Windows SDK 原生 API。

---

### 四、语言调用方式

✅ Windows App SDK = 对系统 WinRT 的「封装 + 增强 + 兼容 + 统一」
✅ Windows App SDK 就是：更好用、更强大、桌面能随便用的 WinRT

**C++/WinRT、C#/.NET 都是用自己的方式调用这套统一的 WinRT API，只是调用方式不一样。**

**C#/.NET：**
```
C# 代码 → .NET 投影封装（自动生成 C# 包装类）→ Windows App SDK API → 系统 WinRT → Windows 底层
```
.NET 做了一层包装/投影（Projection），把 WinRT 转成 C# 熟悉的类、接口、异步方法。本质还是调用同一套系统 API。

*简单理解：*
- 系统 WinRT = 电脑自带的基础接口
- Windows App SDK = 在基础接口上做的高级功能套件
- .NET 投影 = 一个万能翻译器，既能翻译系统 WinRT，也能翻译 Windows App SDK

**C++/WinRT：**
```
C++/WinRT 代码 → 直接调用（头文件库，无包装）→ Windows App SDK API → 系统 WinRT → Windows 内核
```
C++/WinRT 的本质：不是运行时库，而是一套现代 C++ 语法投影层（Projection）。把 WinRT 的 COM 接口转换成干净、现代、类型安全的 C++ 代码。所有转换逻辑、智能指针、模板、包装类全部在头文件里实现。

**最终结论（你可以牢牢记住）**
- ✅ C# 不直接碰 WinRT / App SDK，.NET 负责翻译
- ✅ C++/WinRT 直接调用，效率更高
- ✅ Windows App SDK 是增强库，两种语言的调用逻辑不变，只是多了一层现代增强 API

---

## 附录：Microsoft Visual C++ Redistributable

**是什么**

**Microsoft Visual C++ Redistributable（简称 VC++ 运行库） 是微软提供的一组运行时 DLL 库，专门用来让用 Visual C++（MSVC） 开发的程序（包括 MFC、C++ 游戏、桌面软件、驱动工具等），在没装 Visual Studio 的普通电脑上正常运行**

- 本质：C++ 运行时 + 框架库的集合，以 DLL 形式提供
- 包含核心库：CRT（内存管理、字符串、IO）、STL（vector、string、map）、MFC/ATL、OpenMP、GDI+ 等
- 作用：共享运行库，让多个程序共用一套 DLL，不用每个软件都自带一份

**为什么电脑里会有好几个版本**

- 版本不互相替代：2005、2008、2010、2012、2013、2015–2022 是不同主版本，不能互相覆盖
- 2015–2022 是累积更新：装最新版（如 2022）就包含 2015/2017/2019 的所有功能
- 架构要匹配：x86（32 位）、x64（64 位）、ARM64 要分开装，64 位系统通常同时需要 x86 和 x64

**它们是 Windows 生态的基石，虽然看着乱，但为了保证你电脑里各种新老软件都能和平共处，请保留它们，不要动。**

**为什么需要它们？（翻译官的作用）**
很多软件是用 Visual C++ 开发的，运行时需要调用基础代码库。微软把这些做成了公共组件。如果不装，就会报错（比如经典的"找不到 msvcp140.dll"）。

**为什么这么多不同年份版本？（版本不兼容）**
老软件用老零件（2012 年的游戏只认 2012 版），新软件用新零件，互不替代。你不能指望用 2022 版的库去运行 2012 年的程序。
