# 构建工具与依赖管理：Maven 与 Gradle

## 一、为什么需要构建工具？

手动管理 Java 项目的编译、测试、打包和依赖非常繁琐。构建工具自动化了这些流程。

| 问题 | 构建工具如何解决 |
|------|-----------------|
| 依赖管理 | 自动下载和管理第三方库 |
| 编译打包 | 一条命令完成编译、测试、打包 |
| 项目结构 | 约定标准目录结构 |
| 可复现性 | 锁定依赖版本，团队环境一致 |

---

## 二、Maven

### 简介

Apache Maven 是最经典的 Java 构建工具，使用 XML 配置（`pom.xml`），约定优于配置。

### 标准目录结构

```
myproject/
├── pom.xml
├── src/
│   ├── main/
│   │   ├── java/         # 源代码
│   │   ├── resources/    # 资源文件
│   │   └── webapp/       # Web 应用文件
│   └── test/
│       ├── java/         # 测试代码
│       └── resources/    # 测试资源
└── target/               # 编译输出（自动生成）
```

### pom.xml 核心配置

```xml
<project>
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>my-app</artifactId>
    <version>1.0.0</version>
    <packaging>jar</packaging>

    <properties>
        <maven.compiler.source>17</maven.compiler.source>
        <maven.compiler.target>17</maven.compiler.target>
    </properties>

    <dependencies>
        <dependency>
            <groupId>org.apache.commons</groupId>
            <artifactId>commons-lang3</artifactId>
            <version>3.14.0</version>
        </dependency>
        <dependency>
            <groupId>junit</groupId>
            <artifactId>junit</artifactId>
            <version>4.13.2</version>
            <scope>test</scope>
        </dependency>
    </dependencies>
</project>
```

### 常用命令

```bash
mvn clean           # 清理 target 目录
mvn compile         # 编译
mvn test            # 运行测试
mvn package         # 打包（jar/war）
mvn install         # 安装到本地仓库
mvn clean package   # 清理 + 编译 + 测试 + 打包
mvn dependency:tree # 查看依赖树
```

### 镜像配置（国内加速）

`~/.m2/settings.xml`：

```xml
<settings>
    <mirrors>
        <mirror>
            <id>aliyun</id>
            <mirrorOf>central</mirrorOf>
            <url>https://maven.aliyun.com/repository/central</url>
        </mirror>
    </mirrors>
</settings>
```

---

## 三、Gradle

### 简介

Gradle 是更现代的构建工具，使用 Groovy 或 Kotlin DSL 配置，比 Maven 更灵活简洁。

### 标准目录结构

与 Maven 相同：`src/main/java`、`src/test/java` 等。

### build.gradle（Groovy DSL）

```groovy
plugins {
    id 'java'
}

group = 'com.example'
version = '1.0.0'

java {
    sourceCompatibility = JavaVersion.VERSION_17
}

repositories {
    mavenCentral()
}

dependencies {
    implementation 'org.apache.commons:commons-lang3:3.14.0'
    testImplementation 'junit:junit:4.13.2'
}
```

### 常用命令

```bash
./gradlew build          # 编译 + 测试 + 打包
./gradlew clean          # 清理
./gradlew test           # 运行测试
./gradlew run            # 运行应用（需 application 插件）
./gradlew dependencies   # 查看依赖树
```

> **推荐使用 Gradle Wrapper**（`gradlew`），团队成员无需手动安装 Gradle。

---

## 四、Maven vs Gradle

| 特性 | Maven | Gradle |
|------|-------|--------|
| **配置格式** | XML（pom.xml） | Groovy/Kotlin DSL |
| **配置量** | 较多 | 简洁 |
| **构建速度** | 较慢 | 快（增量构建、缓存） |
| **灵活性** | 约定优先 | 高度灵活 |
| **学习曲线** | 低 | 中等 |
| **生态成熟度** | 非常成熟 | 成熟 |
| **Android** | 不支持 | 官方构建工具 |

> **选择建议**：新项目推荐 Gradle；已有 Maven 项目继续用 Maven 即可。

---

## 五、依赖范围（Scope）

| Scope | Maven | Gradle | 说明 |
|-------|-------|--------|------|
| 编译+运行 | `compile` | `implementation` | 默认，主代码和运行时需要 |
| 仅编译 | `provided` | `compileOnly` | 编译需要，运行时由容器提供 |
| 仅测试 | `test` | `testImplementation` | 只在测试代码中使用 |
| 运行时 | `runtime` | `runtimeOnly` | 编译不需要，运行时需要 |
