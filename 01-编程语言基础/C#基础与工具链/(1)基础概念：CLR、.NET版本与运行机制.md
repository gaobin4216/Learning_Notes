# CLR、.NET 版本与运行机制

## 一、C# 语言概述

C#（读作 "C Sharp"）是微软于 2002 年发布的面向对象编程语言，运行在 .NET 平台上，由 Anders Hejlsberg 主导设计（他也是 TypeScript 和 Delphi 的设计者）。

### C# 的特点

| 特点 | 说明 |
|------|------|
| **面向对象** | 封装、继承、多态，一切皆对象 |
| **强类型** | 编译时类型检查，支持类型推断（var） |
| **自动内存管理** | 内置垃圾回收（GC），无需手动释放内存 |
| **跨平台** | .NET 6+ 支持 Windows、Linux、macOS |
| **现代语法** | async/await、LINQ、模式匹配、记录类型 |
| **丰富的生态** | NuGet 包管理、官方框架支持 |

### 应用领域

- 桌面应用（WPF、WinForms、MAUI）
- Web 应用（ASP.NET Core）
- 游戏开发（Unity 使用 C# 作为主要脚本语言）
- 云原生与微服务
- 移动应用（MAUI、Xamarin）
- IoT 与嵌入式

---

## 二、编译型 vs 解释型：C# 的混合模式

### 先理解两种极端

```
C/C++（纯编译型）：
源代码 → 编译器 → 机器码 → 直接在 CPU 上执行
                         ↑
                    编译一次，直接跑，速度最快
                    但换个系统（Windows→Linux）需要重新编译

Python（纯解释型）：
源代码 → 解释器逐行读取 → 边翻译边执行
                        ↑
                    不需要编译，跨平台
                    但每次运行都要翻译，速度较慢
```

### C# 的"两段式"编译

C# 既不像 C++ 那样直接编译成机器码，也不像 Python 那样逐行解释，而是采用**两段式编译**：

```
第一段（编译期，由 Roslyn 编译器完成）：
    C# 源码(.cs) → IL 中间语言(.dll/.exe)

第二段（运行期，由 CLR 运行时完成）：
    IL 中间语言 → JIT 即时编译 → 机器码 → CPU 执行
```

**为什么这样设计？** 好处是：

1. **跨平台**：IL 是平台无关的中间语言，同一份 .dll 可以在 Windows/Linux/macOS 上运行，CLR 负责把 IL 翻译成对应平台的机器码
2. **性能优化**：JIT 可以在运行时根据实际硬件环境（CPU 型号、指令集）做针对性优化
3. **语言互操作**：所有 .NET 语言（C#、F#、VB.NET）都编译成同一种 IL，可以互相调用

### 与其他语言的对比

| 特性 | C/C++ | Python | Java | C# |
|------|-------|--------|------|-----|
| **编译方式** | 直接编译为机器码 | 解释执行 | 编译为字节码 | 编译为 IL |
| **执行方式** | 直接运行 | 解释器逐行执行 | JVM 解释 + JIT | CLR 解释 + JIT |
| **跨平台** | 需重新编译 | 解释器跨平台 | 字节码跨平台 | IL 跨平台 |
| **运行速度** | 最快 | 较慢 | 接近 C/C++ | 接近 C/C++ |
| **源码保护** | 编译后难反编译 | 源码可直接查看 | 字节码可反编译 | IL 可反编译 |

---

## 三、什么是 IL（中间语言）？

IL（Intermediate Language），也叫 MSIL（Microsoft Intermediate Language）或 CIL（Common Intermediate Language），是 C# 编译后生成的"半成品"代码。

### IL 长什么样？

```csharp
// C# 源码
int a = 10;
int b = 20;
int c = a + b;
```

```il
// 编译后的 IL（简化示意）
ldc.i4.s   10        // 把整数 10 压入栈
stloc.0             // 存入局部变量 a
ldc.i4.s   20        // 把整数 20 压入栈
stloc.1             // 存入局部变量 b
ldloc.0             // 取出 a
ldloc.1             // 取出 b
add                 // 相加
stloc.2             // 结果存入 c
```

IL 是一种**基于栈的指令集**（类似 Java 字节码），人类可以读懂但不直接在 CPU 上执行，需要 CLR 的 JIT 编译器翻译成机器码。

### IL 的关键特征

| 特征 | 说明 |
|------|------|
| **平台无关** | 同一份 IL 可以在任何有 CLR 的平台上运行 |
| **基于栈** | 操作通过入栈/出栈完成，不直接操作寄存器 |
| **类型丰富** | 保留了完整的类型信息（比 Java 字节码信息多） |
| **可反编译** | 工具如 ILSpy、dnSpy 可以把 IL 还原为 C# 代码 |

> **注意**：IL 代码在 .dll/.exe 文件中，不是单独的 .il 文件。可以用 ILSpy 等工具查看。

---

## 四、CLR（公共语言运行时）

### 什么是 CLR？

CLR（Common Language Runtime）是 .NET 的运行时环境，负责执行 IL 代码。你可以把它理解为：

- **C# 的"虚拟机"**（类似 Java 的 JVM）
- **IL 代码的"翻译官"**：把 IL 翻译成当前机器能执行的机器码
- **程序的"管家"**：管理内存、线程、异常、安全等

### CLR 的架构

```
┌─────────────────────────────────────────────────────────┐
│                      CLR 架构                            │
├─────────────────────────────────────────────────────────┤
│  程序集加载器（Assembly Loader）                          │
│  → 加载 .dll / .exe 文件，解析其中的 IL 和元数据            │
├─────────────────────────────────────────────────────────┤
│  运行时数据区                                             │
│  ├── 托管堆（Managed Heap）：存放对象实例                   │
│  ├── 线程栈（Thread Stack）：存放局部变量和方法调用帧        │
│  └── GC 堆（Generation 0/1/2）：分代垃圾回收               │
├─────────────────────────────────────────────────────────┤
│  执行引擎                                                │
│  ├── JIT 编译器：把 IL 翻译成机器码                        │
│  ├── 垃圾回收器（GC）：自动回收不再使用的内存               │
│  ├── 类型系统：运行时类型检查，保证类型安全                  │
│  └── 异常处理：结构化异常处理（try/catch/finally）          │
└─────────────────────────────────────────────────────────┘
```

### JIT 编译器的工作方式

JIT（Just-In-Time，即时编译）不是一次性把所有 IL 都编译成机器码，而是**按需编译**：

```
程序启动
    ↓
方法第一次被调用 → JIT 把该方法的 IL 编译成机器码 → 执行
    ↓
方法第二次被调用 → 直接执行之前编译好的机器码（跳过 JIT）
    ↓
后续调用 → 都直接执行机器码
```

**为什么不用"提前全部编译"？**
- 程序可能有几万个方法，但启动时只用到一小部分，全部编译浪费时间
- JIT 可以根据运行时信息做优化（比如判断某个分支从未执行过）

**JIT 的优化策略：**
- **热点方法**频繁调用的方法，JIT 会做更深度的优化（类似 JVM 的 C1/C2 编译器）
- **内联**：把小方法的代码直接嵌入调用处，减少方法调用开销
- **死代码消除**：删除永远不会执行的代码分支

### CLR 的核心功能

| 功能 | 说明 | 类比 Java |
|------|------|-----------|
| **JIT 编译** | 运行时把 IL 编译为本机机器码 | JVM 的 JIT 编译器 |
| **垃圾回收（GC）** | 自动管理内存，分代回收 | JVM 的 GC |
| **类型安全** | 运行时类型检查，防止类型错误 | JVM 的类型检查 |
| **异常处理** | 结构化异常处理（try/catch/finally） | JVM 的异常机制 |
| **线程管理** | 线程池、任务并行库（TPL） | JVM 的线程池 |
| **安全** | 代码访问安全（CAS，已弃用） | JVM 的安全管理器 |

### CLR vs JVM 的关键区别

| 方面 | CLR | JVM |
|------|-----|-----|
| **设计目标** | 多语言平台（C#、F#、VB.NET） | 最初为 Java 设计，后支持多语言 |
| **值类型** | 支持（struct 是值类型，存在栈上） | 不支持（所有对象都在堆上） |
| **泛型实现** | 真泛型（IL 层面支持） | 类型擦除（运行时泛型信息丢失） |
| **属性** | 语言级支持（get/set 访问器） | 需要手写 getter/setter 方法 |
| **委托/事件** | 内置支持（delegate、event） | 需要接口或 Lambda 模拟 |

---

## 五、什么是"托管代码"与"非托管代码"？

这是理解 C# 运行机制的关键概念。

### 托管代码（Managed Code）

**托管代码**是指运行在 CLR 管理下的代码。C# 编写的代码默认就是托管代码。

"托管"意味着 CLR 为你管理了以下事情：

| CLR 管理的事项 | 你的代码不用操心 |
|----------------|------------------|
| **内存分配** | 不需要 malloc/free |
| **内存回收** | 不需要手动释放对象，GC 自动处理 |
| **类型安全** | 不会出现野指针、数组越界等内存错误 |
| **异常处理** | 统一的 try/catch/finally 机制 |
| **线程调度** | 线程池帮你管理线程生命周期 |

### 非托管代码（Unmanaged Code）

**非托管代码**是指不在 CLR 管理下的代码，比如：

- C/C++ 编写的本地库（.dll/.so）
- 操作系统 API（Windows API）
- COM 组件

C# 可以通过以下方式调用非托管代码：

```csharp
// P/Invoke：调用 Windows API
[DllImport("user32.dll")]
static extern int MessageBox(IntPtr hWnd, string text, string caption, int type);

// 调用 C/C++ 编写的本地库
[DllImport("mylib.dll")]
static extern int MyFunction(int param);
```

> **什么时候需要用非托管代码？** 性能关键路径（如游戏引擎）、调用操作系统底层功能、复用已有的 C/C++ 库。

---

## 六、GC（垃圾回收）机制

### 为什么需要 GC？

在 C/C++ 中，你需要手动管理内存：

```c
// C 风格（手动管理）
char* str = malloc(100);   // 分配内存
// ... 使用 str ...
free(str);                  // 必须手动释放，否则内存泄漏
```

在 C# 中，GC 自动帮你回收不再使用的内存：

```csharp
// C# 风格（自动管理）
string str = new string("hello");  // 分配在托管堆上
// ... 使用 str ...
// 不需要手动释放，GC 自动回收
```

### 分代回收

CLR 的 GC 采用**分代回收**策略，把对象分为三代：

```
┌─────────────────────────────────────────────────────────┐
│  GC 分代模型                                             │
├─────────────────────────────────────────────────────────┤
│  Generation 0（第 0 代）                                  │
│  → 新创建的对象                                           │
│  → 最频繁回收（每次 GC 都会检查 Gen 0）                    │
│  → 大多数对象"朝生夕灭"，很快就不再使用                    │
├─────────────────────────────────────────────────────────┤
│  Generation 1（第 1 代）                                  │
│  → 从 Gen 0 存活下来的对象                                │
│  → 中等频率回收                                           │
│  → 作为 Gen 0 和 Gen 2 之间的"缓冲区"                     │
├─────────────────────────────────────────────────────────┤
│  Generation 2（第 2 代）                                  │
│  → 从 Gen 1 存活下来的对象                                │
│  → 最少回收（通常是长期存在的对象）                        │
│  → 回收成本最高                                           │
└─────────────────────────────────────────────────────────┘
```

**为什么分代？** 经验观察：大多数对象生命周期很短（比如方法内的临时变量）。分代后，GC 可以优先回收"年轻代"，只在必要时才扫描"老年代"，大幅提升效率。

### GC 的触发时机

| 触发条件 | 说明 |
|----------|------|
| **Gen 0 已满** | 新对象分配时发现 Gen 0 空间不足 |
| **显式调用** | `GC.Collect()`（一般不推荐手动调用） |
| **内存压力** | 系统报告内存不足 |
| **Gen 2 回收** | 达到 Gen 2 的阈值 |

### GC 的两种模式

| 模式 | 说明 | 适用场景 |
|------|------|----------|
| **工作站模式** | 优先减少暂停时间 | 桌面应用、UI 程序 |
| **服务器模式** | 优先提高吞吐量 | Web 服务器、后台服务 |

```xml
<!-- 在 .csproj 中配置 -->
<PropertyGroup>
  <ServerGarbageCollection>true</ServerGarbageCollection>
</PropertyGroup>
```

---

## 七、.NET 框架体系：从混乱到统一

### .NET 的前世今生

.NET 的命名历史曾经非常混乱，理解这段历史有助于你看懂老代码和老教程：

```
时间线：
2002  .NET Framework 1.0    ← 初代，仅 Windows，不开源
  │                            代表技术：ASP.NET WebForms、WPF、WinForms
  │
2006  .NET Framework 3.5    ← 引入 LINQ、Lambda、WCF、WPF
  │
2010  .NET Framework 4.0    ← 引入 dynamic、TPL 并行库
  │
2016  .NET Core 1.0         ← 全新重写，跨平台，开源，模块化
  │                            不兼容老的 .NET Framework API
  │
2019  .NET Core 3.0         ← 加入 Windows Desktop（WPF/WinForms）
  │                            加入 Blazor（C# 写前端）
  │
2020  .NET 5                ← 统一：不再叫"Core"，直接叫 ".NET"
  │                            告诉全世界：以后只有一个 .NET
  │
2021  .NET 6（LTS）         ← Minimal API、热重载、C# 10
  │
2022  .NET 7                ← 性能大幅提升、C# 11
  │
2023  .NET 8（LTS）         ← 原生 AOT 编译、C# 12
  │
2024  .NET 9                ← 最新版本、C# 13
```

### 为什么会有 .NET Core？

.NET Framework 有一个致命缺陷：**只能在 Windows 上运行**。

2016 年前后，Linux 在服务器端的份额快速增长，微软意识到必须做一个跨平台版本。于是花了几年时间重写了整个运行时，这就是 .NET Core。

**.NET Core 相比 .NET Framework 的改进：**

| 方面 | .NET Framework | .NET Core / .NET 5+ |
|------|----------------|---------------------|
| **跨平台** | 仅 Windows | Windows、Linux、macOS |
| **开源** | 否 | 是（GitHub 开源） |
| **性能** | 一般 | 大幅提升（Kestrel、Span<T>） |
| **部署** | 需要预装 Framework | 支持独立部署（自带运行时） |
| **版本更新** | 绑定 Windows 更新 | 独立版本节奏 |
| **模块化** | 整体安装 | 按需引用 NuGet 包 |
| **容器化** | 不适合 Docker | 原生支持 Docker |

### 各版本对比

| 框架 | 平台 | 开源 | 状态 | 说明 |
|------|------|------|------|------|
| **.NET Framework** | 仅 Windows | 否 | 维护模式 | 存量项目在用，新项目不要选 |
| **.NET Core** | 跨平台 | 是 | 已合并为 .NET 5+ | 不需要单独学 |
| **.NET 5+** | 跨平台 | 是 | **当前主流** | 新项目必须选这个 |
| **Mono** | 跨平台 | 是 | 用于 Xamarin/Unity | Unity 游戏开发用的是 Mono |
| **.NET Standard** | — | — | 兼容性规范 | 不是运行时，是一个 API 规范 |

> **现在学什么？** 直接学 **.NET 8**（LTS）或 **.NET 9**（最新）。不要学 .NET Framework。

### .NET Standard 是什么？

你可能会看到 `netstandard2.0` 这样的目标框架，它不是运行时，而是一个**API 兼容性规范**：

```
.NET Standard 2.0 定义了一套 API 子集：
    ├── .NET Framework 4.6.1+ 支持
    ├── .NET Core 2.0+ 支持
    ├── .NET 5+ 支持
    ├── Mono 支持
    └── Xamarin 支持

作用：写一个类库，目标设为 netstandard2.0，
     就能在所有上面这些平台上运行。
```

**今天还需要 .NET Standard 吗？** 如果你的库需要同时支持 .NET Framework 和 .NET 5+，用它。否则直接用 `net8.0`。

### .NET 的组件关系

```
.NET SDK（软件开发工具包）
├── CLR（公共语言运行时）
│   ├── JIT 编译器：IL → 机器码
│   ├── 垃圾回收器（GC）：自动内存管理
│   ├── 类型系统：运行时类型检查
│   └── 异常处理：try/catch/finally
│
├── BCL（基础类库，Base Class Library）
│   ├── System.Collections（集合：List、Dictionary、Queue）
│   ├── System.IO（文件读写、流操作）
│   ├── System.Linq（LINQ 查询语法）
│   ├── System.Threading（多线程、锁、信号量）
│   ├── System.Net（HTTP 请求、Socket 通信）
│   ├── System.Text.Json（JSON 序列化）
│   ├── System.Data（ADO.NET 数据库访问）
│   └── System.ComponentModel（组件模型、数据绑定）
│
├── Roslyn（C#/VB.NET 编译器）
│   ├── 语法分析器：把源码解析成语法树
│   ├── 语义分析器：类型检查、符号解析
│   └── IL 代码生成器：输出 .dll/.exe
│
├── dotnet CLI（命令行工具）
│   ├── dotnet new：创建项目（从模板生成）
│   ├── dotnet build：编译项目（调用 MSBuild）
│   ├── dotnet run：编译并运行
│   ├── dotnet test：运行单元测试
│   ├── dotnet publish：发布部署包
│   ├── dotnet add package：添加 NuGet 包
│   ├── dotnet tool install：安装全局工具
│   └── dotnet ef：Entity Framework 迁移工具
│
├── NuGet（包管理器）
│   ├── 从 nuget.org 下载第三方库
│   ├── 管理包的版本和依赖关系
│   └── 缓存在 ~/.nuget/packages 目录
│
└── MSBuild（构建引擎）
    ├── 解析 .csproj 项目文件
    ├── 执行编译流程（还原→编译→链接→输出）
    └── 支持自定义构建任务
```

### SDK vs Runtime：你到底装了什么？

很多初学者分不清 SDK 和 Runtime 的区别：

```
.NET SDK（开发者安装）
├── .NET Runtime（运行时，用户也可以单独装）
│   ├── CLR（执行 IL 代码）
│   └── BCL（基础类库）
├── Roslyn 编译器（把 .cs 编译成 IL）
├── dotnet CLI（命令行工具）
├── NuGet（包管理）
└── MSBuild（构建引擎）

.NET Runtime（普通用户安装）
├── CLR（执行 IL 代码）
└── BCL（基础类库）
```

**简单理解：**
- **Runtime**：只能运行 .NET 程序，适合部署到服务器
- **SDK**：能开发 + 运行 .NET 程序，开发者必装

```bash
# 查看你装了什么
dotnet --list-sdks      # 列出已安装的 SDK
dotnet --list-runtimes  # 列出已安装的运行时
```

### ASP.NET Core 与 Entity Framework Core

.NET 平台有两个重要的官方框架：

```
.NET 基础平台
├── ASP.NET Core（Web 框架）
│   ├── MVC（Model-View-Controller）
│   ├── Web API（RESTful API）
│   ├── Razor Pages（页面模型）
│   ├── Blazor（C# 写前端，WebAssembly）
│   ├── SignalR（实时通信）
│   ├── Minimal API（轻量 API，.NET 6+）
│   └── gRPC（高性能 RPC）
│
└── Entity Framework Core（ORM 框架）
    ├── Code First（先写 C# 类，自动生成数据库表）
    ├── Database First（先有数据库，自动生成 C# 类）
    ├── LINQ to Entities（用 LINQ 查询数据库）
    ├── 迁移（Migration）：版本化数据库变更
    └── 支持 SQL Server、PostgreSQL、MySQL、SQLite
```

---

## 八、版本演进

### .NET 版本历史

| 版本 | 发布年份 | 重要特性 |
|------|----------|----------|
| **.NET Framework 1.0** | 2002 | 首个版本，CLR 1.0 |
| **.NET Framework 2.0** | 2005 | 泛型、Nullable 类型 |
| **.NET Framework 3.5** | 2007 | LINQ、Lambda 表达式、扩展方法 |
| **.NET Framework 4.0** | 2010 | 动态类型（dynamic）、并行任务库（TPL） |
| **.NET Core 1.0** | 2016 | 跨平台、开源、模块化 |
| **.NET Core 3.0** | 2019 | Windows Desktop（WPF/WinForms）、Blazor |
| **.NET 5** | 2020 | 统一平台，去掉"Core"后缀 |
| **.NET 6（LTS）** | 2021 | Minimal API、热重载、C# 10 |
| **.NET 7** | 2022 | 性能提升、C# 11 |
| **.NET 8（LTS）** | 2023 | 原生 AOT、性能大幅提升、C# 12 |
| **.NET 9** | 2024 | 最新版本、C# 13 |

> **LTS（Long-Term Support）** 版本提供 3 年支持，生产环境推荐使用 LTS 版本。

### C# 语言版本与 .NET 版本的对应

| C# 版本 | 对应 .NET 版本 | 重要特性 |
|---------|----------------|----------|
| C# 1.0 | .NET Framework 1.0 | 基础语法、类、接口 |
| C# 3.0 | .NET Framework 3.5 | LINQ、Lambda、扩展方法 |
| C# 5.0 | .NET Framework 4.5 | async/await |
| C# 7.0 | .NET Core 1.0+ | 模式匹配、元组 |
| C# 8.0 | .NET Core 3.0+ | 可空引用类型、switch 表达式 |
| C# 9.0 | .NET 5 | record 类型、顶层语句 |
| C# 10.0 | .NET 6 | 全局 using、文件范围命名空间 |
| C# 11.0 | .NET 7 | 原始字符串字面量、泛型数学 |
| C# 12.0 | .NET 8 | 主构造函数、集合表达式 |
| C# 13.0 | .NET 9 | params 集合、lock 新语义 |

---

## 九、C# 的执行方式

### 1. 命令行编译运行（最常用）

```bash
# 创建控制台项目
dotnet new console -n HelloApp

# 进入项目目录
cd HelloApp

# 编译并运行
dotnet run

# 输出
Hello, World!
```

### 2. 交互式工具（C# REPL）

```bash
# 安装 dotnet-script 工具
dotnet tool install -g dotnet-script

# 启动 REPL（交互式解释器）
dotnet-script

> Console.WriteLine("Hello!")
Hello!
> var x = 10 + 20
> Console.WriteLine(x)
30
```

### 3. 单文件脚本运行

```csharp
// hello.csx（C# 脚本文件）
Console.WriteLine("Hello from script!");
```

```bash
dotnet-script hello.csx
```

---

## 十、开发环境概览

| 工具 | 定位 | 详见 |
|------|------|------|
| **Visual Studio** | 最强大的 C# IDE（Windows） | → (2) 开发环境选择 |
| **VS Code** | 轻量级编辑器 + C# Dev Kit 插件 | → (2) 开发环境选择 |
| **JetBrains Rider** | 跨平台 C# IDE | → (2) 开发环境选择 |
| **NuGet** | 包管理 | → (3) 包管理与项目构建 |
| **MSBuild** | 项目构建 | → (3) 包管理与项目构建 |
