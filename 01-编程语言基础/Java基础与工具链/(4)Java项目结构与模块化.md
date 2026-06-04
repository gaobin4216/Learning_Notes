# Java 项目结构与模块化

## 一、标准项目结构

### Maven/Gradle 约定结构

```
myproject/
├── pom.xml / build.gradle      # 构建配置
├── src/
│   ├── main/
│   │   ├── java/               # 源代码
│   │   │   └── com/example/
│   │   │       ├── App.java
│   │   │       ├── model/
│   │   │       │   └── User.java
│   │   │       └── service/
│   │   │           └── UserService.java
│   │   └── resources/          # 配置文件、资源
│   │       └── application.properties
│   └── test/
│       └── java/
│           └── com/example/
│               └── AppTest.java
└── target/ / build/            # 编译输出
```

### 包（Package）命名规范

```
组织域名反转.项目名.模块名
com.example.myproject.service
com.example.myproject.model
com.example.myproject.controller
```

---

## 二、包与访问控制

### 包声明

```java
package com.example.myproject.model;

public class User {
    private String name;
    private int age;
    // ...
}
```

### 访问修饰符

| 修饰符 | 同类 | 同包 | 子类 | 其他包 |
|--------|------|------|------|--------|
| `public` | ✅ | ✅ | ✅ | ✅ |
| `protected` | ✅ | ✅ | ✅ | ❌ |
| 默认（无修饰符） | ✅ | ✅ | ❌ | ❌ |
| `private` | ✅ | ❌ | ❌ | ❌ |

---

## 三、Java 模块系统（JPMS，Java 9+）

### 什么是模块？

Java 9 引入的模块系统（Java Platform Module System），用于解决大型项目的依赖和封装问题。

### 模块声明

```
myproject/
├── src/
│   └── com.example.app/
│       ├── module-info.java
│       └── com/example/app/
│           └── Main.java
```

```java
// module-info.java
module com.example.app {
    requires java.sql;           // 依赖 java.sql 模块
    requires com.example.lib;    // 依赖另一个模块
    exports com.example.app.api; // 对外暴露的包
}
```

### 模块化的意义

| 作用 | 说明 |
|------|------|
| **强封装** | 只有 `exports` 的包才能被外部访问 |
| **显式依赖** | `requires` 声明所有依赖 |
| **性能优化** | JVM 可以裁剪不需要的模块 |
| **安全性** | 内部 API 不可被外部访问 |

---

## 四、常用设计模式

### 项目分层架构

```
controller/    ← 接收请求，调用 service
    └── UserController.java
service/       ← 业务逻辑
    └── UserService.java
model/         ← 数据模型
    └── User.java
repository/    ← 数据访问
    └── UserRepository.java
config/        ← 配置类
    └── AppConfig.java
util/          ← 工具类
    └── StringUtils.java
```

---

## 五、测试

### JUnit 5 基本用法

```java
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class CalculatorTest {

    @Test
    void testAdd() {
        Calculator calc = new Calculator();
        assertEquals(5, calc.add(2, 3));
    }

    @Test
    void testDivideByZero() {
        Calculator calc = new Calculator();
        assertThrows(ArithmeticException.class, () -> calc.divide(1, 0));
    }
}
```

### 测试目录

```
src/test/java/com/example/
├── service/
│   └── UserServiceTest.java    # 与源代码对应
└── model/
    └── UserTest.java
```

运行测试：`mvn test` 或 `./gradlew test`
