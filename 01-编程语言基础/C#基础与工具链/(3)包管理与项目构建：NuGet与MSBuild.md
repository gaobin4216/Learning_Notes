# 包管理与项目构建：NuGet 与 MSBuild

## 一、为什么需要包管理与构建工具？

### 没有构建工具时的痛苦

假设你写了一个 C# 项目，引用了 3 个第三方库。没有构建工具时，你需要：

1. 手动下载每个库的 .dll 文件
2. 手动把 .dll 复制到项目目录
3. 手动在项目中添加引用
4. 手动执行编译命令
5. 每个库更新时，重复以上步骤
6. 团队其他人也要重复以上步骤

### 构建工具如何解决这些问题

| 问题 | 工具如何解决 |
|------|-------------|
| **依赖管理** | NuGet 自动下载和管理第三方库 |
| **编译打包** | dotnet CLI 一条命令完成编译、测试、打包 |
| **版本锁定** | 锁定依赖版本，团队环境一致 |
| **可复现性** | 任何人拿到代码都能一键还原环境 |

---

## 二、NuGet 包管理

### 什么是 NuGet？

NuGet（读作 "New Get"）是 .NET 的官方包管理器。它的作用是：

1. **下载**：从远程仓库（nuget.org）下载第三方库
2. **管理**：记录你的项目引用了哪些库、什么版本
3. **传递依赖**：如果你引用的库 A 依赖库 B，NuGet 会自动下载库 B

### NuGet 包的本质

一个 NuGet 包本质上是一个 `.zip` 文件，解压后包含：

```
MyPackage.1.0.0.nupkg（本质是 zip）
├── lib/
│   └── net8.0/
│       └── MyPackage.dll        ← 编译好的程序集
├── MyPackage.nuspec             ← 包的元数据（名称、版本、依赖）
└── README.md                    ← 说明文档
```

### NuGet 包来源

| 来源 | 说明 | 地址 |
|------|------|------|
| **nuget.org** | 官方公共包仓库（最大的 .NET 包仓库） | https://www.nuget.org |
| **Azure Artifacts** | 微软 Azure 的私有包托管 | 付费服务 |
| **GitHub Packages** | GitHub 私有包托管 | 免费有限额 |
| **本地文件夹** | 本地 NuGet 源（离线环境用） | 任意目录 |

### 添加 NuGet 包

#### 方式一：dotnet CLI（推荐）

```bash
# 添加包（自动安装最新稳定版）
dotnet add package Newtonsoft.Json

# 添加指定版本
dotnet add package Newtonsoft.Json --version 13.0.3

# 移除包
dotnet remove package Newtonsoft.Json

# 查看已安装的包
dotnet list package

# 查看可用的更新
dotnet list package --outdated
```

#### 方式二：Visual Studio

1. 右键项目 → `Manage NuGet Packages`
2. 搜索包名
3. 选择版本，点击 `Install`

#### 方式三：Package Manager Console（VS 内置命令行）

```powershell
# 安装包
Install-Package Newtonsoft.Json

# 指定版本
Install-Package Newtonsoft.Json -Version 13.0.3

# 卸载包
Uninstall-Package Newtonsoft.Json

# 更新包
Update-Package Newtonsoft.Json
```

### .csproj 中的包引用

当你执行 `dotnet add package` 后，包引用会自动写入 `.csproj` 文件：

```xml
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
        <TargetFramework>net8.0</TargetFramework>
    </PropertyGroup>

    <ItemGroup>
        <!-- NuGet 包引用 -->
        <PackageReference Include="Newtonsoft.Json" Version="13.0.3" />
        <PackageReference Include="Serilog" Version="3.1.1" />
    </ItemGroup>
</Project>
```

> **Restore（还原）**：当你从 Git 拉取代码后，需要执行 `dotnet restore` 来下载 `.csproj` 中声明的 NuGet 包。`dotnet build` 和 `dotnet run` 会自动触发 restore。

### 常用 NuGet 包

| 包名 | 用途 | 说明 |
|------|------|------|
| **Newtonsoft.Json** | JSON 序列化 | 最流行的 JSON 库（也有内置的 System.Text.Json） |
| **Serilog** | 结构化日志 | 比 Console.WriteLine 更专业的日志方案 |
| **AutoMapper** | 对象映射 | 在 DTO 和实体之间自动映射 |
| **Dapper** | 轻量 ORM | 比 EF Core 更轻量的数据库访问 |
| **Entity Framework Core** | ORM 框架 | 微软官方 ORM，功能最全 |
| **xUnit** | 单元测试框架 | .NET 最流行的测试框架 |
| **Moq** | Mock 框架 | 模拟依赖对象，方便单元测试 |
| **Polly** | 弹性处理 | 重试、熔断、超时策略 |
| **FluentValidation** | 验证框架 | 链式 API 做参数验证 |
| **MediatR** | 中介者模式 | CQRS 和事件驱动架构 |

### 中央包管理（Central Package Management）

当你的解决方案有多个项目时，每个项目可能引用相同包的不同版本，容易混乱。中央包管理可以在一个地方统一管理所有包的版本：

`Directory.Packages.props`（解决方案根目录）：

```xml
<Project>
    <PropertyGroup>
        <ManagePackageVersionsCentrally>true</ManagePackageVersionsCentrally>
    </PropertyGroup>
    <ItemGroup>
        <!-- 在这里统一定义版本 -->
        <PackageVersion Include="Newtonsoft.Json" Version="13.0.3" />
        <PackageVersion Include="Serilog" Version="3.1.1" />
        <PackageVersion Include="xUnit" Version="2.7.0" />
    </ItemGroup>
</Project>
```

各项目的 `.csproj` 中不再指定版本：

```xml
<ItemGroup>
    <!-- 只写包名，版本由中央文件控制 -->
    <PackageReference Include="Newtonsoft.Json" />
    <PackageReference Include="Serilog" />
</ItemGroup>
```

**好处**：所有项目用同一个版本，避免版本冲突。

### NuGet 依赖解析

NuGet 会自动处理传递依赖。比如你的项目引用了 `Serilog.Sinks.Console`，而它依赖 `Serilog`：

```
你的项目
└── Serilog.Sinks.Console 3.1.1
    └── Serilog 3.1.1          ← NuGet 自动下载
```

如果两个包依赖同一个库的不同版本，NuGet 会选择**兼容的最高版本**：

```
你的项目
├── PackageA → 依赖 Newtonsoft.Json 12.0.1
└── PackageB → 依赖 Newtonsoft.Json 13.0.3

结果：使用 13.0.3（高版本兼容低版本）
```

---

## 三、MSBuild 与 dotnet CLI

### 什么是 MSBuild？

MSBuild 是 .NET 的**构建引擎**，负责解析 `.csproj` 文件并执行编译流程。你通常不直接调用 MSBuild，而是通过 `dotnet CLI` 间接使用它。

### dotnet CLI 构建命令

dotnet CLI 是 .NET 的命令行工具，相当于 Java 的 Maven/Gradle：

```bash
dotnet new console -n MyApp    # 创建控制台项目
dotnet build                    # 编译（自动先 restore）
dotnet run                      # 编译并运行
dotnet test                     # 运行测试
dotnet publish                  # 发布（生成部署包）
dotnet clean                    # 清理编译输出
dotnet restore                  # 还原 NuGet 包
dotnet pack                     # 打包为 NuGet 包
```

### 编译流程详解

当你执行 `dotnet build` 时，MSBuild 会执行以下步骤：

```
dotnet build
    ↓
1. Restore（还原 NuGet 包）
   → 读取 .csproj 中的 <PackageReference>
   → 从 nuget.org 下载缺失的包
   → 缓存到 ~/.nuget/packages
    ↓
2. Compile（编译）
   → Roslyn 编译器把 .cs 文件编译成 IL
   → 输出到 bin/Debug/net8.0/ 目录
    ↓
3. Link（链接）
   → 合并依赖的程序集引用
   → 生成 .dll 或 .exe
    ↓
4. Output（输出）
   → bin/Debug/net8.0/MyApp.dll（IL 代码）
   → bin/Debug/net8.0/MyApp.pdb（调试符号）
   → bin/Debug/net8.0/MyApp.deps.json（依赖清单）
```

### 项目文件（.csproj）

`.csproj` 是 C# 项目的核心配置文件，用 XML 格式：

```xml
<Project Sdk="Microsoft.NET.Sdk">
    <!-- 项目属性 -->
    <PropertyGroup>
        <OutputType>Exe</OutputType>              <!-- 输出类型：Exe 或 Library -->
        <TargetFramework>net8.0</TargetFramework>  <!-- 目标框架 -->
        <RootNamespace>MyApp</RootNamespace>       <!-- 根命名空间 -->
        <Version>1.0.0</Version>                   <!-- 程序集版本 -->
        <ImplicitUsings>enable</ImplicitUsings>    <!-- 隐式 using（C# 10+） -->
        <Nullable>enable</Nullable>                <!-- 可空引用类型（C# 8+） -->
    </PropertyGroup>

    <!-- NuGet 包引用 -->
    <ItemGroup>
        <PackageReference Include="Newtonsoft.Json" Version="13.0.3" />
    </ItemGroup>

    <!-- 项目引用 -->
    <ItemGroup>
        <ProjectReference Include="../MyLibrary/MyLibrary.csproj" />
    </ItemGroup>
</Project>
```

### 目标框架（Target Framework）

`<TargetFramework>` 指定你的项目编译到哪个平台：

| 标识符 | 说明 | 使用场景 |
|--------|------|----------|
| `net8.0` | .NET 8 | 新项目首选 |
| `net9.0` | .NET 9 | 最新项目 |
| `netstandard2.0` | .NET Standard 2.0 | 需要兼容 .NET Framework 的类库 |
| `net48` | .NET Framework 4.8 | 仅 Windows 的老项目 |

你也可以同时支持多个框架：

```xml
<!-- 多目标框架 -->
<TargetFrameworks>net8.0;netstandard2.0</TargetFrameworks>
```

### 常用项目模板

```bash
dotnet new list                    # 查看所有可用模板
dotnet new console -n MyApp        # 控制台应用
dotnet new classlib -n MyLib       # 类库（生成 .dll）
dotnet new webapi -n MyApi         # Web API
dotnet new mvc -n MyWebApp         # MVC Web 应用
dotnet new blazor -n MyBlazorApp   # Blazor 应用
dotnet new worker -n MyWorker      # 后台服务（Worker Service）
dotnet new xunit -n MyTests        # xUnit 测试项目
dotnet new sln -n MySolution       # 解决方案文件
```

### 解决方案管理

```bash
# 创建解决方案
dotnet new sln -n MySolution

# 把项目添加到解决方案
dotnet sln add src/MyApp/MyApp.csproj
dotnet sln add src/MyLibrary/MyLibrary.csproj
dotnet sln add tests/MyApp.Tests/MyApp.Tests.csproj

# 查看解决方案中的项目
dotnet sln list
```

---

## 四、发布与部署

### 发布模式

```bash
# 框架依赖部署（FDD）
# → 目标机器需要安装 .NET 运行时
# → 生成的包体积小
dotnet publish -c Release

# 独立部署（SCD）
# → 包含 .NET 运行时，目标机器不需要安装 .NET
# → 生成的包体积大（~60-100MB）
dotnet publish -c Release -r win-x64 --self-contained

# 单文件发布
# → 把所有文件打包成一个 .exe
dotnet publish -c Release -r win-x64 --self-contained -p:PublishSingleFile=true

# 原生 AOT 编译（.NET 7+）
# → 直接编译成机器码，不需要 CLR 和 JIT
# → 启动最快，体积最小，但有限制（不支持反射等）
dotnet publish -c Release -r win-x64 -p:PublishAot=true
```

### 发布模式对比

| 模式 | 需要运行时？ | 体积 | 启动速度 | 适用场景 |
|------|-------------|------|----------|----------|
| **框架依赖** | 需要 | 小 | 一般 | 服务器部署（已有运行时） |
| **独立部署** | 不需要 | 大 | 一般 | 分发给用户 |
| **单文件** | 可选 | 中 | 一般 | 简化分发 |
| **AOT** | 不需要 | 小 | 最快 | 性能敏感、容器化 |

### 常见运行时标识符（RID）

| RID | 说明 |
|-----|------|
| `win-x64` | Windows 64 位（最常见） |
| `win-arm64` | Windows ARM64（Surface Pro X 等） |
| `linux-x64` | Linux 64 位 |
| `linux-arm64` | Linux ARM64（树莓派、AWS Graviton） |
| `osx-x64` | macOS Intel |
| `osx-arm64` | macOS Apple Silicon（M1/M2/M3） |

---

## 五、镜像配置（国内加速）

### 为什么需要镜像？

nuget.org 的服务器在国外，国内下载速度很慢。配置国内镜像可以大幅加速。

### NuGet 镜像

```bash
# 命令行添加阿里云镜像
dotnet nuget add source https://nuget.aliyun.com/api/v3/index.json --name aliyun

# 查看已配置的源
dotnet nuget list source
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

### 常用国内镜像

| 镜像 | 地址 |
|------|------|
| **阿里云** | https://nuget.aliyun.com/api/v3/index.json |
| **腾讯云** | https://mirrors.tencent.com/nuget/ |
| **华为云** | https://repo.huaweicloud.com/repository/nuget/ |

> **优先级**：NuGet 会按顺序尝试源，建议把阿里云放在 nuget.org 前面。
