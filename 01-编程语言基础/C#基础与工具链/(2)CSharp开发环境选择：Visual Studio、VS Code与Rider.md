# C# 开发环境选择：Visual Studio、VS Code 与 Rider

## 一、什么是 IDE？为什么需要它？

**IDE（Integrated Development Environment，集成开发环境）** 是把代码编辑、编译、调试、版本控制等功能集成在一起的软件。你可以用记事本写 C# 代码，但 IDE 能让你的开发效率提升数倍。

### IDE 提供的核心能力

| 能力 | 没有 IDE 时 | 有 IDE 时 |
|------|-------------|-----------|
| **代码补全** | 手动敲每个字符 | 智能提示，Tab 确认 |
| **错误检查** | 编译后才知道哪里错了 | 写代码时实时标红 |
| **重构** | 手动查找替换 | 一键重命名、提取方法 |
| **调试** | 加 Console.WriteLine | 断点、单步、查看变量 |
| **项目管理** | 手动管理文件和引用 | 可视化管理依赖和配置 |
| **版本控制** | 命令行 git 操作 | 可视化 diff、提交、分支 |

### 三种工具的定位

| 工具 | 一句话定位 | 适合人群 |
|------|-----------|----------|
| **Visual Studio** | 最强大的 C# IDE | .NET 开发者（强烈推荐） |
| **VS Code** | 轻量级编辑器 + 插件 | 轻量开发、跨平台开发者 |
| **JetBrains Rider** | 跨平台 C# IDE | 跨平台开发、JetBrains 用户 |

---

## 二、Visual Studio：最强大的 C# IDE

### 什么是 Visual Studio？

Visual Studio（简称 VS）是微软官方的 IDE，专门为 .NET 开发设计。它是 C# 生态中最成熟、功能最完整的开发工具。

### 版本对比

| 版本 | 价格 | 特点 |
|------|------|------|
| **Community** | 免费 | 个人/小团队，功能完整 |
| **Professional** | 付费 | 企业开发，团队协作 |
| **Enterprise** | 付费 | 高级调试、测试工具、代码覆盖率 |

> **学生优惠**：学生可通过 [Visual Studio Dev Essentials](https://visualstudio.microsoft.com/dev-essentials/) 免费使用。

> **选择建议**：初学者和个人开发者用 Community 就够了，功能和 Enterprise 几乎一样。

### 核心功能

| 功能 | 说明 |
|------|------|
| **智能代码补全** | IntelliSense，基于上下文的精准补全，能补全变量名、方法名、参数 |
| **重构工具** | 重命名、提取方法、内联变量、移动类到其他文件 |
| **调试器** | 条件断点、即时窗口、远程调试、内存查看、线程切换 |
| **版本控制** | Git 集成，可视化 diff、提交历史、分支管理 |
| **数据库工具** | SQL Server 集成，可以直接在 VS 里写 SQL、查看表结构 |
| **框架支持** | ASP.NET、WPF、WinForms、MAUI、Unity |
| **NuGet** | 深度集成包管理，图形化安装/更新/卸载 |
| **热重载** | 修改代码即时生效，不需要重启程序 |
| **诊断工具** | CPU 使用率、内存占用、事件日志实时监控 |

### 安装与配置

#### 1. 安装 Visual Studio

访问 [https://visualstudio.microsoft.com/](https://visualstudio.microsoft.com/) 下载安装。

#### 2. 选择工作负载

**工作负载（Workload）** 是 VS 的安装组件包，你不需要安装所有工作负载，只选自己需要的：

| 工作负载 | 用途 | 包含的 SDK/框架 |
|----------|------|-----------------|
| **.NET 桌面开发** | WPF、WinForms | Windows Forms、WPF 模板 |
| **ASP.NET 和 Web 开发** | Web 应用、API | ASP.NET Core、Node.js |
| **使用 Unity 的游戏开发** | Unity 游戏 | Unity 编辑器集成 |
| **.NET Multi-platform App UI** | 跨平台移动/桌面应用 | MAUI、Xamarin |

> **建议**：初学者至少装 **.NET 桌面开发** 和 **ASP.NET 和 Web 开发** 两个工作负载。

#### 3. 配置 .NET SDK

`Tools → Options → Projects and Solutions → .NET Core`：
- 指定 .NET SDK 路径
- 配置默认目标框架

### 解决方案（Solution）与项目（Project）的关系

这是 VS 中最重要的概念之一：

```
解决方案（.sln 文件）
│   → 相当于一个"文件夹"，把多个相关项目组织在一起
│   → 一个解决方案可以包含多个项目
│
├── 项目1（.csproj 文件）
│   → 相当于一个"工程"，编译后生成一个 .dll 或 .exe
│   → 包含一组 .cs 源文件
│
├── 项目2（.csproj 文件）
│   → 比如一个类库项目
│
└── 项目3（.csproj 文件）
    → 比如一个测试项目
```

**为什么需要解决方案？** 一个真实的软件通常由多个项目组成（主程序 + 类库 + 测试），解决方案把它们组织在一起，方便统一管理。

### 常用快捷键

| 操作 | 快捷键 | 说明 |
|------|--------|------|
| 代码补全 | `Ctrl + Space` | 触发 IntelliSense |
| 快速修复 | `Ctrl + .` | 显示可用的修复和重构 |
| 查找类型 | `Ctrl + T` | 搜索类、方法、文件 |
| 重命名 | `Ctrl + R, R` | 重命名符号（自动更新所有引用） |
| 格式化代码 | `Ctrl + K, D` | 自动调整缩进和空格 |
| 调试运行 | `F5` | 启动调试 |
| 不调试运行 | `Ctrl + F5` | 直接运行，不进入调试 |
| 查看定义 | `F12` | 跳转到方法/类的定义 |
| 查找用法 | `Shift + F12` | 查看某个符号在哪里被使用 |
| 注释/取消注释 | `Ctrl + K, C` / `Ctrl + K, U` | 切换行注释 |
| 转到实现 | `Ctrl + F12` | 跳转到接口的实现 |
| 查看引用 | `Alt + F2` | 查看所有引用 |

### 项目创建

#### 控制台应用

1. `File → New → Project`
2. 选择 `Console App`
3. 选择框架版本（.NET 8 / .NET 9）
4. 填写项目名和位置

#### ASP.NET Core Web 应用

1. `File → New → Project`
2. 选择 `ASP.NET Core Web App`
3. 选择模板：
   - **Empty**：空项目，从零开始
   - **MVC**：Model-View-Controller 架构
   - **Razor Pages**：页面模型，适合简单页面
   - **Web API**：RESTful API，前后端分离

---

## 三、VS Code：轻量级编辑器

### 什么是 VS Code？

VS Code（Visual Studio Code）是微软的免费开源代码编辑器。注意：**VS Code 不是 IDE**，它是一个编辑器，需要通过安装插件来获得 IDE 的能力。

### VS Code 与 Visual Studio 的本质区别

```
Visual Studio：
    "全家桶"——编译器、调试器、项目管理全部内置
    打开 .sln 文件就能开发

VS Code：
    "空壳子"——只有文本编辑和终端
    需要安装插件才能写 C#
    通过 Language Server Protocol（LSP）与 Roslyn 通信
```

**LSP（Language Server Protocol）** 是 VS Code 实现智能补全的核心协议：
```
VS Code（编辑器前端）
    ↓ 发送"用户在输入什么"
Language Server（后端，Roslyn）
    ↓ 返回"应该提示什么"
VS Code 显示补全列表
```

### 安装与配置

#### 1. 安装 C# 扩展

按 `Ctrl+Shift+X`，搜索并安装：

| 扩展 | 说明 | 是否必装 |
|------|------|----------|
| **C# Dev Kit** | 微软官方 C# 扩展包 | 必装 |
| **C#** | C# 语言支持（C# Dev Kit 已包含） | 可选 |
| **IntelliCode for C# Dev Kit** | AI 辅助代码补全 | 推荐 |
| **GitLens** | Git 增强（查看提交历史、blame） | 推荐 |
| **Error Lens** | 在代码行内显示错误信息 | 推荐 |

#### 2. 调试配置

`.vscode/launch.json`：

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": ".NET Core Launch (console)",
            "type": "coreclr",
            "request": "launch",
            "program": "${workspaceFolder}/bin/Debug/net8.0/MyApp.dll",
            "args": [],
            "cwd": "${workspaceFolder}",
            "console": "integratedTerminal",
            "preLaunchTask": "build"
        }
    ]
}
```

> **注意**：`program` 路径中的 `MyApp` 要替换成你的项目名，`net8.0` 要替换成你的目标框架版本。

### VS Code vs Visual Studio

| 特性 | VS Code | Visual Studio |
|------|---------|---------------|
| **启动速度** | 秒开 | 需要几十秒 |
| **内存占用** | ~300MB | ~2-4GB |
| **智能补全** | 基础（依赖插件） | 强大（IntelliSense 深度集成） |
| **重构能力** | 有限 | 强大（2500+ 重构操作） |
| **调试功能** | 基础 | 强大（条件断点、远程调试、内存查看） |
| **框架支持** | 通过插件 | 深度集成（WPF 设计器、EF 工具） |
| **跨平台** | 全平台 | 仅 Windows / macOS |
| **价格** | 免费 | Community 免费 |

> **选择建议**：
> - C# 专业开发 → Visual Studio
> - 轻量查看/编辑 → VS Code
> - 跨平台开发 → VS Code 或 Rider

---

## 四、JetBrains Rider：跨平台 C# IDE

### 简介

Rider 是 JetBrains 出品的跨平台 .NET IDE，基于 IntelliJ 平台和 ReSharper 技术。JetBrains 是做 IDE 起家的公司（IntelliJ IDEA、PyCharm、WebStorm 都是他们的产品），代码分析能力是业界顶尖的。

### 什么是 ReSharper？

ReSharper 是 JetBrains 的 Visual Studio 插件，提供 2500+ 代码检查和重构操作。Rider 内置了 ReSharper 的全部能力，但不需要安装 Visual Studio。

### 版本与价格

| 版本 | 价格 | 说明 |
|------|------|------|
| **个人许可** | 付费（首年 $149） | 个人项目 |
| **商业许可** | 付费（首年 $349） | 企业开发 |
| **学生** | 免费 | 通过 JetBrains 学生计划 |

### 核心功能

| 功能 | 说明 |
|------|------|
| **智能代码补全** | 基于 ReSharper 的强大补全，比 VS 更智能 |
| **重构工具** | 2500+ 重构和代码检查 |
| **调试器** | 跨平台调试、远程调试、数据库调试 |
| **数据库工具** | 内置数据库管理（SQL Server、PostgreSQL、MySQL） |
| **前端支持** | HTML/CSS/JavaScript/TypeScript |
| **Unity 支持** | 游戏开发集成（实时同步 Unity 编辑器） |
| **跨平台** | Windows、macOS、Linux |
| **性能分析** | 内置 dotMemory、dotTrace |

### Rider vs Visual Studio

| 特性 | Rider | Visual Studio |
|------|-------|---------------|
| **跨平台** | ✅ Windows/macOS/Linux | ❌ 仅 Windows（macOS 版功能有限） |
| **启动速度** | 快（基于 IntelliJ 平台） | 慢 |
| **内存占用** | 中等 | 大 |
| **代码分析** | 非常强大（ReSharper 内置） | 强大 |
| **重构能力** | 非常强大 | 强大 |
| **调试功能** | 强大 | 非常强大（Windows 上更成熟） |
| **价格** | 付费 | Community 免费 |
| **WPF 设计器** | 无 | 有 |
| **热重载** | 支持 | 支持 |

> **选择建议**：
> - 跨平台开发 → Rider
> - Windows 专业开发 → Visual Studio
> - Unity 游戏开发 → Rider 或 Visual Studio

---

## 五、.NET SDK 安装与管理

### SDK vs Runtime 的区别

```
SDK（开发者安装）= Runtime + 编译器 + CLI 工具 + NuGet + MSBuild
Runtime（用户安装）= CLR + BCL（只能运行，不能开发）
```

**简单理解：** 你要写代码，装 SDK。你只想运行别人写的程序，装 Runtime。

### Windows 安装

```powershell
# 方式一：winget（推荐，Windows 自带）
winget install Microsoft.DotNet.SDK.8

# 方式二：Scoop（需要先安装 Scoop）
scoop install dotnet-sdk

# 方式三：Chocolatey（需要先安装 Chocolatey）
choco install dotnet-8.0-sdk

# 方式四：手动下载安装包
# 访问 https://dotnet.microsoft.com/download
```

### 验证安装

```bash
dotnet --version          # 显示当前 SDK 版本
dotnet --list-sdks        # 列出所有已安装的 SDK
dotnet --list-runtimes    # 列出所有已安装的运行时
```

### 多版本管理

一台机器可以同时安装多个 .NET SDK 版本。通过 `global.json` 可以指定项目使用的 SDK 版本：

```bash
# 在项目根目录创建 global.json
dotnet new globaljson --sdk-version 8.0.404
```

生成的 `global.json`：

```json
{
  "sdk": {
    "version": "8.0.404",
    "rollForward": "latestPatch"
  }
}
```

| `rollForward` 值 | 行为 |
|-------------------|------|
| `patch` | 只用精确版本（8.0.404） |
| `latestPatch` | 用最新的补丁版本（如 8.0.405） |
| `minor` | 允许升级到更高的次版本 |
| `latestMinor` | 用最新的次版本 |
| `major` | 允许升级到更高的主版本 |

### macOS / Linux

```bash
# macOS（Homebrew）
brew install dotnet-sdk

# Ubuntu
sudo apt install dotnet-sdk-8.0

# CentOS / RHEL
sudo dnf install dotnet-sdk-8.0
```

### dotnet 全局工具

.NET 有一个全局工具系统，可以安装命令行工具：

```bash
# 安装全局工具
dotnet tool install -g dotnet-script      # C# REPL
dotnet tool install -g dotnet-ef           # Entity Framework CLI
dotnet tool install -g dotnet-outdated     # 检查过期的 NuGet 包

# 查看已安装的全局工具
dotnet tool list -g

# 更新全局工具
dotnet tool update -g dotnet-script

# 卸载全局工具
dotnet tool uninstall -g dotnet-script
```

---

## 六、环境选择总结

| 场景 | 推荐工具 | 原因 |
|------|----------|------|
| **C# 专业开发（Windows）** | Visual Studio Community | 功能最全，免费 |
| **跨平台开发** | JetBrains Rider | 三平台一致体验 |
| **轻量开发/学习** | VS Code + C# Dev Kit | 免费、轻量、跨平台 |
| **Unity 游戏开发** | Visual Studio 或 Rider | Unity 官方推荐 |
| **ASP.NET Core 开发** | Visual Studio + ASP.NET 工作负载 | Web 工具最完善 |
| **学生学习** | Visual Studio Community | 免费，资料最多 |
| **服务器上编辑** | VS Code（通过 Remote SSH） | 无需本地 IDE |
