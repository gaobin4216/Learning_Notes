# C# 环境搭建与工具链配置

## 一、.NET SDK 安装

### 推荐版本

| 版本 | 说明 | 状态 |
|------|------|------|
| **.NET 8 SDK** | LTS，推荐 | 长期支持 |
| **.NET 9 SDK** | 最新 | 当前版本 |

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

### macOS / Linux

```bash
# macOS（Homebrew）
brew install dotnet-sdk

# Ubuntu
sudo apt install dotnet-sdk-8.0
```

---

## 二、IDE 安装（Visual Studio）

### 下载安装

1. 下载 [Visual Studio Community](https://visualstudio.microsoft.com/)（免费）
2. 选择工作负载：
   - **.NET 桌面开发**（WPF、WinForms）
   - **ASP.NET 和 Web 开发**（Web 应用、API）
3. 安装完成

### 推荐扩展

| 扩展 | 说明 |
|------|------|
| **ReSharper** | 代码分析与重构（付费） |
| **CodeMaid** | 代码清理与格式化 |
| **GitHub Copilot** | AI 辅助编码 |

---

## 三、VS Code 配置

### 安装 C# 扩展

```bash
code --install-extension ms-dotnettools.csdevkit
```

### 推荐扩展

| 扩展 | 说明 |
|------|------|
| **C# Dev Kit** | C# 开发工具包 |
| **IntelliCode** | AI 辅助补全 |
| **GitLens** | Git 增强 |
| **Error Lens** | 内联错误显示 |

### 配置文件

`.vscode/launch.json`：

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": ".NET Core Launch",
            "type": "coreclr",
            "request": "launch",
            "program": "${workspaceFolder}/bin/Debug/net8.0/MyApp.dll",
            "cwd": "${workspaceFolder}",
            "console": "integratedTerminal",
            "preLaunchTask": "build"
        }
    ]
}
```

---

## 四、第一个 C# 项目

### 命令行方式

```bash
# 创建项目
dotnet new console -n HelloApp
cd HelloApp

# 运行
dotnet run
```

输出：`Hello, World!`

### Visual Studio 方式

1. `File → New → Project → Console App`
2. 选择 .NET 8，填写项目名
3. 编写代码，按 `F5` 运行

### ASP.NET Core Web API

```bash
dotnet new webapi -n MyApi
cd MyApi
dotnet run

# 访问 https://localhost:5001/swagger
```

---

## 五、代码质量工具

### 代码分析器

```xml
<!-- .csproj -->
<PropertyGroup>
    <EnableNETAnalyzers>true</EnableNETAnalyzers>
    <AnalysisMode>Recommended</AnalysisMode>
    <EnforceCodeStyleInBuild>true</EnforceCodeStyleInBuild>
</PropertyGroup>
```

### 常用工具

| 工具 | 用途 | 集成方式 |
|------|------|----------|
| **Roslyn 分析器** | 内置代码分析 | .NET SDK 内置 |
| **StyleCop** | 代码风格检查 | NuGet 包 |
| **SonarQube** | 综合代码质量平台 | 独立服务 + 插件 |
| **BenchmarkDotNet** | 性能基准测试 | NuGet 包 |
| **Coverlet** | 代码覆盖率 | NuGet 包 |

### .editorconfig

```ini
root = true

[*]
indent_style = space
indent_size = 4
end_of_line = lf
charset = utf-8

[*.cs]
csharp_style_namespace_declarations = file_scoped:suggestion
csharp_style_var_for_built_in_types = true:suggestion
dotnet_sort_system_directives_first = true
```

---

## 六、常见问题

### SDK 版本不匹配

```bash
dotnet --list-sdks
dotnet new globaljson --sdk-version 8.0.404
```

### NuGet 包下载慢

配置阿里云镜像（见 (3) 包管理与项目构建）。

### 项目无法编译

```bash
dotnet restore
dotnet clean
dotnet build
```

---

## 七、Git 配置

### .gitignore

```
bin/
obj/
*.user
*.suo
.vs/
```
