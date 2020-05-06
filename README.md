# C

todo 处理项目中的todo事项

## C程序的编译流程

### 1  precompiled

宏定义是预处理指令集中的一个子集 

 - 宏展开
 - 删除注释
 - 文本替换
    
    gcc -E main.c -o main.i
    或者 cpp main.c   // cpp - The C Preprocessor

### 2   编译

将C源码翻译为汇编语言(助记符),汇编语言并不是机器语言,汇编语言就是一种更贴近二进制的助记符语言.
(将变量名（符号地址）替换为 汇编指令)
    
    movl    %edi, -20(%rbp)
    movq    %rsi, -32(%rbp)
    movl    -20(%rbp), %eax
    movl    %eax, %esi
    movl    $.LC0, %edi
    movl    $0, %eax
    call    printf
    movl    $0, -4(%rbp)
    jmp     .L2
    
只执行编译操作
    
    gcc -S main.c -o main.s  | gcc -S main.i -o main.s
    
编译过程的五个阶段
    
 - 词法分析
 - 语法分析
 - 语义检查和中间代码生成
 - 代码优化
 - 目标代码生成

有很多变量/常量的值在编译时确定，还有一部分在运行时确定.

### 3 汇编

将汇编语言转化为机器语言，内容保存在目标文件中(将助记符替换为二进制)

    gcc -c main.c -o main.o
   
main.o 是一个二进制文件,如果使用vim去查看文件内容，你会发现内容为乱码.如果要使内容可读，需要借助工具
    
    nm main.o
    readelf -S main.o
    objdump -t main.o
    ...

### 4 链接

当编写了多个C文件时，我们将他们编译链接成一个可执行的文件，此时就需要用到链接脚本文件（ld）
ld脚本主要功能就是：将多个目标文件（.o）和库文件（.a\.so）链接成一个可执行的文件。

    1 链接配置（可有可无）

    如一些符号变量的定义、入口地址、输出格式等

        STACK_SIZE = 0X200;
        OUTPUT_FORMAT(elf32-littlearm)
        OUTPUT_ARCH(arm)
        ENTRY(_start)

    2 内存布局定义

        脚本中以MEMORY命令定义了存储空间，其中以ORIGIN定义地址空间的起始地址，LENGTH定义地址空间的长度。

        MEMORY
        {
        FLASH (rx) : ORIGIN = 0, LENGTH = 64K
        }

    3 段链接定义

        脚本中以SECTIONS命令定义一些段（text、data、bss等段）链接分布。

     ld test.o -o test;

     [guangsujiqiang@su-ct7 binary_search_tree]$>ld test.o -o test
     ld: warning: cannot find entry symbol _start; defaulting to 00000000004000b0
     test.o: In function `main':
     main.c:(.text+0x1f): undefined reference to `printf'
     main.c:(.text+0x51): undefined reference to `printf'

     没有__start是因为c程序以main为主函数,汇编以start为主函数入口,使用gcc取代ld进行链接即可
     gcc test.o -o test -lselfpkg -L /home/my/lib


### 5   装载

将可执行文件load到内存中(从外存置换到内存)，开始运行.这一部分涉及到装载器.

### 常见词汇

v.

    precompiled        预编译
    compile            编译
    compilation        汇编
    assemble           集合
    load               装载
    link               链接

n.

    compiler       编译器     gcc llvm clang
    assembler      汇编器     as 
    linker         链接器     ld
    loader         装载器


##### 备注：

 - 笔记内容多为自己的总结,因为还处于学习阶段，所以不能保证其正确性，仅供参考
 - 强推 宋劲杉老师的书 《Linux C编程一站式学习》 https://docs.huihoo.com/c/linux-c-programming/index.html
 - 必须掌握的库 string库 数学计算库 io库 **线程库 进程库 信号处理**
 - 我想在能挣钱的同时 做有意义的事 不再浪费自己的青春 
 - 我的终极目标是可以流畅阅读C项目源码
 
#### 学习曲线
 
 todo 了解Linux系统编程部分知识 系统调用  select / poll / epoll 
 todo 熟练掌握 多进程 多线程 信号 IPC 线程安全 并发 部分 原理知识，了解如何写出线程安全的类 如何处理并发问题 
        对临界资源的操作被打断是造成混乱的根源,如果一个操作可以被打断，我们称该操作是非原子性的.
 todo 熟悉常用数据结构, 管道是用环形队列实现的
 
 todo php源码 为简历增彩 找两个项目（直播/图片服务器）   
 todo 数据库的实现原理 数据库面试刷题
 todo redis实现原理 面试题刷题
 todo nginx tcp 部分刷题
   
#### 待深入研究问题
   
php如何写出线程安全的类 php高并发编程
MT-safe Multiple Thread safe

并发执行:交错执行，多线程访问临界资源时，必须进行同步控制.多线程的临界资源有全局数据，堆区数据，文件描述符
同步控制方式：
    信号量
    互斥锁
    

可重入函数：(对同一资源进行操作的函数，可以同时重复执行多次,而不会影响最终结果的准确性)
线程安全函数与可重入函数的表达意思很接近

比如有一个定时任务,拉取昨天的新入值员工, `php 1.php` 我在两个不同的`shell`中执行这个命令,
最终的结果是正确的，那么我们就可以称`1.php`中的`同步函数`是可重入函数.

   某些库函数会使用线程间共享的数据，如果没有同步控制，线程操作是不安全的。
   所以，我们使用这样一些函数时，就必须使用其安全的版本，即可重入函数；

`i++`操作并不是一条指令完成的，即不是原子的。操作系统执行i++的时候可能执行了一部分就被调度去执行另一个代码，而单条指令是不会被打断的。
解决方式：对临界区加锁（二元信号量、互斥锁、多元信号量等）,所以线程安全函数要么不允许打断，要么对临界资源上了锁.
多线程编程时,操作临界资源需要使用线程安全函数. 非临界资源则无所谓.   

但是在函数中使用静态变量是不好的，以后会讲到这样的函数是不可重入的。
strtok函数使用了静态变量，它不是线程安全的，必要时应该用可重入的strtok_r函数，以后再详细介绍“可重入”和“线程安全”这两个概念

多线程场景下,线程执行可以按照我们期望的顺序产出结果,不会出现数据污染等意外情况.那么我们称该实现是线程安全的.否则为非线程安全. 
有资源竞争时才会出现问题.
 
 MT 多线程使用静态链接方式 
 MD 多线程使用动态链接方式