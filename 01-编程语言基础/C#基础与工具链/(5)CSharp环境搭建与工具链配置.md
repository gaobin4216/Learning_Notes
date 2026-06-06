# C# 环境搭建与工具链配置

## 一、.NET SDK 安装

### SDK 与 Runtime 的区别

在安装之前，先搞清楚两个概念：

| 组件 | 包含内容 | 谁需要安装 |
|------|----------|-----------|
| **.NET SDK** | Runtime + 编译器 + CLI 工具 + NuGet + MSBuild | 开发者 |
| **.NET Runtime** | CLR + BCL（只能运行，不能开发） | 普通用户 / 服务器 |

```bash
# 安装 SDK 后，你可以：
dotnet new ...     # 创建项目（SDK 独有）
dotnet build ...   # 编译项目（SDK 独有）
dotnet run ...     # 运行项目
dotnet publish ... # 发布项目（SDK 独有）

# 安装 Runtime 后，你只能：
dotnet MyApp.dll   # 运行已编译的程序
```

### 推荐版本

| 版本 | 说明 | 状态 |
|------|------|------|
| **.NET 8 SDK** | LTS，生产环境推荐 | 长期支持（到 2026 年） |
| **.NET 9 SDK** | 最新版本 | 当前版本（到 2025 年中） |

> **建议**：开发时安装 .NET 8 SDK（LTS），同时可选装 .NET 9 SDK 体验新特性。

### Windows 安装

```powershell
# 方式一：winget（推荐，Windows 10/11 自带）
winget install Microsoft.DotNet.SDK.8

# 方式二：Scoop（需要先安装 Scoop）
scoop install dotnet-sdk

# 方式三：Chocolatey（需要先安装 Chocolatey）
choco install dotnet-8.0-sdk

# 方式四：手动下载安装包
# 访问 https://dotnet.microsoft.com/download
# 下载 SDK 安装包，双击安装
```

### macOS 安装

```bash
# Homebrew（推荐）
brew install dotnet-sdk

# 或者手动下载
# 访问 https://dotnet.microsoft.com/download
# 选择 macOS ARM64（M1/M2/M3）或 x64（Intel）
```

### Linux 安装

```bash
# Ubuntu / Debian
sudo apt update
sudo apt install dotnet-sdk-8.0

# CentOS / RHEL / Fedora
sudo dnf install dotnet-sdk-8.0

# 或者使用安装脚本（通用）
wget https://dot.net/v1/dotnet-install.sh
chmod +x dotnet-install.sh
./dotnet-install.sh --channel 8.0
```

### 验证安装

```bash
dotnet --version          # 当前 SDK 版本
dotnet --list-sdks        # 所有已安装的 SDK
dotnet --list-runtimes    # 所有已安装的运行时
```

输出示例：

```
$ dotnet --version
8.0.404

$ dotnet --list-sdks
8.0.404 [C:\Program Files\dotnet\sdk]

$ dotnet --list-runtimes
Microsoft.NETCore.App 8.0.4 [C:\Program Files\dotnet\shared\Microsoft.NETCore.App]
Microsoft.AspNetCore.App 8.0.4 [C:\Program Files\dotnet\shared\Microsoft.AspNetCore.App]
```

---

## 二、IDE 安装

### 方案一：Visual Studio（推荐 Windows 用户）

#### 下载安装

1. 访问 [https://visualstudio.microsoft.com/](https://visualstudio.microsoft.com/)
2. 下载 **Community** 版本（免费）
3. 运行安装程序

#### 选择工作负载

**至少勾选这两个：**

| 工作负载 | 用途 |
|----------|------|
| ✅ **.NET 桌面开发** | WPF、WinForms 桌面应用 |
| ✅ **ASP.NET 和 Web 开发** | Web 应用、API、Blazor |

可选：

| 工作负载 | 用途 |
|----------|------|
| **使用 Unity 的游戏开发** | Unity 游戏 |
| **.NET Multi-platform App UI** | 跨平台移动/桌面应用 |

#### 安装推荐扩展

| 扩展 | 说明 | 是否免费 |
|------|------|----------|
| **GitHub Copilot** | AI 辅助编码 | 学生免费 |
| **CodeMaid** | 代码清理与格式化 | 免费 |
| **ReSharper** | 代码分析与重构 | 付费（功能强大） |

### 方案二：VS Code（推荐跨平台用户）

#### 安装 VS Code

访问 [https://code.visualstudio.com/](https://code.visualstudio.com/) 下载安装。

#### 安装 C# 扩展

按 `Ctrl+Shift+X` 打开扩展面板，搜索并安装：

```bash
# 命令行安装
code --install-extension ms-dotnettools.csdevkit
```

| 扩展 | 说明 | 是否必装 |
|------|------|----------|
| **C# Dev Kit** | 微软官方 C# 开发工具包 | 必装 |
| **IntelliCode** | AI 辅助补全 | 推荐 |
| **GitLens** | Git 增强（查看提交历史） | 推荐 |
| **Error Lens** | 行内显示错误信息 | 推荐 |
| **Thunder Client** | REST API 测试（类似 Postman） | 可选 |

### 方案三：JetBrains Rider（推荐跨平台专业用户）

#### 下载安装

1. 访问 [https://www.jetbrains.com/rider/](https://www.jetbrains.com/rider/)
2. 下载对应平台的安装包
3. 学生可通过 [JetBrains 学生计划](https://www.jetbrains.com/community/education/) 免费使用

---

## 三、第一个 C# 项目

### 命令行方式

```bash
# 创建控制台项目
dotnet new console -n HelloApp

# 进入项目目录
cd HelloApp

# 查看生成的文件
ls
# HelloApp.csproj  ← 项目文件
# Program.cs       ← 源代码

# 运行
dotnet run
# 输出：Hello, World!
```

### 生成的 Program.cs（.NET 6+ 顶层语句）

```csharp
// 只有一行代码，没有 Main 方法、没有 using、没有 namespace
// 这是 C# 9 引入的"顶层语句"语法糖
Console.WriteLine("Hello, World!");
```

等价于传统的完整写法：

```csharp
using System;

namespace HelloApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello, World!");
        }
    }
}
```

### Visual Studio 方式

1. `File → New → Project`
2. 选择 `Console App`
3. 选择框架版本（.NET 8 / .NET 9）
4. 填写项目名和位置
5. 按 `F5` 运行

### ASP.NET Core Web API

```bash
# 创建 Web API 项目
dotnet new webapi -n MyApi
cd MyApi

# 运行
dotnet run

# 默认监听 https://localhost:5001
# 访问 Swagger 文档：https://localhost:5001/swagger
```

### 自定义入口点（C# 9+ 之前）

如果不用顶层语句，传统的入口点是 `Main` 方法：

```csharp
namespace HelloApp
{
    class Program
    {
        // Main 方法是程序的入口点
        static void Main(string[] args)
        {
            Console.WriteLine("Hello, World!");

            // 读取命令行参数
            if (args.Length > 0)
            {
                Console.WriteLine($"参数: {args[0]}");
            }
        }
    }
}
```

---

## 四、global.json：锁定 SDK 版本

### 为什么需要 global.json？

一台机器上可能安装了多个 SDK 版本。`global.json` 可以指定项目使用哪个 SDK 版本，避免不同开发者用不同版本导致编译结果不一致。

### 创建 global.json

```bash
# 在项目根目录创建
dotnet new globaljson --sdk-version 8.0.404
```

### global.json 内容

```json
{
  "sdk": {
    "version": "8.0.404",
    "rollForward": "latestPatch",
    "allowPrerelease": false
  }
}
```

| 字段 | 说明 |
|------|------|
| `version` | 指定的 SDK 版本 |
| `rollForward` | 版本回退策略 |
| `allowPrerelease` | 是否允许预览版 |

### rollForward 策略

| 值 | 行为 | 示例 |
|----|------|------|
| `patch` | 只用精确版本 | 只用 8.0.404 |
| `latestPatch` | 用最新的补丁版本 | 8.0.404 → 8.0.405 |
| `feature` | 允许升级到更高的 feature band | 8.0.4xx → 8.0.5xx |
| `minor` | 允许升级到更高的次版本 | 8.0.x → 8.1.x |
| `major` | 允许升级到更高的主版本 | 8.x → 9.x |
| `latestMajor` | 用最新的主版本 | 用系统中最新的 SDK |

---

## 五、代码质量工具

### 内置代码分析器

.NET SDK 内置了 Roslyn 代码分析器，可以在编译时检查代码问题：

```xml
<!-- .csproj -->
<PropertyGroup>
    <!-- 启用代码分析 -->
    <EnableNETAnalyzers>true</EnableNETAnalyzers>

    <!-- 分析模式：Default / Recommended / All -->
    <AnalysisMode>Recommended</AnalysisMode>

    <!-- 在构建时强制执行代码风格 -->
    <EnforceCodeStyleInBuild>true</EnforceCodeStyleInBuild>

    <!-- 将警告视为错误（严格模式） -->
    <TreatWarningsAsErrors>true</TreatWarningsAsErrors>
</PropertyGroup>
```

### 常用代码质量工具

| 工具 | 用途 | 安装方式 | 说明 |
|------|------|----------|------|
| **Roslyn 分析器** | 内置代码分析 | .NET SDK 自带 | 检查常见代码问题 |
| **StyleCop** | 代码风格检查 | NuGet 包 | 强制统一代码风格 |
| **SonarQube** | 综合代码质量平台 | 独立服务 | 代码异味、漏洞、坏味道 |
| **BenchmarkDotNet** | 性能基准测试 | NuGet 包 | 精确测量代码性能 |
| **Coverlet** | 代码覆盖率 | NuGet 包 | 测试覆盖率报告 |

### .editorconfig：统一代码风格

`.editorconfig` 文件定义了代码的格式化规则，所有编辑器都会遵守：

```ini
root = true

[*]
indent_style = space
indent_size = 4
end_of_line = lf
charset = utf-8
trim_trailing_whitespace = true
insert_final_newline = true

[*.cs]
# 命名空间风格：file_scoped（C# 10+ 推荐）
csharp_style_namespace_declarations = file_scoped:suggestion

# 使用 var 推断类型
csharp_style_var_for_built_in_types = true:suggestion
csharp_style_var_when_type_is_apparent = true:suggestion

# using 排序：System 开头的放前面
dotnet_sort_system_directives_first = true

# 花括号换行
csharp_new_line_before_open_brace = all

# 表达式体成员
csharp_style_expression_bodied_methods = when_on_single_line:suggestion
csharp_style_expression_bodied_properties = true:suggestion
```

---

## 六、NuGet 镜像配置

### 为什么需要镜像？

nuget.org 的服务器在国外，国内下载速度很慢。

### 添加阿里云镜像

```bash
dotnet nuget add source https://nuget.aliyun.com/api/v3/index.json --name aliyun
```

### 手动配置 NuGet.Config

`NuGet.Config` 位置：
- Windows：`%AppData%\NuGet\NuGet.Config`
- macOS/Linux：`~/.nuget/NuGet/NuGet.Config`

```xml
<?xml version="1.0" encoding="utf-8"?>
<configuration>
    <packageSources>
        <add key="aliyun" value="https://nuget.aliyun.com/api/v3/index.json" protocolVersion="3" />
        <add key="nuget.org" value="https://api.nuget.org/v3/index.json" protocolVersion="3" />
    </packageSources>
</configuration>
```

> **优先级**：源的顺序决定了优先级，建议把阿里云放在前面。

### 常用国内镜像

| 镜像 | 地址 |
|------|------|
| **阿里云** | `https://nuget.aliyun.com/api/v3/index.json` |
| **腾讯云** | `https://mirrors.tencent.com/nuget/` |
| **华为云** | `https://repo.huaweicloud.com/repository/nuget/` |

---

## 七、常见问题排查

### SDK 版本不匹配

**症状**：`dotnet build` 报错 "The current .NET SDK does not support targeting .NET X.X"

**解决**：

```bash
# 查看已安装的 SDK
dotnet --list-sdks

# 如果缺少对应版本，安装它
winget install Microsoft.DotNet.SDK.8

# 或者用 global.json 指定一个已有的版本
dotnet new globaljson --sdk-version 8.0.404
```

### NuGet 包下载慢或失败

**症状**：`dotnet restore` 超时或很慢

**解决**：

```bash
# 添加国内镜像
dotnet nuget add source https://nuget.aliyun.com/api/v3/index.json --name aliyun

# 清除 NuGet 缓存后重试
dotnet nuget locals all --clear
dotnet restore
```

### 项目无法编译

**症状**：`dotnet build` 报各种奇怪错误

**解决**（按顺序尝试）：

```bash
# 1. 清理并重新编译
dotnet clean
dotnet build

# 2. 删除 bin/obj 目录后重试
rm -rf bin obj
dotnet build

# 3. 还原 NuGet 包后重试
dotnet restore
dotnet build

# 4. 检查 .csproj 文件是否正确
cat *.csproj
```

### 找不到 dotnet 命令

**症状**：`dotnet` 命令提示"不是内部或外部命令"

**解决**：
- Windows：重新安装 SDK，或检查 `PATH` 环境变量是否包含 `C:\Program Files\dotnet`
- macOS/Linux：检查 `~/.dotnet` 或 `/usr/share/dotnet` 是否在 `PATH` 中

---

## 八、Git 配置

### .gitignore

C# 项目的 `.gitignore` 文件：

```
# 编译输出
bin/
obj/

# VS 用户配置
*.user
*.suo
*.userosscache
*.sln.docstates

# VS 目录
.vs/

# Rider 目录
.idea/

# NuGet
*.nupkg
**/[Pp]ackages/*
!**/[Pp]ackages/build/

# 发布输出
publish/

# macOS
.DS_Store
```

### 推荐的 Git 工作流

```bash
# 初始化仓库
git init
git add .
git commit -m "Initial commit"

# 创建开发分支
git checkout -b develop

# 功能开发
git checkout -b feature/add-user-api
# ... 编码 ...
git add .
git commit -m "feat: add user API"
git checkout develop
git merge feature/add-user-api
```
