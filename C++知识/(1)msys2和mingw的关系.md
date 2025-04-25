# POSIX
​可移植操作系统接口​​，Portable Operating System Interface，是​​由IEEE制定的标准族​​，旨在为不同UNIX操作系统提供统一的应用程序接口（API），确保软件能在兼容系统上无缝移植

# Cygwin
* Cygwin 是运行在 Windows 平台上的类 UNIX 模拟环境，​​核心功能是为 Windows 提供 POSIX 兼容的 API 接口和丰富的 GNU 工具集​​，使开发者能够在 Windows 上编译、运行 UNIX/Linux 应用程序。
* Cygwin 由动态链接库（DLL）和 GNU 工具链构成，通过模拟 UNIX 系统调用（如 fork、signal 等）实现与 POSIX 标准的兼容。它并非虚拟机，而是通过翻译层将 UNIX API 转换为 Windows API，使得原生 Windows 系统可直接运行 UNIX 程序。
* Cygwin 通过动态链接库拦截 UNIX 系统调用（如文件操作、进程管理），将其转换为等效的 Windows API，例如：
UNIX 的 fork() 调用 → Windows 的 CreateProcess() 实现多进程。
文件路径 /home/user 映射为 Windows 的 C:\cygwin\home\user。
* ​​POSIX 标准支持​​：覆盖 90% 以上的 UNIX 接口，但部分实时系统调用（如 mlock）可能受限。    
* ​跨平台开发​​：允许开发者直接在 Windows 上编写和调试 Linux 兼容的代码，减少环境切换成本。

**Cygwin是由一个库和一个GNU开发工具链组成的；这个库实现了POSIX系统调用API的功能，它可以把部分POSIX调用转换成Windows系统调用（POSIX为不同Unix系统提供统一的API（应用程序接口）），从而支持用户在Windows平台上可以运行大量与Unix系统类似的应用程序；而这个GNU开发工具链（包括GCC和GDB）则支持让用户进行软件开发。**

# MinGW(Minimalist GNU for Windows)  
* MinGW是一种用于开发原生 Windows 应用的最小化 GNU 开发环境，可以理解为开发 Windows 程序的 gcc，也就是说这个gcc就是专门编译出能在windows平台运行的程序的编译器。MinGW 本身并不一定要运行在 Windows 下，Linux 上也可以通过 MinGW 工具链交叉编译 Windows 程序
# MSYS2
* MSYS (Minimal SYStem) 是一系列 GNU 工具（bash、make、gawk、grep等）的集合（基于旧版 Cygwin），用于弥补 Windows cmd shell 的不足，让 MinGW 在 Windows 上更便于使用。
* MSYS2 是一个独立的 MSYS 重写（因为 MinGW 和 MSYS 更新缓慢），基于新一代 Cygwin 和 MinGW-w64，提供更多 API 支持和 64 位应用开发，因此建议抛弃 MSYS 直接使用 MSYS2
### MSYS2详细说明
- MSYS2（Minimal SYStem 2）是一个集成了大量的GNU工具链、工具和库的开源软件包集合。它提供了一个类似于Linux的shell环境，可以在Windows系统中编译和运行许多Linux应用程序和工具
- MSYS2与MinGW-w64相似，但比MinGW-w64更完整和稳定，提供了Pacman包管理器以方便用户安装和管理软件包。不需网上搜索安装包，下载安装。直接运用pacman进行下载，并且升级简单。
### MSYS2核心特点
- 类Unix环境提供Bash、Coreutils、Grep等Unix工具，支持Shell脚本运行，弥补Windows命令行功能的不足。
- MinGW-w64 工具链支持生成原生Windows程序（无需依赖Cygwin DLL），提供32/64位、UCRT（Universal C Runtime）等多种运行时环境。
- Arch Linux 包管理通过 pacman 管理软件包，可安装数千个预编译库（如GCC、Python、OpenSSL）。
- 多环境支持，MSYS2 安装后提供多个终端入口，每个终端对应不同的开发环境和工具链，​核心区别在于目标平台、路径处理方式和运行时依赖。  
  **用户可通过不同终端启动脚本切换开发环境：**  
  • MSYS：基于Cygwin的POSIX兼容环境（适合移植Unix工具）。  
  • MINGW64：生成64位原生Windows程序（默认使用MSVCRT运行时）。  
  • UCRT64：使用Windows Universal C Runtime（兼容性更好）。  
  • CLANG64：基于LLVM/Clang的工具链。

[不同的终端对应不同的环境和不同的工具链](https://blog.csdn.net/pumpkin84514/article/details/144410387)  
```  
不同的终端对应不同的环境和不同的工具链，不同的终端安装名不同，

运行 POSIX 命令（如 git、make）	     msys2.exe  
编译 32 位 Windows 程序	            mingw32.exe  
编译 64 位 Windows 程序	            mingw64.exe  
编译 64 位 Windows 程序，使用 UCRT	 ucrt64.exe  
使用 Clang 而不是 GCC	            clang64.exe  
编写跨平台 POSIX 代码（类似 Cygwin）  msys2.exe  
```