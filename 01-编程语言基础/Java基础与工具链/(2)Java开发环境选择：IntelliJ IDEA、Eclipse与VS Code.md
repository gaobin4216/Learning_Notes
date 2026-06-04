# Java 开发环境选择：IntelliJ IDEA、Eclipse 与 VS Code

## 一、核心概念速览

| 工具 | 一句话定位 | 适合人群 |
|------|-----------|----------|
| **IntelliJ IDEA** | 最智能的 Java IDE | Java 开发者（强烈推荐） |
| **Eclipse** | 老牌开源 IDE | 企业开发、插件生态 |
| **VS Code** | 轻量级编辑器 + 插件 | 轻量开发、多语言开发者 |
| **NetBeans** | Apache 开源 IDE | 教学、JavaFX 开发 |

---

## 二、IntelliJ IDEA：最强大的 Java IDE

### 版本对比

| 版本 | 价格 | 特点 |
|------|------|------|
| **Community** | 免费开源 | Java SE、Kotlin、Groovy |
| **Ultimate** | 付费 | + Web、Spring、数据库、微服务 |

> **学生优惠**：学生可通过 [JetBrains 学生计划](https://www.jetbrains.com/community/education/) 免费使用 Ultimate 版。

### 核心功能

| 功能 | 说明 |
|------|------|
| **智能代码补全** | 基于上下文的精准补全（Ctrl+Space） |
| **重构工具** | 重命名、提取方法、内联变量 |
| **调试器** | 条件断点、表达式求值、远程调试 |
| **版本控制** | Git/SVN 集成，可视化 diff |
| **数据库工具** | SQL 支持、数据查看（Ultimate） |
| **框架支持** | Spring、Jakarta EE、Micronaut（Ultimate） |
| **Maven/Gradle** | 深度集成构建工具 |

### 安装与配置

#### 1. 安装 IntelliJ IDEA

访问 [https://www.jetbrains.com/idea/](https://www.jetbrains.com/idea/) 下载安装。

#### 2. 配置 JDK

1. `File → Project Structure → Project`
2. 选择 Project SDK，点击 `Add SDK → JDK`
3. 选择 JDK 安装目录

#### 3. 配置 Maven/Gradle

`File → Settings → Build → Build Tools`：
- Maven：配置 `settings.xml` 路径和本地仓库
- Gradle：配置 Gradle 安装路径或使用 Wrapper

### 常用快捷键

| 操作 | 快捷键 |
|------|--------|
| 代码补全 | `Ctrl + Space` |
| 智能补全 | `Ctrl + Shift + Space` |
| 查找类 | `Ctrl + N` |
| 查找文件 | `Ctrl + Shift + N` |
| 重构 | `Ctrl + Alt + Shift + T` |
| 重命名 | `Shift + F6` |
| 格式化 | `Ctrl + Alt + L` |
| 运行 | `Shift + F10` |
| 调试 | `Shift + F9` |
| 查看定义 | `Ctrl + B` |
| 查找用法 | `Alt + F7` |
| 生成代码 | `Alt + Insert` |

### 项目创建

#### Maven 项目

1. `File → New → Project`
2. 选择 `Maven Archetype`
3. 选择 Archetype（如 `maven-archetype-quickstart`）
4. 填写 GroupId、ArtifactId、Version

#### Gradle 项目

1. `File → New → Project`
2. 选择 `Gradle`
3. 选择语言（Java/Kotlin/Groovy）
4. 填写 GroupId、ArtifactId

---

## 三、Eclipse：老牌开源 IDE

### 版本选择

| 版本 | 说明 |
|------|------|
| **Eclipse IDE for Java Developers** | 基础 Java 开发 |
| **Eclipse IDE for Enterprise Java** | Java EE/Web 开发 |
| **Eclipse IDE for Java Developers + Web Tools** | 综合开发 |

### 安装

1. 访问 [https://www.eclipse.org/downloads/](https://www.eclipse.org/downloads/)
2. 下载 Eclipse Installer
3. 选择版本并安装

### 核心功能

| 功能 | 说明 |
|------|------|
| **代码补全** | Content Assist（Ctrl+Space） |
| **重构** | 丰富的重构工具 |
| **调试** | 断点、条件断点、表达式监视 |
| **插件系统** | Eclipse Marketplace 海量插件 |
| **Maven 集成** | m2e 插件 |
| **Git 集成** | EGit 插件 |

### 常用快捷键

| 操作 | 快捷键 |
|------|--------|
| 代码补全 | `Ctrl + Space` |
| 快速修复 | `Ctrl + 1` |
| 格式化 | `Ctrl + Shift + F` |
| 组织 import | `Ctrl + Shift + O` |
| 查找类 | `Ctrl + Shift + T` |
| 重命名 | `Alt + Shift + R` |
| 运行 | `Ctrl + F11` |
| 调试 | `F11` |

### Eclipse vs IntelliJ IDEA

| 特性 | IntelliJ IDEA | Eclipse |
|------|---------------|---------|
| **启动速度** | 中等 | 较快 |
| **内存占用** | 较大 | 中等 |
| **开箱即用** | 功能完整 | 需安装插件 |
| **智能补全** | 非常强大 | 一般 |
| **重构能力** | 强大 | 良好 |
| **插件生态** | 丰富 | 非常丰富 |
| **价格** | Community 免费 | 完全免费开源 |
| **学习曲线** | 低 | 中等 |

> **选择建议**：
> - 新项目 / 个人开发 → IntelliJ IDEA
> - 企业已有 Eclipse 项目 → Eclipse
> - 预算有限 → Eclipse 或 IntelliJ IDEA Community

---

## 四、VS Code：轻量级编辑器

### 安装与配置

#### 1. 安装 Java 扩展

按 `Ctrl+Shift+X`，搜索并安装：

| 扩展 | 说明 |
|------|------|
| **Extension Pack for Java** | 微软官方 Java 扩展包（必装） |
| **Spring Boot Extension Pack** | Spring Boot 支持 |
| **Gradle for Java** | Gradle 支持 |
| **Maven for Java** | Maven 支持 |

#### 2. 配置 JDK

`.vscode/settings.json`：

```json
{
    "java.jdt.ls.java.home": "C:/Program Files/Java/jdk-21",
    "java.configuration.runtimes": [
        {
            "name": "JavaSE-17",
            "path": "C:/Program Files/Java/jdk-17",
            "default": true
        },
        {
            "name": "JavaSE-21",
            "path": "C:/Program Files/Java/jdk-21"
        }
    ],
    "java.compile.nullAnalysis.mode": "automatic",
    "java.format.settings.profile": "GoogleStyle"
}
```

#### 3. 调试配置

`.vscode/launch.json`：

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "type": "java",
            "name": "Launch Current File",
            "request": "launch",
            "mainClass": "${file}"
        },
        {
            "type": "java",
            "name": "Launch Main Class",
            "request": "launch",
            "mainClass": "com.example.Main",
            "projectName": "myproject"
        }
    ]
}
```

### VS Code vs IntelliJ IDEA

| 特性 | VS Code | IntelliJ IDEA |
|------|---------|---------------|
| **启动速度** | 快 | 中等 |
| **内存占用** | 小（~300MB） | 大（~1-2GB） |
| **智能补全** | 基础 | 强大 |
| **重构能力** | 有限 | 强大 |
| **框架支持** | 通过插件 | 深度集成 |
| **Maven/Gradle** | 基础支持 | 深度集成 |
| **价格** | 免费 | Community 免费 |

> **选择建议**：
> - Java 专业开发 → IntelliJ IDEA
> - 轻量查看/编辑 → VS Code
> - 多语言混合开发 → VS Code

---

## 五、JDK 安装与管理

### 常见 JDK 发行版

| 发行版 | 维护者 | 许可证 | 说明 |
|--------|--------|--------|------|
| **Oracle JDK** | Oracle | 商业（生产环境需付费） | 官方版本 |
| **OpenJDK** | 开源社区 | GPL v2 | 开源标准 |
| **Adoptium (Eclipse Temurin)** | Eclipse 基金会 | GPL v2 | 推荐的免费发行版 |
| **Amazon Corretto** | Amazon | GPL v2 | AWS 优化 |
| **Azul Zulu** | Azul Systems | GPL v2 | 多平台支持 |
| **GraalVM** | Oracle | GPL v2 | 高性能多语言 VM |

> **推荐**：个人学习使用 Adoptium Temurin 或 Amazon Corretto。

### Windows 安装 JDK

#### 方式一：手动安装

1. 访问 [Adoptium](https://adoptium.net/) 下载 JDK
2. 运行安装程序
3. 配置环境变量：

```powershell
# 设置 JAVA_HOME
setx JAVA_HOME "C:\Program Files\Eclipse Adoptium\jdk-21.0.2.13-hotspot"

# 添加到 PATH
setx PATH "%JAVA_HOME%\bin;%PATH%"
```

#### 方式二：使用包管理器

```powershell
# 使用 winget（Windows 11）
winget install EclipseAdoptium.Temurin.21.JDK

# 使用 Scoop
scoop install temurin21-jdk

# 使用 Chocolatey
choco install temurin21
```

### 多版本管理

#### SDKMAN（Linux/macOS）

```bash
# 安装 SDKMAN
$ curl -s "https://get.sdkman.io" | bash

# 列出可用 JDK
$ sdk list java

# 安装 JDK
$ sdk install java 21.0.2-tem

# 切换版本
$ sdk use java 17.0.9-tem

# 设置默认版本
$ sdk default java 21.0.2-tem
```

#### Windows 手动管理

```powershell
# 切换 JAVA_HOME
setx JAVA_HOME "C:\Program Files\Eclipse Adoptium\jdk-17.0.9.9-hotspot"
```

---

## 六、环境选择总结

| 场景 | 推荐工具 |
|------|----------|
| **Java 专业开发** | IntelliJ IDEA Ultimate |
| **日常 Java 开发** | IntelliJ IDEA Community（推荐） |
| **企业级 Web 开发** | IntelliJ IDEA + Spring |
| **轻量开发/学习** | VS Code + Extension Pack for Java |
| **团队协作/大型项目** | IntelliJ IDEA + Maven/Gradle |
| **学生学习** | IntelliJ IDEA Community 或 Eclipse |
