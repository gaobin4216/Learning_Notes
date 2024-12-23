# Cygwin
* Cygwin是一个支持在Windows平台上运行的Unix环境，它最早的版本于1995年10月发布，最新的一个稳定版本3.4.6则于2023年2月14日发布。其目标是让Windows用户可以使用GNU和开源工具，如bash, gcc, less等。但是，Cygwin并不是一个支持运行原生Linux应用或者让Windows应用感知Unix功能的工具；它实际上是一个大型的GNU和开源工具集合，支持在windows上提供类似于Linux distribution 版本的功能（Linux_distribution的目标是让用户在不同的硬件平台上使用类似于Unix的功能和体验），允许用户在Windows系统上运行许多原本只能在Unix或Linux系统上运行的软件。
# MinGW(Minimalist GNU for Windows)  
* MinGW是一种用于开发原生 Windows 应用的最小化 GNU 开发环境，可以理解为开发 Windows 程序的 gcc，也就是说这个gcc就是专门编译出能在windows平台运行的程序的编译器。MinGW 本身并不一定要运行在 Windows 下，Linux 上也可以通过 MinGW 工具链交叉编译 Windows 程序
# MSYS2
* MSYS (Minimal SYStem) 是一系列 GNU 工具（bash、make、gawk、grep等）的集合（基于旧版 Cygwin），用于弥补 Windows cmd shell 的不足，让 MinGW 在 Windows 上更便于使用。
* MSYS2 是一个独立的 MSYS 重写（因为 MinGW 和 MSYS 更新缓慢），基于新一代 Cygwin 和 MinGW-w64，提供更多 API 支持和 64 位应用开发，因此建议抛弃 MSYS 直接使用 MSYS2
### MSYS2详细说明
- MSYS2（Minimal SYStem 2）是一个集成了大量的GNU工具链、工具和库的开源软件包集合。它提供了一个类似于Linux的shell环境，可以在Windows系统中编译和运行许多Linux应用程序和工具
- MSYS2与MinGW-w64相似，但比MinGW-w64更完整和稳定，提供了Pacman包管理器以方便用户安装和管理软件包。不需网上搜索安装包，下载安装。直接运用pacman进行下载，并且升级简单。