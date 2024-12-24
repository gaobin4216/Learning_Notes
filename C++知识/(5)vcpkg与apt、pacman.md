# pacman 是 MSYS2 或 Arch Linux 等发行版的包管理工具，主要用于管理系统软件包，包括编译工具链、开发工具、库等。
# vcpkg 是专门为 C++ 开发提供的库管理工具，专注于提供 C++ 第三方库的管理，并与 CMake 等构建系统集成。
### vcpkg在windos上编译时需要安装vs，至少使用bulidtools安装C++桌面开发和英语，安装文件避免空格，使用windows版本的cmake，在使用vscode时编译器要选择msvc，因为vcpkg编译的库是适用于msvc的。或者就需要用GCC编译vcpkg的包
> 总结来说，vcpkg在Windows上比较适合用VS跑第三方库，如果是vscode搭配gcc，那就最好别用vcpkg的第三方库了。


> 总结，在windows上安装使用msys2安装mingw可以使用pacman，和pacman相对等的是ubuntu的apt，管理第三方库最好是vcpkg。