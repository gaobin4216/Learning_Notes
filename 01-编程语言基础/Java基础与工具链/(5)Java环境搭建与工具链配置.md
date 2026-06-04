# Java 环境搭建与工具链配置

## 一、JDK 安装

### 推荐 JDK 发行版

| 发行版 | 说明 | 下载地址 |
|--------|------|----------|
| **Adoptium Temurin** | Eclipse 基金会，推荐 | adoptium.net |
| **Amazon Corretto** | AWS 维护 | aws.amazon.com/corretto |
| **Oracle JDK** | 官方版，生产环境需付费 | oracle.com/java |
| **GraalVM** | 高性能多语言 VM | graalvm.org |

### Windows 安装

```powershell
# 方式一：winget（推荐）
winget install EclipseAdoptium.Temurin.21.JDK

# 方式二：Scoop
scoop install temurin21-jdk

# 方式三：手动安装
# 从 adoptium.net 下载安装包，运行安装
```

### 配置环境变量

```powershell
# 设置 JAVA_HOME
setx JAVA_HOME "C:\Program Files\Eclipse Adoptium\jdk-21.0.2.13-hotspot"

# 添加到 PATH（安装程序通常会自动配置）
setx PATH "%JAVA_HOME%\bin;%PATH%"
```

### 验证安装

```bash
java -version
javac -version
```

### macOS / Linux

```bash
# macOS（Homebrew）
brew install temurin@21

# Ubuntu
sudo apt install openjdk-21-jdk

# 多版本管理（推荐 SDKMAN）
curl -s "https://get.sdkman.io" | bash
sdk list java
sdk install java 21.0.2-tem
```

---

## 二、IDE 安装（IntelliJ IDEA）

1. 下载 [IntelliJ IDEA](https://www.jetbrains.com/idea/)
2. 安装 Community 版（免费）或 Ultimate 版
3. 首次启动时配置 JDK
4. 安装推荐插件：
   - Lombok
   - Maven Helper / Gradle
   - MyBatisX（如使用 MyBatis）
   - SonarLint

---

## 三、构建工具配置

### Maven 配置

下载 [Maven](https://maven.apache.org/download.cgi)，解压后配置环境变量。

镜像加速 `~/.m2/settings.xml`：

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

### Gradle 配置

推荐使用 **Gradle Wrapper**，无需手动安装。项目根目录执行：

```bash
# 生成 Wrapper（需先安装 Gradle）
gradle wrapper

# 之后用 gradlew 代替 gradle
./gradlew build
```

镜像加速 `build.gradle`：

```groovy
repositories {
    maven { url 'https://maven.aliyun.com/repository/public' }
    mavenCentral()
}
```

---

## 四、第一个 Java 项目

### 命令行方式

```bash
# 创建目录
mkdir hello && cd hello

# 编写代码
cat > Hello.java << 'EOF'
public class Hello {
    public static void main(String[] args) {
        System.out.println("Hello, Java!");
    }
}
EOF

# 编译运行
javac Hello.java
java Hello
```

### IntelliJ IDEA 方式

1. `File → New → Project → Java`
2. 选择 JDK，填写项目名
3. 右键 `src → New → Java Class`
4. 编写代码，点击运行按钮

### Maven 项目

```bash
mvn archetype:generate \
    -DgroupId=com.example \
    -DartifactId=hello \
    -DarchetypeArtifactId=maven-archetype-quickstart \
    -DinteractiveMode=false

cd hello
mvn compile exec:java -Dexec.mainClass="com.example.App"
```

---

## 五、代码质量工具

| 工具 | 用途 | 集成方式 |
|------|------|----------|
| **Checkstyle** | 代码风格检查 | Maven/Gradle 插件 |
| **SpotBugs** | 静态 Bug 分析 | Maven/Gradle 插件 |
| **SonarQube** | 综合代码质量平台 | 独立服务 + 插件 |
| **Lombok** | 减少样板代码 | IDE 插件 + 依赖 |

---

## 六、常见问题

### JAVA_HOME 未设置

```bash
# 检查
echo $JAVA_HOME        # Linux/macOS
echo %JAVA_HOME%       # Windows

# 重新设置后重启终端
```

### 版本不匹配

```bash
# 检查 java 和 javac 版本是否一致
java -version
javac -version

# 确认 PATH 中的 JDK 优先级
where java    # Windows
which java    # Linux/macOS
```

### Maven 下载慢

配置阿里云镜像（见上方 Maven 配置），或使用公司内部私服。
