# POSIX
​可移植操作系统接口​​，Portable Operating System Interface，是​​由IEEE制定的标准族​​，旨在为不同UNIX操作系统提供统一的应用程序接口（API），确保软件能在兼容系统上无缝移植
# Cygwin与MinGW区别
### Cygwin用于在Windows上模拟Unix环境并移植unix程序
（将unix api翻译成windows api）
### MinGW用于在Windows上使用GNU工具链开发原生Windows应用
​​（直接调用windows api）
## Cygwin
* Cygwin 是运行在 Windows 平台上的类 UNIX 模拟环境，​​核心功能是为 Windows 提供 POSIX 兼容的 API 接口和丰富的 GNU 工具集​​，使开发者能够在 Windows 上编译、运行 UNIX/Linux 应用程序。
* Cygwin 由动态链接库（DLL）和 GNU 工具链构成，通过模拟 UNIX 系统调用（如 fork、signal 等）实现与 POSIX 标准的兼容。它并非虚拟机，而是通过翻译层将 UNIX API 转换为 Windows API，使得原生 Windows 系统可直接运行 UNIX 程序。
* Cygwin 通过动态链接库拦截 UNIX 系统调用（如文件操作、进程管理），将其转换为等效的 Windows API，例如：
UNIX 的 fork() 调用 → Windows 的 CreateProcess() 实现多进程。
文件路径 /home/user 映射为 Windows 的 C:\cygwin\home\user。
* ​​POSIX 标准支持​​：覆盖 90% 以上的 UNIX 接口，但部分实时系统调用（如 mlock）可能受限。    
* ​跨平台开发​​：允许开发者直接在 Windows 上编写和调试 Linux 兼容的代码，减少环境切换成本。

**Cygwin是由一个库和一个GNU开发工具链组成的；这个库实现了POSIX系统调用API的功能，它可以把部分POSIX调用转换成Windows系统调用（POSIX为不同Unix系统提供统一的API（应用程序接口）），从而支持用户在Windows平台上可以运行大量与Unix系统类似的应用程序；而这个GNU开发工具链（包括GCC和GDB）则支持让用户进行软件开发。**

## MinGW(Minimalist GNU for Windows)  
 MinGW是一种用于开发原生 Windows 应用的最小化 GNU 开发环境，可以理解为开发 Windows 程序的 gcc，也就是说这个gcc就是专门编译出能在windows平台运行的程序的编译器。

#### MinGW
仅支持 ​​32 位程序开发​​，且已停止更新多年。其内置的 GCC 版本停留在 4.8.1，无法适配现代 C/C++ 标准（如 C++17/20）。仅用于维护旧项目或简单的 32 位程序开发。
#### MinGW-w64
* MinGW-w64 诞生于 2005-2010 年，作为原始 MinGW 项目的分支。原始 MinGW 因更新缓慢且缺乏对 64 位系统和现代 API 的支持，逐渐被社区淘汰。MinGW-w64 通过 ​​洁净室工程原则​​ 独立开发，最终成为 GCC 官方推荐的工具链
* 提供对 ​​32 位（i686）和 64 位（x86_64）Windows 系统​​ 的原生支持，生成无需依赖第三方库的 .exe 文件
* 包含完整的 GNU 开发套件：  
  * GCC 编译器​​：支持 C、C++、Fortran 等多种语言，兼容 C++17/20 等最新标准。
  * GNU Binutils​​：包括汇编器（as）、链接器（ld）等底层工具。
  * GDB 调试器​​：提供源码级调试能力。
  * Windows API 头文件与库​​：如 DirectX、ReactOS DDK，覆盖 Win32/Win64 API。




# MSYS2
* MSYS (Minimal SYStem) 是一系列 GNU 工具（bash、make、gawk、grep等）的集合（基于旧版 Cygwin），用于弥补 Windows cmd shell 的不足，让 MinGW 在 Windows 上更便于使用。
* MSYS2 是一个独立的 MSYS 重写（因为 MinGW 和 MSYS 更新缓慢），基于新一代 Cygwin 和 MinGW-w64，提供更多 API 支持和 64 位应用开发，因此建议抛弃 MSYS 直接使用 MSYS2
### MSYS2详细说明
- MSYS2（​​Minimal SYStem 2​​）是专为Windows设计的​​类Unix开发环境与跨平台构建工具集​​，其核心目标是为开发者提供在Windows上编译原生应用及移植Unix/Linux程序的统一平台。它结合了Cygwin的POSIX兼容层、Arch Linux的Pacman包管理系统，以及MinGW-w64工具链，形成了功能强大的开发框架
- MSYS2是一个集成了大量的GNU工具链、工具和库的开源软件包集合。它提供了一个类似于Linux的shell环境，可以在Windows系统中编译和运行许多Linux应用程序和工具
- MSYS2与MinGW-w64相似，但比MinGW-w64更完整和稳定，提供了Pacman包管理器以方便用户安装和管理软件包。不需网上搜索安装包，下载安装。直接运用pacman进行下载，并且升级简单。
#### 技术栈整合
* Cygwin兼容层​​：提供Unix系统调用模拟，支持bash shell、GNU工具（如grep、sed）等，使Windows用户能运行Unix脚本。
* MinGW-w64工具链​​：包含GCC编译器、GDB调试器等，支持生成原生32/64位Windows程序（.exe），无需依赖第三方动态库。
* Pacman包管理器​​：移植自Arch Linux，管理超过3000个预编译软件包，支持依赖解析与一键更新
#### 多工具链架构
MSYS2维护六大核心仓库，适配不同开发需求：
* ​传统仓库​​：
  * mingw32（32位MSVCRT运行时）、mingw64（64位MSVCRT运行时）。
* ​现代仓库​​：
  * ucrt64（推荐，64位UCRT运行时，适配Windows 10+）、clang64（LLVM/Clang工具链）
### MSYS2核心特点
- 类Unix环境提供Bash、Coreutils、Grep等Unix工具，支持Shell脚本运行，弥补Windows命令行功能的不足。
- MinGW-w64 工具链支持生成原生Windows程序（无需依赖Cygwin DLL），提供32/64位、UCRT（Universal C Runtime）等多种运行时环境。
- Arch Linux 包管理通过 pacman 管理软件包，可安装数千个预编译库（如GCC、Python、OpenSSL）。
- 多环境支持，MSYS2 安装后提供多个终端入口，每个终端对应不同的开发环境和工具链，​核心区别在于目标平台、路径处理方式和运行时依赖。
  
**用户可通过不同终端启动脚本切换开发环境：**
##### MSYS​​
​​定位​​：基于 Cygwin 的 POSIX 兼容环境，主要用于移植 Unix/Linux 工具到 Windows。
​​编译特性​​：生成的程序依赖 MSYS2.dll，无法直接在原生 Windows 中独立运行。
​​适用场景​​：开发或运行需要 Unix 环境的工具（如 autoconf、git）。
##### MINGW32​​
​​定位​​：32 位 Windows 原生开发环境。
​​工具链​​：GCC 编译器 + MSVCRT 运行时（旧版 Windows 兼容）。
​​适用场景​​：维护传统 32 位项目或适配旧系统（如 Windows XP）。
##### MINGW64​​
​​定位​​：64 位 Windows 原生开发环境。
​​工具链​​：GCC 编译器 + MSVCRT 运行时。
​​适用场景​​：开发不依赖新特性的 64 位程序。
##### UCRT64​​
​​定位​​：现代 64 位 Windows 开发环境（推荐默认选择）。
​​工具链​​：GCC 编译器 + UCRT（Universal C Runtime），适配 Windows 10/11。
​​优势​​：支持 Unicode、最新 API 和高性能数学库。
##### CLANG64​​
​​定位​​：基于 LLVM/Clang 的 64 位开发环境。
​​工具链​​：Clang 编译器 + UCRT 运行时。
​​优势​​：支持 C++20/23 标准、静态分析工具（如 clang-tidy）。

##### CLANGARM64​​
​​定位​​：针对 ARM 架构设备（如智能手机）的 64 位开发环境。
​​工具链​​：Clang 编译器 + UCRT 运行时。
​​适用场景​​：跨平台开发或嵌入式系统适配

**不同的终端对应不同的环境和不同的工具链**

| 环境名称​​	​| ​编译器​​	|​ ​运行时库 |​​	​​目标架构 |​​	 ​推荐场景 |​​
|---|---|---|---|---|
|MSYS	  |GCC	|Cygwin	|x86_64	|Unix |工具移植|
MINGW32	GCC	MSVCRT	i686	32 位旧系统兼容
MINGW64	GCC	MSVCRT	x86_64	64 位基础开发
UCRT64	GCC	UCRT	x86_64	现代 Windows 原生程序开发
CLANG64	Clang	UCRT	x86_64	高性能优化与静态代码分析
CLANGARM64	Clang	UCRT	ARM64	ARM 设备开发

运行 POSIX 命令（如 git、make）	     msys2.exe  
编译 32 位 Windows 程序	            mingw32.exe  
编译 64 位 Windows 程序	            mingw64.exe  
编译 64 位 Windows 程序，使用 UCRT	 ucrt64.exe  
使用 Clang 而不是 GCC	            clang64.exe  
编写跨平台 POSIX 代码（类似 Cygwin）  msys2.exe  
```