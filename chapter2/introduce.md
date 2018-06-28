第二章 基本概念

1 环境
编译环境与运行环境可以不处于同一机器上

翻译环境 translation environment

    compile main.c

    预处理器处理 预处理指令
        进行 include 、常量替换等文本操作
    解析 parse
        语句解析
        [优化器  optimizer]

    生成目标代码  object code
        main.o
    连接器  linker
        链接启动代码

    可执行文件
        a.out


    gcc -c -o /home/www/main.out main.c

        -c  Compile or assemble the source files
        -o  指定目标代码名称



执行环境 execution environment

        加载到内存
        宿主环境
            由操作系统完成
        自由环境
            加载到ROM中


         一个C程序的源代码可能分布于多个文件中 , 但是一个函数只能完整的出现在一个文件中