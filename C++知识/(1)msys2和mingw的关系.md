# Cygwin

# MinGW(Minimalist GNU for Windows)  
* MinGW是一种用于开发原生 Windows 应用的最小化 GNU 开发环境，可以理解为开发 Windows 程序的 gcc，也就是说这个gcc就是专门编译出能在windows平台运行的程序的编译器。MinGW 本身并不一定要运行在 Windows 下，Linux 上也可以通过 MinGW 工具链交叉编译 Windows 程序

# MSYS2
* MSYS (Minimal SYStem) 是一系列 GNU 工具（bash、make、gawk、grep等）的集合（基于旧版 Cygwin），用于弥补 Windows cmd shell 的不足，让 MinGW 在 Windows 上更便于使用。
* MSYS2 是一个独立的 MSYS 重写（因为 MinGW 和 MSYS 更新缓慢），基于新一代 Cygwin 和 MinGW-w64，提供更多 API 支持和 64 位应用开发，因此建议抛弃 MSYS 直接使用 MSYS2