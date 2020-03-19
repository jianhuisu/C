## gcc使用

gcc -g -lc -Wall main.c -o main

    -g  目标文件中生成调试符号 注意，加调试信息必须在编译每个目标文件时用-g选项，而不能只在最后编译生成可执行文件时用-g选项
    -lc 链接libc目标文件 不手动添加也可以 gcc 默认追加 
    -Wall 显示编译过程中的报警信息 推荐打开
    -o    指定输出文件名
    
- gcc -M main.c  输出以main.c源文件的依赖,`包括` 系统头文件的依赖关系 例如 stdio.h的依赖关系
- gcc -MM main.c 输出以main.c源文件的依赖,`不包括`对操作系统的依赖项

#### 制作静态库

静态库文件制作完成,几乎main.c所有需要的信息都可以在静态库`libstack`中找到,将main.c**编译链接**在一起

    [guangsujiqiang@su-ct7 static_library]$>gcc main.c -L. -lstack -Istack -o main
    
解释一下参数

 - -L. `L`后跟在哪个目录寻找需要的库文件,`L.`代表在当前目录下寻找。编译器默查找的目录可以用`-print-search-dirs`命令查看
 - -lstack 小写的`l`标明编译器需要链接的库名 `-lstack` 告诉编译器要链接`libstack`库.**库文件名都是以lib开头的，静态库以.a作为后缀，
    表示Archive** 但是在链接时需要省略前面的`lib`前缀
    编译器会首先找有没有共享库libstack.so，如果有就链接它，如果没有就找有没有静态库libstack.a，如果有就链接它。
    所以编译器是优先考虑共享库的，如果希望编译器只链接静态库，可以指定`-static`选项  
 - -I. `-I`选项指明编译器去哪里找头文件