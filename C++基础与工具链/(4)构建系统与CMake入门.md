# 构建工具与 CMake

## 一、构建工具生态总览

### 为什么要分三层

编译一个 C++ 程序，需要解决三个不同的问题：

| 问题 | 谁来解决 | 举例 |
|------|----------|------|
| **怎么翻译代码？** | 编译器 | GCC、Clang、MSVC |
| **怎么管理多文件的编译顺序和依赖？** | 构建系统 | Make、Ninja、MSBuild |
| **怎么在不同平台上生成统一的构建规则？** | 构建系统生成器 | CMake、Meson、Autotools |

### 三层架构

```
┌─────────────────────────────────────────────────────────────┐
│  第一层：构建系统生成器（生成规则文件）                        │
│    CMake、Meson、Autotools、qmake、Premake                   │
│    输入：CMakeLists.txt / meson.build / configure.ac          │
│    输出：Makefile / build.ninja / .sln                        │
├─────────────────────────────────────────────────────────────┤
│  第二层：构建系统（读取规则，调度编译）                        │
│    Make、Ninja、MSBuild、nmake、Bazel                         │
│    输入：Makefile / build.ninja / .sln                        │
│    输出：调用编译器命令，生成 .o/.obj，再链接为可执行文件       │
├─────────────────────────────────────────────────────────────┤
│  第三层：编译器（实际翻译代码）                                │
│    GCC、Clang、MSVC (cl.exe)                                  │
│    输入：.cpp 源文件                                          │
│    输出：.o/.obj 目标文件 → 链接 → .exe/.so/.a                │
└─────────────────────────────────────────────────────────────┘
```

### 一条完整的构建链路

以"用 CMake + Make + GCC 在 Linux 上编译一个多文件项目"为例：

```
开发者写的文件：
  CMakeLists.txt（告诉 CMake 有哪些源文件、要生成什么）
  main.cpp、utils.cpp

第一步：CMake 读取 CMakeLists.txt，生成 Makefile
  $ cmake ..
  -- Configuring done
  -- Generating done
  -- Build files written to: /project/build/Makefile    ← 生成了 Makefile

第二步：Make 读取 Makefile，按规则调用 GCC
  $ make
  /usr/bin/g++ -c main.cpp -o main.o                    ← Make 调用 GCC 编译
  /usr/bin/g++ -c utils.cpp -o utils.o                   ← Make 调用 GCC 编译
  /usr/bin/g++ main.o utils.o -o MyApp                   ← Make 调用 GCC 链接

第三步：运行
  $ ./MyApp
```

**再看 Windows 上用 CMake + MSBuild + MSVC 的同一条路**：

```
$ cmake ..                                     ← CMake 生成 .sln/.vcxproj
$ cmake --build .                              ← 底层调用 MSBuild
  MSBuild.exe MyApp.sln /p:Configuration=Release  ← MSBuild 调用 cl.exe 编译
  cl.exe /c main.cpp /Fo main.obj                ← MSVC 编译
  cl.exe /c utils.cpp /Fo utils.obj
  link.exe main.obj utils.obj /OUT:MyApp.exe     ← MSVC 链接
```

**同源码、同 CMakeLists.txt，只是生成器不同，就适配了不同平台。** 这就是三层架构的价值。

### 各层工具速查

| 层级 | 工具 | 定位 | 平台 |
|------|------|------|------|
| **编译器** | GCC | GNU 编译器，Linux 标准 | Linux/macOS/Windows(MSYS2) |
| | Clang | LLVM 前端，错误信息友好 | 全平台 |
| | MSVC (cl.exe) | 微软编译器，Windows 原生 | Windows |
| **构建系统** | GNU Make | Unix 标准，读 Makefile | Linux/macOS/Windows(MSYS2) |
| | Ninja | 极速构建，由生成器产生 | 全平台 |
| | MSBuild | VS 底层引擎，读 .sln | Windows |
| | nmake | 微软的 make，读 makefile | Windows |
| **生成器** | CMake | 行业标准，跨平台首选 | 全平台 |
| | Meson | 语法简洁，生成 Ninja | 全平台 |
| | Autotools | GNU 传统，生成 Makefile | Linux/macOS |
| | qmake | Qt 专用 | 全平台 |

---

## 二、构建系统

### 1. GNU Make

Unix/Linux 下的标准构建工具，读取 Makefile 执行编译规则。

Makefile 基本语法：**目标 + 依赖 + 命令**

```makefile
# 目标: 依赖
#     命令（必须以 Tab 开头）
hello: hello.c
	gcc hello.c -o hello

clean:
	rm -f hello
```

特点：
- 通过比较文件修改时间决定是否重新编译（增量构建）
- Linux/macOS 默认自带，Windows 需通过 MSYS2/MinGW 安装
- 命令：`make`（构建）、`make clean`（清理）

### 2. Ninja

Google 开发的轻量级构建系统，设计目标是**极致的构建速度**。

| 对比 | Make | Ninja |
|------|------|-------|
| **定位** | 通用构建工具 | 专注于速度的构建工具 |
| **Makefile** | 手写可读 | 不建议手写（由生成器产生） |
| **并行构建** | `make -j4` | 默认并行 |
| **增量构建** | 基于时间戳 | 基于时间戳 + 内容哈希 |
| **使用场景** | 直接使用 | CMake/Meson 的后端 |

```bash
# CMake 生成 Ninja 构建文件
cmake -G Ninja ..
# 执行构建
ninja
```

### 3. MSBuild

微软的构建平台，Visual Studio 的底层构建引擎。

- 项目文件格式：`.sln`（解决方案）、`.vcxproj`（C++ 项目）、`.csproj`（C# 项目）
- 在 VS 中点击"生成"时，实际就是调用 MSBuild
- 也可以命令行使用：`msbuild MyProject.sln /p:Configuration=Release`

```powershell
# 命令行构建
msbuild MyProject.sln /p:Configuration=Release /p:Platform=x64

# 或通过 CMake 生成 VS 工程后构建
cmake --build . --config Release
```

### 4. 其他构建系统

| 构建系统 | 说明 |
|----------|------|
| **nmake** | 微软的 make 实现，语法类似 GNU Make，随 VS 安装 |
| **qmake** | Qt 框架的构建工具，生成 Makefile 或 VS 工程 |
| **Bazel** | Google 开源，适合超大型项目（单体仓库），支持多语言 |
| **SCons** | Python 编写的构建系统，用 Python 脚本替代 Makefile |
| **Meson** | 高速构建系统，生成 Ninja 文件，语法简洁 |

---

## 三、构建系统生成器

### 1. CMake

CMake 是跨平台的构建系统生成器，它本身不编译代码，而是根据 CMakeLists.txt 生成构建文件。

**CMake 的角色**："总设计师"——生成蓝图，施工队（Make、Ninja、MSBuild）按蓝图干活。

| CMake 生成器（-G） | 生成的文件 | 交给谁用 |
|---------------------|-----------|----------|
| `"Unix Makefiles"` | Makefile | GNU Make |
| `Ninja` | build.ninja | Ninja |
| `"Visual Studio 17 2022"` | .sln / .vcxproj | MSBuild / VS |
| `"Xcode"` | .xcodeproj | Xcode |
| `"MinGW Makefiles"` | Makefile | MinGW Make |

```bash
# 默认生成器（Linux 下是 Make，Windows + VS 下是 VS 工程）
cmake ..

# 指定生成器
cmake -G Ninja ..
cmake -G "MinGW Makefiles" ..
cmake -G "Visual Studio 17 2022" -A x64 ..
```

**CMake 不需要 VS Code 的 tasks.json/launch.json**：CMake 自动找到编译器、头文件、库，生成编译规则。VS Code 只要安装 CMake Tools 插件，识别 CMakeLists.txt 即可。

### 2. Meson

新兴的构建系统生成器，语法比 CMake 更简洁，生成 Ninja 文件。

```meson
# meson.build
project('hello', 'c')
executable('hello', 'main.c')
```

```bash
meson setup build
cd build
ninja
```

### 3. Autotools（autoconf + automake）

GNU 传统的构建系统生成器，生成 Makefile。配置复杂但历史悠久，许多老牌开源项目使用。

```bash
./configure
make
make install
```

### 4. 生成器对比

| 生成器 | 配置语言 | 生成目标 | 学习曲线 | 适用场景 |
|--------|----------|----------|----------|----------|
| **CMake** | CMakeLists.txt | Make/Ninja/VS/Xcode | 中等 | 行业标准，跨平台首选 |
| **Meson** | meson.build | Ninja | 低 | 新项目，追求简洁 |
| **Autotools** | configure.ac + Makefile.am | Make | 高 | 老牌 GNU 项目 |
| **qmake** | .pro 文件 | Make/VS | 低 | Qt 项目专用 |
| **Premake** | premake5.lua | VS/Xcode/gmake | 低 | 游戏开发常用 |

---

## 四、编译器

| 编译器 | 前端 | 后端 | 平台 | 说明 |
|--------|------|------|------|------|
| **GCC** | 自有 | 自有 | Linux/macOS/Windows(MSYS2) | GNU 编译器集，支持 C/C++/Fortran 等 |
| **Clang** | 自有 | LLVM | 全平台 | 由苹果赞助，编译速度快，错误信息友好 |
| **MSVC (cl.exe)** | 自有 | 自有 | Windows | Visual Studio 自带，Windows 原生支持最好 |
| **MinGW GCC** | GCC | GCC | Windows | GCC 的 Windows 移植版 |

### 编译器前端/后端架构

```
源代码 → [前端：词法分析、语法分析、生成 AST] → 中间表示(IR) → [后端：优化、生成机器码] → 目标文件
```

LLVM 的设计允许不同语言前端（Clang、Rust、Swift）共享同一个后端，实现"一次优化，多语言受益"。

---

## 五、CMake 使用

### 1. 安装

从 [CMake 官网](https://cmake.org/download/) 下载安装包（64 位选 x86_64），安装时勾选"Add CMake to the system PATH"。

```bash
cmake --version
```

### 2. 命令行使用

以一个简单的 HelloCMake 项目为例：

```
HelloCMake/
├── CMakeLists.txt
└── HelloCMake.cpp
```

CMakeLists.txt：

```cmake
cmake_minimum_required(VERSION 3.18)
project(HelloCMake)
add_executable(HelloCMake HelloCMake.cpp)
```

**生成 + 编译**：

```bash
mkdir build && cd build
cmake ..                    # 生成构建文件
cmake --build .             # 编译（默认 Debug）
cmake --build . --config Release   # 编译（Release）
```

### 3. CMake-GUI 使用

1. 打开 CMake-GUI，设置源码目录和构建目录（建议单独建 `build` 文件夹）
2. 点击 Configure，选择编译器和生成器
3. 点击 Generate，生成构建文件
4. 点击 Open Project，用 VS 打开编译

### 4. 常用 CMake 变量

```bash
# 指定生成器
cmake -G "Ninja" ..

# 指定编译器
cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..

# 指定构建类型
cmake -DCMAKE_BUILD_TYPE=Release ..

# 指定安装路径
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
```

---

## 六、CMakeLists.txt 基础语法

```cmake
# 指定最低版本
cmake_minimum_required(VERSION 3.18)

# 定义项目名和支持的语言
project(MyApp LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行目标
add_executable(MyApp main.cpp utils.cpp parser.cpp)

# 添加静态库
add_library(mylib STATIC lib.cpp)

# 链接库
target_link_libraries(MyApp mylib)

# 添加头文件搜索路径
target_include_directories(MyApp PRIVATE include)

# 查找并链接第三方库
find_package(OpenCV REQUIRED)
target_link_libraries(MyApp ${OpenCV_LIBS})
```
