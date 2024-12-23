[toc]

# 一、基础概念
&emsp;&emsp;我们以gcc编译器为例来说，它可以编译很多种编程语言(括C、C++、Objective-C、Fortran、Java等等)，当你的程序只有一个源文件时，直接就可以用gcc命令编译它。
```cpp
gcc hello.c -o hello_world
```
&emsp;&emsp;但是当你的程序包含很多个源文件时，用gcc命令逐个去编译时，你就很容易混乱而且工作量大。因此make工具就很有必要。
## 1、Makefile
&emsp;&emsp;Makefile 文件描述了整个工程的编译、连接等规则。其中包括：工程中的哪些源文件需要编译以及如何编译、需要创建那些中间文件以及如何创建这些中间文件、如何最后产生我们想要得可执行文件。尽管看起来可能是很复杂的事情，但是为工程编写 Makefile 的好处是能够使用一行命令来完成“自动化编译”，一旦提供了正确的 Makefile，编译整个工程你所要做的唯一的一件事就是输入 make 命令。整个工程完全自动编译，极大提高了效率。makefile命令中就包含了调用gcc（也可以是别的编译器）去编译某个源文件的命令。
## 2、make工具
&emsp;&emsp;make工具可以看成是一个智能的批处理工具，它本身并没有编译和链接的功能，而是用类似于批处理的方式通过调用makefile文件中用户指定的命令来进行编译和链接的。  
&emsp;&emsp;make 是一个命令工具，它解释Makefile中的规则。在Makefile文件中描述了整个工程所有文件的编译顺序、编译规则。Makefile有自己的书写格式、关键字、函数。而且在Makefile中可以使用系统shell所提供的任何命令来完成想要的工作。Makefile在绝大多数的IDE开发环境中都在使用，已经成为一种工程的编译方法。       
&emsp;&emsp;当对工程中的若干源文件修改以后，只需要重新执行 make 命令，就会自动根据修改情况完成源文件的对应目标文件的更新、中间文件的更新、最终的可执行程序的更新。make 通过比较对应文件的最后修改时间，来决定哪些文件需要更新、那些文件不需要更新。对需要更新的文件 make 就执行相应的命令来重建它，对于不需要重建的文件 make 什么也不做。
方法。
>&emsp;&emsp;**简单来说，make工具是用来执行Makefile的，Makefile是类unix环境下(比如Linux)的类似于批处理的"脚本"文件。其基本语法是: 目标+依赖+命令，只有在目标文件不存在，或目标比依赖的文件更旧，命令才会被执行。由此可见，Makefile和make可适用于任意工作，不限于编程。比如，可以用来管理latex。**

## 3、CMake
### 3.1、why？
* makefile在一些简单的工程完全可以人工拿下，但是当工程非常大的时候，手写makefile也是非常麻烦的。
* 如果换了个平台makefile重新修改。因为软件想跨平台，必须要保证能够在不同平台编译，就得为每一种平台标准重新写一次Makefile。各个平台都有自己的Make工具，例如GNU Make，QT的qmake，微软的MS nmake，BSD Make(pmake)，Makepp等等。

>**cmake可以更加简单的生成makefile文件给make用。也可以跨平台生成对应平台能用的makefile。**

### 3.2、简介
&emsp;&emsp;CMake是一个跨平台的安装(编译)工具，可以用简单的语句来描述所有平台的安装(编译过程)。他能够输出各种各样的makefile或者project文件，能测试编译器所支持的C++特性,类似UNIX下的automake。只是CMake的组态档取名为CMakeLists.txt。Cmake并不直接建构出最终的软件，而是产生标准的建构档(如 Unix 的 Makefile 或 Windows Visual C++ 的projects/workspaces)，然后再依一般的建构方式使用。这使得熟悉某个集成开发环境(IDE)的开发者可以用标准的方式建构他的软件，这种可以使用各平台的原生建构系统的能力是 CMake 和 SCons 等其他类似系统的区别之处。  
&emsp;&emsp;CMake首先允许开发者编写一种平台无关的 CMakeList.txt文件来定制整个编译流程，然后再根据目标用户的平台进一步生成所需的本地化Makefile和工程文件，如Unix的Makefile或Windows的Visual Studio工程。从而做到“Write once, run everywhere”。显然，CMake是一个比上述几种make更高级的编译配置工具。工作过程如下：
<div align=center>

![请添加图片描述](https://i-blog.csdnimg.cn/blog_migrate/c21f472971e34676a84b70d37ee4fe1d.png)</div>

cmake 的特点主要有：
>* 开放源代码，使用类 BSD 许可发布。http://cmake.org/HTML/Copyright.html
>* 跨平台，并可生成 native 编译配置文件，在 Linux/Unix 平台，生成 makefile，在苹果平台，可以生成 xcode，在 Windows 平台，可以生成 MSVC 的工程文件。
>* 能够管理大型项目，KDE4 就是最好的证明。
>* 简化编译构建过程和编译过程。Cmake 的工具链非常简单：cmake+make。
>* 高效虑，按照 KDE 官方说法，CMake 构建 KDE4 的 kdelibs 要比使用 autotools 来构建 KDE3.5.6 的 kdelibs 快 40%，主要是因为 Cmake 在工具链中没有 libtool
>* 可扩展，可以为 cmake 编写特定功能的模块，扩充 cmake 功能。
# 二、CMake应用学习
## 1、Window下安装及使用
### (1)CMake安装
* 从[CMake官网](https://cmake.org/download/)下载对应的安装包，如果系统是64位就选择x86_64，如果是32位就选择i386。
<div align=center>

![请添加图片描述](https://i-blog.csdnimg.cn/blog_migrate/b7083d9f77ddf523c2fbba2afda42ab1.png)


</div>

* 安装CMake，建议英文路径，同时勾选添加环境变量。
<div align=center>

![请添加图片描述](https://i-blog.csdnimg.cn/blog_migrate/1f885fae61bd38e85e21738fba46ad5e.png)


</div>

勾选之后就不需手动再添加环境变量了。如果不放心，可以在电脑高级系统设置->环境变量->path中查看是否已添加。
<div align=center>

![请添加图片描述](https://i-blog.csdnimg.cn/blog_migrate/c745e93a957a412e02aa4ec10d7440c2.png)


</div>

* 检查安装
win+R，输入cmd回车，打开管理员窗口，输入cmake -version查看安装情况。

<div align=center>

![请添加图片描述](https://i-blog.csdnimg.cn/blog_migrate/817e5f67812974fb4d98090f62da2a5a.png)
</div>

### (2)CMake命令行运行示例
* 首先安装C++编译器，例如mingw，或者安装Visual Studio,VS会自带MSVC编译器。这里我们选择安装Visual Studio 2017。
* 桌面新建一个文件夹HelloCMake，在文件夹内新建一个Hello CMake.cpp，作用是在控制台输出HelloCMake，同时在cpp同目录新建一个CMakeLists.txt文件。

HelloCMake.cpp内容：
```cpp
#include <iostream>
int main() 
{
  std::cout << "HelloCMake" << std::endl;
  system("pause");
  return 0;
}
```
CMakeLists.txt内容：
```cpp
cmake_minimum_required (VERSION 3.18)
project (HelloCMake)
add_executable (HelloCMake HelloCMake.cpp)
```
* 在文件夹内打开cmd窗口，输入
```cpp
cmake .
```
CMake会自己找到VS的c++编译器，生成vs项目；(红框为我们自己写的内容)
<div align=center>

![请添加图片描述](https://i-blog.csdnimg.cn/blog_migrate/0796aee6ebec6aa89507c9ff625d17b3.png)


</div>

* 现在使用VS打开sln解决方案文件，就可以编译、运行、调试，由于项目中还存在其他的解决方案，需将HelloWorld解决方案设为“启动项”之后才能进行调试。
<div align=center>

![请添加图片描述](https://i-blog.csdnimg.cn/blog_migrate/df6e6ca5f5fc2c4669d06d41f164acf7.png)

</div>

* CMake在生成项目后，接下来就是编译工程(默认Debug模式)，在文件夹cmd直接输入
```cpp
cmake --bulid .
```
如果用Release模式编译，在文件夹cmd直接输入
```cpp
cmake --build . -- /p:Configuration=Release
```
<div align=center>

![请添加图片描述](https://i-blog.csdnimg.cn/blog_migrate/25dbd96c2bb320a7c8ad327cb6b62e3e.png)

</div>

红框的两个文件夹中就是不同模式生成的可执行文件.exe,可以直接双击运行。

### (3)CMake-GUI运行示例
* 在桌面新建一个文件夹HelloCMake，在文件夹内新建一个Hello CMake.cpp，作用是在控制台输出HelloCMake，同时在cpp同目录新建一个CMakeLists.txt文件，最后在文件夹内新建一个bulid文件夹用来放生成文件。
<div align=center>

![请添加图片描述](https://i-blog.csdnimg.cn/blog_migrate/53df13c78fa744811f75d32c5661cc4a.png)

</div>

* 以下步骤依次进行
<div align=center>   

![请添加图片描述](https://i-blog.csdnimg.cn/blog_migrate/c2665d73437d4cd4fdf0be6c0b85aaa5.png)
![请添加图片描述](https://i-blog.csdnimg.cn/blog_migrate/20a31a0de8081ec0052a5ad4680bd9d0.png)

</div>
点击Generate生成VS项目，打开解决方案就可以编译运行。
<div align=center>   

![请添加图片描述](https://i-blog.csdnimg.cn/blog_migrate/3d1c470cd365d9f3c0a68b753ec64993.png)

</div>
生成的解决方案中有三个项目，这三个项目分别是：

> **ALL_BUILD：**  该目标会导致工程中所有项目被构建，类似 Visual Studio的Build All或者make的make all命令
> **HelloWorld：** 项目本身，就是在CMakeLists.txt文件中配置的project(HelloWorld)
> **ZERO_CHECK：** 该项目会检查生成工程的 CMake 配置文件(CMakeLists.txt)是否更新，如更新将运行 CMake 重新生成工程文件，如果确信 CMakeLists.txt 不会被更新，或者希望手工运行 CMake 重新生成工程文件，可以在 CMakeLists.txt 配置文件中添加 set(CMAKE_SUPPRESS_REGENERATION FALSE) 命令， ZERO_CHECK 目标将不会生成
## 2、Linux下安装及使用
***暂时没有用到Linux，以后用到再更！***