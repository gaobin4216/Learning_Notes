# 最优配合：vscode + cmake + msys2（安装mingw64，安装和管理第三方库）

 >不同的编译器编译的库会存在区别，因此vcpkg安装时用cl编译的库，用GCC编译器去调用时，就会出一些莫名奇妙的问题。

## vscode与gcc绑定，使用msys2安装mingw环境，使用mingw下的gcc和g++编译程序，msys2可以使用pacman安装管理第三方库，将msys2/mingw/bin放在环境变量下，使用Cmake构建时就能找到库。

## Visual Studio与cl绑定，安装vcpkg时，vcpkg在windos上编译时需要安装vs，至少使用bulidtools安装C++桌面开发和英语，安装文件避免空格，使用windows版本的cmake。vcpkg的路径包含也没有pacman做的好。