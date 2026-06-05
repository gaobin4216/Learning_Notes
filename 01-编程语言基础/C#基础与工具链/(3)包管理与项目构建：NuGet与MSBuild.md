# 包管理与项目构建：NuGet 与 MSBuild

## 一、为什么需要包管理与构建工具？

手动管理 C# 项目的编译、测试、打包和依赖非常繁琐。.NET 生态提供了 NuGet（包管理）和 MSBuild（构建系统）来自动化这些流程。

| 问题 | 工具如何解决 |
|------|-------------|
| 依赖管理 | NuGet 自动下载和管理第三方库 |
| 编译打包 | dotnet CLI 一条命令完成编译、测试、打包 |
| 项目结构 | 约定标准目录结构 |
| 可复现性 | 锁定依赖版本，团队环境一致 |

---

## 二、NuGet 包管理

### 简介

NuGet 是 .NET 的官方包管理器，类似于 Java 的 Maven Central、Python 的 PyPI。

### NuGet 包来源

| 来源 | 说明 |
|------|------|
| **nuget.org** | 官方公共包仓库 |
| **Azure Artifacts** | 私有包托管 |
| **GitHub Packages** | GitHub 私有包 |
| **本地文件夹** | 本地 NuGet 源 |

### 添加 NuGet 包

#### 方式一：dotnet CLI（推荐）

```bash
# 添加包
dotnet add package Newtonsoft.Json

# 添加指定版本
dotnet add package Newtonsoft.Json --version 13.0.3

# 移除包
dotnet remove package Newtonsoft.Json

# 查看已安装的包
dotnet list package
```

#### 方式二：Visual Studio

1. 右键项目 → `Manage NuGet Packages`
2. 搜索包名
3. 点击 `Install`

#### 方式三：Package Manager Console

```powershell
# 安装包
Install-Package Newtonsoft.Json

# 卸载包
Uninstall-Package Newtonsoft.Json
```

### .csproj 中的包引用

```xml
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
        <TargetFramework>net8.0</TargetFramework>
    </PropertyGroup>

    <ItemGroup>
        <PackageReference Include="Newtonsoft.Json" Version="13.0.3" />
        <PackageReference Include="Serilog" Version="3.1.1" />
    </ItemGroup>
</Project>
```

### 常用 NuGet 包

| 包名 | 用途 |
|------|------|
| **Newtonsoft.Json** | JSON 序列化 |
| **Serilog** | 结构化日志 |
| **AutoMapper** | 对象映射 |
| **Dapper** | 轻量 ORM |
| **Entity Framework Core** | ORM 框架 |
| **xUnit** | 单元测试框架 |
| **Moq** | Mock 框架 |
| **Polly** | 弹性与瞬态故障处理 |
| **FluentValidation** | 验证框架 |

### 中央包管理（Central Package Management）

`Directory.Packages.props`（项目根目录）：

```xml
<Project>
    <PropertyGroup>
        <ManagePackageVersionsCentrally>true</ManagePackageVersionsCentrally>
    </PropertyGroup>
    <ItemGroup>
        <PackageVersion Include="Newtonsoft.Json" Version="13.0.3" />
        <PackageVersion Include="Serilog" Version="3.1.1" />
    </ItemGroup>
</Project>
```

`.csproj` 中不再指定版本：

```xml
<ItemGroup>
    <PackageReference Include="Newtonsoft.Json" />
    <PackageReference Include="Serilog" />
</ItemGroup>
```

---

## 三、dotnet CLI 构建命令

dotnet CLI 是 .NET 的命令行工具，相当于 Java 的 mvn/gradle。

### 常用命令

```bash
dotnet new console -n MyApp    # 创建控制台项目
dotnet build                    # 编译
dotnet run                      # 编译并运行
dotnet test                     # 运行测试
dotnet publish                  # 发布
dotnet clean                    # 清理
dotnet restore                  # 还原 NuGet 包
dotnet pack                     # 打包为 NuGet 包
```

### 项目文件（.csproj）

```xml
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
        <OutputType>Exe</OutputType>
        <TargetFramework>net8.0</TargetFramework>
        <RootNamespace>MyApp</RootNamespace>
        <Version>1.0.0</Version>
    </PropertyGroup>

    <ItemGroup>
        <PackageReference Include="Newtonsoft.Json" Version="13.0.3" />
    </ItemGroup>

    <ItemGroup>
        <ProjectReference Include="../MyLibrary/MyLibrary.csproj" />
    </ItemGroup>
</Project>
```

### 目标框架

| 标识符 | 说明 |
|--------|------|
| `net8.0` | .NET 8（跨平台） |
| `net9.0` | .NET 9（跨平台） |
| `netstandard2.0` | .NET Standard 2.0（兼容性） |
| `net48` | .NET Framework 4.8（仅 Windows） |

---

## 四、项目模板

### 常用模板

```bash
dotnet new list                    # 查看所有模板
dotnet new console -n MyApp        # 控制台应用
dotnet new classlib -n MyLib       # 类库
dotnet new webapi -n MyApi         # Web API
dotnet new mvc -n MyWebApp         # MVC Web 应用
dotnet new blazor -n MyBlazorApp   # Blazor 应用
dotnet new worker -n MyWorker      # 后台服务
dotnet new xunit -n MyTests        # xUnit 测试项目
dotnet new sln -n MySolution       # 解决方案文件
```

### 添加项目到解决方案

```bash
dotnet new sln -n MySolution
dotnet sln add MyApp/MyApp.csproj
dotnet sln add MyLib/MyLib.csproj
```

---

## 五、发布与部署

### 发布模式

```bash
# 框架依赖部署（需要目标机器安装 .NET 运行时）
dotnet publish -c Release

# 独立部署（包含 .NET 运行时，体积大）
dotnet publish -c Release -r win-x64 --self-contained

# 单文件发布
dotnet publish -c Release -r win-x64 --self-contained -p:PublishSingleFile=true

# 原生 AOT 编译（.NET 7+）
dotnet publish -c Release -r win-x64 -p:PublishAot=true
```

### 常见运行时标识符（RID）

| RID | 说明 |
|-----|------|
| `win-x64` | Windows 64 位 |
| `win-arm64` | Windows ARM64 |
| `linux-x64` | Linux 64 位 |
| `osx-x64` | macOS 64 位 |
| `osx-arm64` | macOS ARM（Apple Silicon） |

---

## 六、镜像配置（国内加速）

### NuGet 镜像

```bash
# 命令行添加阿里云镜像
dotnet nuget add source https://nuget.aliyun.com/api/v3/index.json --name aliyun
```

`NuGet.Config`（位于 `%AppData%\NuGet\NuGet.Config` 或项目根目录）：

```xml
<?xml version="1.0" encoding="utf-8"?>
<configuration>
    <packageSources>
        <add key="nuget.org" value="https://api.nuget.org/v3/index.json" protocolVersion="3" />
        <add key="aliyun" value="https://nuget.aliyun.com/api/v3/index.json" protocolVersion="3" />
    </packageSources>
</configuration>
```
