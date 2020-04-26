## CMake与Make最简单直接的区别

写程序大体步骤为：

1.用编辑器编写源代码，如.c文件。
2.用编译器编译代码生成目标文件，如.o。
3.用链接器连接目标代码生成可执行文件，如.exe。

但如果源文件太多，一个一个编译时就会特别麻烦，于是人们想到，为什么不设计一种类似批处理的程序，来批处理编译源文件呢，
于是就有了make工具，它是一个自动化编译工具，你可以使用一条命令实现完全编译。
但是你需要编写一个规则文件，make依据它来批处理编译，这个文件就是makefile，所以编写makefile文件也是一个程序员所必备的技能。

你或许听过好几种Make工具，例如

    GNU Make ，
    QT 的 qmake ，
    微软的 MS nmake，
    BSD Make（pmake），
    Makepp，

等等。这些 Make 工具遵循着不同的规范和标准，所执行的Makefile格式也千差万别。

对于一个大工程，编写makefile实在是件复杂的事(makefile is different in different platforms)，于是人们又想，为什么不设计一个工具，
读入所有源文件之后，自动生成makefile呢，于是就出现了cmake工具，它能够输出各种各样的makefile或者project文件,
从而帮助程序员减轻负担(cmake是让程序员用统一的语法来写cmake文件，然后cmake会帮助我们生成对应的平台下的makefile)。
但是随之而来也就是编写cmakelist文件，它是cmake所依据的规则。所以在编程的世界里没有捷径可走，还是要脚踏实地的。


###

在 linux 平台下使用 CMake 生成 Makefile 并编译的流程如下：

1 编写 CMake 配置文件 CMakeLists.txt 。
2 执行命令 cmake PATH 或者 ccmake PATH 生成 Makefile (ccmake 和 cmake 的区别在于前者提供了一个交互式的界面。。其中， PATH 是 CMakeLists.txt 所在的目录。)
3 使用 make 命令进行编译。

### reference material

 - https://www.cnblogs.com/grey-wolf/p/12637730.html

