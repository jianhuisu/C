## make、makefile、cmake之间的区别与联系

首先说明一下make、makefile、cmake存在的原因

在进行编译时，如果程序只有一个源文件，那么我们可以直接利用gcc命令对其进行编译；
但是，如果程序包含多个源文件的话，用gcc命令对源文件进行逐个编译显然会比较繁琐。尤其是在有大量源文件时，这样繁琐的编译工作很容易会导致混乱；
为了使多个源文件的编译工作更加便捷，就出现了make工具和makefile文件。

### 什么是make工具？

make工具类似于批处理工具，可以对多个源文件进行批量地编译和链接；
但是需要明确的是，make工具本身不具备编译和批处理功能，它是通过调用makefile文件中的命令实现编译和链接。

### 什么是makefile文件？

makefile是一个文本文件，其中包含了make工具在执行时所要遵循的一系列规则；
比如，makefile文件中包含了调用gcc（也可以是别的编译器）去编译某个源文件的命令。

### 什么是Cmake工具？

在一些简单的工程中，makefile文件完全可以由程序员自己编写；但是当工程非常大时，手写makefile文件肯定不是一个明智的选择；
Cmake工具的功能就是用来生成makefile文件，以便make工具进行调用；
Cmake工具根据CMakeLists.txt（组态档）文件生成makefile文件；而CMakefile文件是需要程序员自己编写的，或者借助IDE生成；
类似CMake的工具有很多，比如autotools、Qt环境下的qmake等。

### CLion提示 Cmake project is not loaded
    
新建一个project,不要打开已有的project,新建的project系统会自动为你新建CMakeLists.txt
得到了这句话，于是就新建了project，将之前的代码粘贴进来，果然Clion自动生成了CMakeLists.txt，
之前一直不亮的小甲虫也亮了起来，点击绿色三角，开始编译，成功后自动开始运行

Clion调试redis https://sunznx.com/redis/redis-source-debug-with-clion.html

### 参考资料

原文链接：https://blog.csdn.net/Aiyanghong/article/details/86501720