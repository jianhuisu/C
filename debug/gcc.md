## gcc使用

gcc -g -lc -Wall main.c -o main

    -g  目标文件中生成调试符号
    -lc 链接libc目标文件 不手动添加也可以 gcc 默认追加 
    -Wall 显示编译过程中的报警信息 推荐打开
    -o    指定输出文件名
    
- gcc -M main.c  输出以main.c源文件的依赖,`包括` 系统头文件的依赖关系 例如 stdio.h的依赖关系
- gcc -MM main.c 输出以main.c源文件的依赖,`不包括`对操作系统的依赖项
