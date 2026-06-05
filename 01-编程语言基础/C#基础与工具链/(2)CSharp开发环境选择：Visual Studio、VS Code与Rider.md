# C# 开发环境选择：Visual Studio、VS Code 与 Rider

## 一、核心概念速览

| 工具 | 一句话定位 | 适合人群 |
|------|-----------|----------|
| **Visual Studio** | 最强大的 C# IDE | .NET 开发者（强烈推荐） |
| **VS Code** | 轻量级编辑器 + 插件 | 轻量开发、跨平台开发者 |
| **JetBrains Rider** | 跨平台 C# IDE | 跨平台开发、JetBrains 用户 |

---

## 二、Visual Studio：最强大的 C# IDE

### 版本对比

| 版本 | 价格 | 特点 |
|------|------|------|
| **Community** | 免费 | 个人/小团队，功能完整 |
| **Professional** | 付费 | 企业开发 |
| **Enterprise** | 付费 | 高级调试、测试工具 |

> **学生优惠**：学生可通过 [Visual Studio Dev Essentials](https://visualstudio.microsoft.com/dev-essentials/) 免费使用。

### 核心功能

| 功能 | 说明 |
|------|------|
| **智能代码补全** | IntelliSense，基于上下文的精准补全 |
| **重构工具** | 重命名、提取方法、内联变量 |
| **调试器** | 条件断点、即时窗口、远程调试 |
| **版本控制** | Git 集成，可视化 diff |
| **数据库工具** | SQL Server 集成 |
| **框架支持** | ASP.NET、WPF、WinForms、MAUI、Unity |
| **NuGet** | 深度集成包管理 |
| **热重载** | 修改代码即时生效 |

### 安装与配置

#### 1. 安装 Visual Studio

访问 [https://visualstudio.microsoft.com/](https://visualstudio.microsoft.com/) 下载安装。

#### 2. 选择工作负载

| 工作负载 | 用途 |
|----------|------|
| **.NET 桌面开发** | WPF、WinForms |
| **ASP.NET 和 Web 开发** | Web 应用、API |
| **使用 Unity 的游戏开发** | Unity 游戏 |
| **.NET Multi-platform App UI** | 跨平台移动/桌面应用 |

#### 3. 配置 .NET SDK

`Tools → Options → Projects and Solutions → .NET Core`：
- 指定 .NET SDK 路径
- 配置默认目标框架

### 常用快捷键

| 操作 | 快捷键 |
|------|--------|
| 代码补全 | `Ctrl + Space` |
| 快速修复 | `Ctrl + .` |
| 查找类型 | `Ctrl + T` |
| 重构 | `Ctrl + R, R`（重命名） |
| 格式化 | `Ctrl + K, D` |
| 运行 | `F5` |
| 调试 | `F5`（调试）/ `Ctrl + F5`（不调试） |
| 查看定义 | `F12` |
| 查找用法 | `Shift + F12` |
| 注释 | `Ctrl + K, C` |
| 取消注释 | `Ctrl + K, U` |

### 项目创建

#### 控制台应用

1. `File → New → Project`
2. 选择 `Console App`
3. 选择框架版本（.NET 8 / .NET 9）
4. 填写项目名和位置

#### ASP.NET Core Web 应用

1. `File → New → Project`
2. 选择 `ASP.NET Core Web App`
3. 选择模板（Empty、MVC、Razor Pages、Web API）

---

## 三、VS Code：轻量级编辑器

### 安装与配置

#### 1. 安装 C# 扩展

按 `Ctrl+Shift+X`，搜索并安装：

| 扩展 | 说明 |
|------|------|
| **C# Dev Kit** | 微软官方 C# 扩展包（必装） |
| **C#** | C# 语言支持 |
| **IntelliCode for C# Dev Kit** | AI 辅助代码补全 |

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

### VS Code vs Visual Studio

| 特性 | VS Code | Visual Studio |
|------|---------|---------------|
| **启动速度** | 快 | 慢 |
| **内存占用** | 小（~300MB） | 大（~2-4GB） |
| **智能补全** | 基础 | 强大 |
| **重构能力** | 有限 | 强大 |
| **调试功能** | 基础 | 强大 |
| **框架支持** | 通过插件 | 深度集成 |
| **跨平台** | 全平台 | 仅 Windows |
| **价格** | 免费 | Community 免费 |

> **选择建议**：
> - C# 专业开发 → Visual Studio
> - 轻量查看/编辑 → VS Code
> - 跨平台开发 → VS Code 或 Rider

---

## 四、JetBrains Rider：跨平台 C# IDE

### 简介

Rider 是 JetBrains 出品的跨平台 .NET IDE，基于 IntelliJ 平台和 ReSharper 技术。

### 版本与价格

| 版本 | 价格 | 说明 |
|------|------|------|
| **个人许可** | 付费（首年 $149） | 个人项目 |
| **商业许可** | 付费（首年 $349） | 企业开发 |
| **学生** | 免费 | 通过 JetBrains 学生计划 |

### 核心功能

| 功能 | 说明 |
|------|------|
| **智能代码补全** | 基于 ReSharper 的强大补全 |
| **重构工具** | 2500+ 重构和代码检查 |
| **调试器** | 跨平台调试、远程调试 |
| **数据库工具** | 内置数据库管理 |
| **前端支持** | HTML/CSS/JavaScript/TypeScript |
| **Unity 支持** | 游戏开发集成 |
| **跨平台** | Windows、macOS、Linux |

### Rider vs Visual Studio

| 特性 | Rider | Visual Studio |
|------|-------|---------------|
| **跨平台** | ✅ Windows/macOS/Linux | ❌ 仅 Windows |
| **启动速度** | 快 | 慢 |
| **内存占用** | 中等 | 大 |
| **代码分析** | 非常强大（ReSharper） | 强大 |
| **重构能力** | 非常强大 | 强大 |
| **调试功能** | 强大 | 非常强大 |
| **价格** | 付费 | Community 免费 |

> **选择建议**：
> - 跨平台开发 → Rider
> - Windows 专业开发 → Visual Studio
> - Unity 游戏开发 → Rider 或 Visual Studio

---

## 五、.NET SDK 安装与管理

### Windows 安装

```powershell
# 方式一：winget（推荐）
winget install Microsoft.DotNet.SDK.8

# 方式二：Scoop
scoop install dotnet-sdk

# 方式三：Chocolatey
choco install dotnet-8.0-sdk
```

### 验证安装

```bash
dotnet --version
dotnet --list-sdks
dotnet --list-runtimes
```

### 多版本管理

```powershell
# 使用 global.json 固定版本
dotnet new globaljson --sdk-version 8.0.404

# 查看已安装版本
dotnet --list-sdks
```

### macOS / Linux

```bash
# macOS（Homebrew）
brew install dotnet-sdk

# Ubuntu
sudo apt install dotnet-sdk-8.0
```

---

## 六、环境选择总结

| 场景 | 推荐工具 |
|------|----------|
| **C# 专业开发** | Visual Studio Enterprise |
| **日常 C# 开发** | Visual Studio Community（推荐） |
| **跨平台开发** | JetBrains Rider 或 VS Code |
| **ASP.NET Core 开发** | Visual Studio + ASP.NET 工作负载 |
| **Unity 游戏开发** | Visual Studio 或 Rider |
| **轻量开发/学习** | VS Code + C# Dev Kit |
| **学生学习** | Visual Studio Community |
