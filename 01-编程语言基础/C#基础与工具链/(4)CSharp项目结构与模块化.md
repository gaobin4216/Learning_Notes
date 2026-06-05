# C# 项目结构与模块化

## 一、标准项目结构

### 解决方案与项目

```
MySolution/
├── MySolution.sln                  # 解决方案文件
├── src/
│   ├── MyApp/                      # 主应用项目
│   │   ├── MyApp.csproj            # 项目文件
│   │   ├── Program.cs              # 入口点
│   │   ├── Controllers/
│   │   ├── Models/
│   │   ├── Services/
│   │   └── appsettings.json        # 配置文件
│   └── MyLibrary/                  # 类库项目
│       ├── MyLibrary.csproj
│       └── Helpers/
├── tests/
│   └── MyApp.Tests/               # 测试项目
│       ├── MyApp.Tests.csproj
│       └── Services/
└── Directory.Build.props           # 共享构建属性
```

### 项目类型

| 项目类型 | 说明 | 模板命令 |
|----------|------|----------|
| **Console App** | 控制台应用 | `dotnet new console` |
| **Class Library** | 类库 | `dotnet new classlib` |
| **Web API** | RESTful API | `dotnet new webapi` |
| **MVC** | Web 应用 | `dotnet new mvc` |
| **Blazor** | 前端框架 | `dotnet new blazor` |
| **Worker** | 后台服务 | `dotnet new worker` |
| **xUnit** | 测试项目 | `dotnet new xunit` |

---

## 二、命名空间与访问控制

### 命名空间声明

```csharp
namespace MyApp.Models;

public class User
{
    public string Name { get; set; } = string.Empty;
    public int Age { get; set; }
}
```

> **C# 10+** 支持文件作用域命名空间，减少一层缩进。

### 命名空间命名规范

```
组织名.项目名.模块名
MyApp.Models
MyApp.Services
MyApp.Controllers
```

### 访问修饰符

| 修饰符 | 同类 | 同程序集 | 子类 | 其他程序集 |
|--------|------|----------|------|------------|
| `public` | ✅ | ✅ | ✅ | ✅ |
| `internal` | ✅ | ✅ | ❌ | ❌ |
| `protected` | ✅ | ❌ | ✅ | ❌ |
| `private` | ✅ | ❌ | ❌ | ❌ |

---

## 三、程序集（Assembly）

程序集是 .NET 的部署单元，是编译后的 `.dll` 或 `.exe` 文件，包含 IL 代码和元数据。

### 程序集的组成

```
程序集（Assembly）
├── 清单（Manifest）      → 程序集名称、版本、引用
├── 类型元数据            → 类、接口、方法定义
├── IL 代码               → 编译后的中间语言代码
└── 资源                  → 嵌入式资源、图片等
```

### 程序集引用

```xml
<!-- 引用其他项目 -->
<ItemGroup>
    <ProjectReference Include="../MyLibrary/MyLibrary.csproj" />
</ItemGroup>

<!-- 引用 NuGet 包 -->
<ItemGroup>
    <PackageReference Include="Newtonsoft.Json" Version="13.0.3" />
</ItemGroup>
```

---

## 四、依赖注入（DI）

.NET 内置了依赖注入容器，是现代 .NET 开发的核心模式。

### 注册服务

```csharp
// Program.cs
var builder = WebApplication.CreateBuilder(args);

builder.Services.AddScoped<IUserService, UserService>();      // 每个请求一个实例
builder.Services.AddSingleton<ICacheService, CacheService>(); // 全局单例
builder.Services.AddTransient<IEmailService, EmailService>(); // 每次调用一个实例
```

### 生命周期

| 生命周期 | 方法 | 说明 |
|----------|------|------|
| **Transient** | `AddTransient` | 每次请求创建新实例 |
| **Scoped** | `AddScoped` | 每个请求作用域一个实例 |
| **Singleton** | `AddSingleton` | 全局单例 |

### 使用依赖注入

```csharp
public class UserController : ControllerBase
{
    private readonly IUserService _userService;

    // 构造函数注入
    public UserController(IUserService userService)
    {
        _userService = userService;
    }
}
```

---

## 五、常用设计模式

### 项目分层架构

```
Controllers/     ← 接收请求，调用 Service
Services/        ← 业务逻辑
Models/          ← 数据模型
Repositories/    ← 数据访问
Interfaces/      ← 接口定义
Configuration/   ← 配置类
Middleware/      ← 中间件
```

---

## 六、测试

### xUnit 基本用法

```csharp
using Xunit;

public class CalculatorTests
{
    [Fact]
    public void Add_TwoNumbers_ReturnsSum()
    {
        var calc = new Calculator();
        Assert.Equal(5, calc.Add(2, 3));
    }

    [Theory]
    [InlineData(1, 1, 2)]
    [InlineData(-1, 1, 0)]
    public void Add_MultipleCases_ReturnsCorrectResult(int a, int b, int expected)
    {
        var calc = new Calculator();
        Assert.Equal(expected, calc.Add(a, b));
    }
}
```

运行测试：`dotnet test`

### Mock 框架（Moq）

```csharp
using Moq;

var mockRepo = new Mock<IUserRepository>();
mockRepo.Setup(r => r.GetById(1)).Returns(new User { Id = 1, Name = "Test" });

var service = new UserService(mockRepo.Object);
var user = service.GetById(1);
```
