# C# 项目结构与模块化

## 一、解决方案与项目的关系

### 什么是解决方案（Solution）？

解决方案（`.sln` 文件）是 Visual Studio 的概念，用于**把多个相关项目组织在一起**。

```
为什么需要解决方案？

一个真实的软件通常由多个部分组成：
├── 主程序（Web API）
├── 共享类库（通用工具）
├── 数据访问层（数据库操作）
└── 单元测试

如果没有解决方案，你需要分别打开每个项目。
有了解决方案，打开一个 .sln 文件就能看到所有项目。
```

### 什么是项目（Project）？

项目（`.csproj` 文件）是编译的最小单位。每个项目编译后生成一个 `.dll`（类库）或 `.exe`（可执行程序）。

### 标准目录结构

```
MySolution/                          ← 解决方案根目录
├── MySolution.sln                   ← 解决方案文件
├── Directory.Build.props            ← 共享构建属性（可选）
├── Directory.Packages.props         ← 中央包管理（可选）
│
├── src/                             ← 源代码目录
│   ├── MyApp/                       ← 主应用项目
│   │   ├── MyApp.csproj             ← 项目文件
│   │   ├── Program.cs               ← 入口点（Main 方法）
│   │   ├── appsettings.json         ← 配置文件
│   │   ├── Controllers/             ← API 控制器
│   │   ├── Models/                  ← 数据模型
│   │   ├── Services/                ← 业务逻辑
│   │   ├── Middleware/              ← 中间件
│   │   └── Configuration/           ← 配置类
│   │
│   └── MyApp.Core/                  ← 共享类库项目
│       ├── MyApp.Core.csproj
│       ├── Interfaces/              ← 接口定义
│       ├── Entities/                ← 实体类
│       └── Helpers/                 ← 工具类
│
├── tests/                           ← 测试目录
│   └── MyApp.Tests/                 ← 测试项目
│       ├── MyApp.Tests.csproj
│       ├── Controllers/             ← 控制器测试
│       └── Services/                ← 服务测试
│
└── docs/                            ← 文档目录
```

### 项目类型

| 项目类型 | 说明 | 模板命令 | 输出 |
|----------|------|----------|------|
| **Console App** | 控制台应用 | `dotnet new console` | .exe |
| **Class Library** | 类库（被其他项目引用） | `dotnet new classlib` | .dll |
| **Web API** | RESTful API 服务 | `dotnet new webapi` | .dll |
| **MVC** | Web 应用（Model-View-Controller） | `dotnet new mvc` | .dll |
| **Blazor** | C# 前端框架 | `dotnet new blazor` | .dll |
| **Worker** | 后台服务（定时任务、消息处理） | `dotnet new worker` | .dll |
| **xUnit** | 单元测试项目 | `dotnet new xunit` | .dll |
| **MAUI** | 跨平台移动/桌面应用 | `dotnet new maui` | .exe |

---

## 二、程序集（Assembly）

### 什么是程序集？

程序集是 .NET 的**部署单元**，就是编译后的 `.dll` 或 `.exe` 文件。它不只是机器码，还包含了丰富的元数据。

### 程序集的组成

```
程序集（Assembly）= .dll 或 .exe 文件
├── 清单（Manifest）
│   → 程序集名称、版本号、文化信息
│   → 引用的其他程序集列表
│   → 安全权限信息
│
├── 类型元数据（Metadata）
│   → 类、接口、结构体的定义
│   → 方法签名、属性、字段
│   → 自定义特性（Attribute）
│
├── IL 代码（IL Code）
│   → 编译后的中间语言代码
│   → 由 CLR 的 JIT 编译器在运行时翻译成机器码
│
└── 资源（Resources）
    → 嵌入式资源（图片、配置文件）
    → 字符串表（多语言支持）
```

### 程序集引用

一个项目可以引用其他项目或 NuGet 包：

```xml
<ItemGroup>
    <!-- 引用同一个解决方案中的其他项目 -->
    <ProjectReference Include="../MyApp.Core/MyApp.Core.csproj" />
</ItemGroup>

<ItemGroup>
    <!-- 引用 NuGet 包 -->
    <PackageReference Include="Newtonsoft.Json" Version="13.0.3" />
</ItemGroup>
```

**ProjectReference vs PackageReference：**
- **ProjectReference**：引用自己写的项目，编译时一起编译
- **PackageReference**：引用第三方 NuGet 包，使用预编译的 .dll

---

## 三、命名空间与访问控制

### 命名空间的作用

命名空间用来**组织代码、避免命名冲突**。比如两个库都有 `User` 类，用命名空间区分：

```csharp
using MyApp.Models;       // 我的 User 类
using AnotherLib.Models;  // 别人的 User 类

var myUser = new MyApp.Models.User();
var otherUser = new AnotherLib.Models.User();
```

### 命名空间声明

```csharp
// C# 10+ 文件范围命名空间（推荐，减少一层缩进）
namespace MyApp.Models;

public class User
{
    public string Name { get; set; } = string.Empty;
    public int Age { get; set; }
}
```

```csharp
// 传统写法（C# 10 之前）
namespace MyApp.Models
{
    public class User
    {
        public string Name { get; set; } = string.Empty;
        public int Age { get; set; }
    }
}
```

### 命名空间命名规范

```
组织名.项目名.模块名

示例：
MyCompany.MyApp.Models          ← 数据模型
MyCompany.MyApp.Services        ← 业务逻辑
MyCompany.MyApp.Controllers     ← API 控制器
MyCompany.MyApp.Data            ← 数据访问
```

### 隐式 using（C# 10+）

在 `.csproj` 中启用 `<ImplicitUsings>enable</ImplicitUsings>` 后，以下命名空间会自动引用，不需要手动写 `using`：

```csharp
// 这些命名空间自动引用，不需要手写 using
System
System.Collections.Generic
System.IO
System.Linq
System.Net.Http
System.Threading
System.Threading.Tasks
```

### 访问修饰符

访问修饰符控制类、方法、字段的可见范围：

| 修饰符 | 同类 | 同程序集 | 子类 | 其他程序集 | 用途 |
|--------|------|----------|------|------------|------|
| `public` | ✅ | ✅ | ✅ | ✅ | 对外公开的 API |
| `internal` | ✅ | ✅ | ❌ | ❌ | 程序集内部使用（默认） |
| `protected` | ✅ | ❌ | ✅ | ❌ | 子类可以访问 |
| `private` | ✅ | ❌ | ❌ | ❌ | 类内部使用（默认） |
| `protected internal` | ✅ | ✅ | ✅ | ❌ | 子类或同程序集 |
| `private protected` | ✅ | ❌ | ✅ | ❌ | 子类且同程序集 |

```csharp
public class UserService
{
    private readonly ILogger _logger;           // 只有 UserService 能访问
    internal int RetryCount { get; set; }       // 同程序集的类能访问
    public string UserName { get; set; }        // 所有人都能访问
    protected virtual void OnError() { }        // 子类可以重写
}
```

---

## 四、依赖注入（DI）

### 什么是依赖注入？

**依赖注入（Dependency Injection，DI）** 是一种设计模式，核心思想是：**不要自己创建依赖对象，而是由外部传入**。

### 没有 DI 时的问题

```csharp
// ❌ 不好的写法：自己创建依赖
public class OrderService
{
    private readonly EmailService _emailService = new EmailService();  // 硬编码
    private readonly DatabaseContext _db = new DatabaseContext();       // 硬编码

    public void CreateOrder(Order order)
    {
        _db.Save(order);
        _emailService.Send(order.CustomerEmail, "订单已创建");
    }
}

// 问题：
// 1. 无法替换成测试用的 Mock 对象
// 2. 无法切换实现（比如从邮件换成短信）
// 3. 类之间耦合度高
```

### 使用 DI 的写法

```csharp
// ✅ 好的写法：通过构造函数接收依赖
public class OrderService
{
    private readonly IEmailService _emailService;
    private readonly IDatabaseContext _db;

    // 依赖通过构造函数"注入"进来
    public OrderService(IEmailService emailService, IDatabaseContext db)
    {
        _emailService = emailService;
        _db = db;
    }

    public void CreateOrder(Order order)
    {
        _db.Save(order);
        _emailService.Send(order.CustomerEmail, "订单已创建");
    }
}

// 好处：
// 1. 测试时可以传入 Mock 对象
// 2. 可以轻松切换实现（邮件→短信）
// 3. 类只依赖接口，不依赖具体实现
```

### .NET 内置的 DI 容器

.NET 内置了依赖注入容器，不需要第三方库：

```csharp
// Program.cs
var builder = WebApplication.CreateBuilder(args);

// 注册服务到容器
builder.Services.AddScoped<IOrderService, OrderService>();       // 每个请求一个实例
builder.Services.AddSingleton<ICacheService, CacheService>();    // 全局单例
builder.Services.AddTransient<IEmailService, EmailService>();    // 每次调用一个实例

var app = builder.Build();
```

### DI 生命周期

| 生命周期 | 方法 | 何时创建 | 何时销毁 | 适用场景 |
|----------|------|----------|----------|----------|
| **Transient** | `AddTransient` | 每次请求时创建新实例 | 请求结束 | 无状态服务 |
| **Scoped** | `Each HTTP 请求共享一个实例** | 请求结束 | 有状态的请求级服务 |
| **Singleton** | `AddSingleton` | 第一次请求时创建 | 应用关闭 | 缓存、配置、全局服务 |

**生命周期图解：**

```
请求1 进入 → 创建 Scope1
    ├── Scoped 服务：在 Scope1 内复用同一个实例
    ├── Transient 服务：每次都创建新实例
    └── Singleton 服务：全局复用
请求1 结束 → 销毁 Scope1

请求2 进入 → 创建 Scope2
    ├── Scoped 服务：创建新实例（新的 Scope）
    └── Singleton 服务：复用之前的实例
```

### 构造函数注入（最常用）

```csharp
public class UserController : ControllerBase
{
    private readonly IUserService _userService;
    private readonly ILogger<UserController> _logger;

    // 构造函数注入：容器自动解析并传入
    public UserController(IUserService userService, ILogger<UserController> logger)
    {
        _userService = userService;
        _logger = logger;
    }

    [HttpGet("{id}")]
    public ActionResult<User> GetById(int id)
    {
        _logger.LogInformation("查询用户 {Id}", id);
        var user = _userService.GetById(id);
        return Ok(user);
    }
}
```

---

## 五、常用设计模式

### 项目分层架构

```
Controllers/     ← 接收 HTTP 请求，调用 Service，返回响应
Services/        ← 业务逻辑（核心代码在这里）
Models/          ← 数据模型（DTO、Entity）
Repositories/    ← 数据访问（数据库操作）
Interfaces/      ← 接口定义（定义契约）
Configuration/   ← 配置类（强类型配置）
Middleware/      ← 中间件（请求管道中的处理逻辑）
```

### 典型的调用链

```
HTTP 请求
    ↓
Controller（接收请求，参数验证）
    ↓
Service（业务逻辑处理）
    ↓
Repository（数据库查询）
    ↓
Database（SQL Server / PostgreSQL）
    ↓
返回结果，层层返回
```

---

## 六、测试

### 为什么需要测试？

测试能保证你的代码在修改后不会出问题。没有测试的代码就像没有安全网的高空作业。

### xUnit 基本用法

xUnit 是 .NET 最流行的单元测试框架：

```csharp
using Xunit;

public class CalculatorTests
{
    // [Fact] 表示一个独立的测试方法
    [Fact]
    public void Add_TwoNumbers_ReturnsSum()
    {
        var calc = new Calculator();
        var result = calc.Add(2, 3);
        Assert.Equal(5, result);
    }

    // [Theory] + [InlineData] 表示参数化测试
    [Theory]
    [InlineData(1, 1, 2)]
    [InlineData(-1, 1, 0)]
    [InlineData(0, 0, 0)]
    public void Add_MultipleCases_ReturnsCorrectResult(int a, int b, int expected)
    {
        var calc = new Calculator();
        Assert.Equal(expected, calc.Add(a, b));
    }
}
```

### 运行测试

```bash
# 运行所有测试
dotnet test

# 运行特定项目的测试
dotnet test tests/MyApp.Tests/MyApp.Tests.csproj

# 运行特定测试方法
dotnet test --filter "Add_TwoNumbers_ReturnsSum"
```

### Mock 框架（Moq）

Mock 用来**模拟依赖对象**，让测试只关注被测代码本身：

```csharp
using Moq;

[Fact]
public void GetUser_ExistingId_ReturnsUser()
{
    // 创建 Mock 对象
    var mockRepo = new Mock<IUserRepository>();

    // 设置 Mock 行为：当调用 GetById(1) 时，返回指定的 User
    mockRepo.Setup(r => r.GetById(1))
            .Returns(new User { Id = 1, Name = "Test" });

    // 用 Mock 对象创建被测服务
    var service = new UserService(mockRepo.Object);

    // 执行测试
    var user = service.GetById(1);

    // 验证结果
    Assert.Equal("Test", user.Name);

    // 验证 GetById(1) 被调用了一次
    mockRepo.Verify(r => r.GetById(1), Times.Once);
}
```
