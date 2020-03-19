## 静态库

有时候需要把一组代码编译成一个库，这个库在很多项目中都要用到，例如libc就是这样一个库，我们在不同的程序中都会用到libc中的库函数.
其实一个静态库可以简单看成是一组目标文件（.o/.obj文件）的集合.

如何制作一个静态库

    [guangsujiqiang@su-ct7 static_library]$>gcc -c stack/stack.c stack/push.c stack/pop.c stack/is_empty.c
    [guangsujiqiang@su-ct7 static_library]$>ll
    total 20
    -rw-rw-r-- 1 guangsujiqiang guangsujiqiang 1376 Mar 19 17:01 is_empty.o
    -rw-rw-r-- 1 guangsujiqiang guangsujiqiang   93 Mar 19 16:38 main.c
    -rw-rw-r-- 1 guangsujiqiang guangsujiqiang 1448 Mar 19 17:01 pop.o
    -rw-rw-r-- 1 guangsujiqiang guangsujiqiang 1488 Mar 19 17:01 push.o
    -rw-rw-r-- 1 guangsujiqiang guangsujiqiang    0 Mar 19 17:00 README.md
    drwxrwxr-x 2 guangsujiqiang guangsujiqiang   81 Mar 19 16:39 stack
    -rw-rw-r-- 1 guangsujiqiang guangsujiqiang 1000 Mar 19 17:01 stack.o

`gcc -c stack/stack.c stack/push.c stack/pop.c stack/is_empty.c` 
虽然没有使用`-o` 显式的指定输出目标文件名,则编译器默认为每一个源文件生成`Stem.o`格式的目标文件.比如上文结果中的 `stack.o` `push.o` `is_empty.o` `pop.o`.
(选项`-c`用来告诉编译器编译源代码但不要执行链接，输出结果为对象文件。文件默认名与源码文件名相同，只是将其后缀变为 .o.)

#### 生成静态库文件

    [guangsujiqiang@su-ct7 static_library]$>ar rs libstack.a is_empty.o pop.o push.o stack.o
    ar: creating libstack.a

 - ar 是将目标文件打包到一起的打包工具,tar是将文件打包到一起的工具,就相当于将多个目标文件的内容进行merge
 - r 选项表示将后面的文件列表添加到文件包,如果文件包不存在就创建它，如果文件包中已有同名文件就替换成新的
 - s 是专用于生成静态库的，表示为静态库创建索引，这个索引被链接器使用,如果不添加该选项,可以另外执行`ranlib libstack.a`命令来创建索引
 - libstack.a  **库文件名都是以lib开头的，静态库以.a作为后缀** 共享库/动态库以.so作为后缀
 
简单展示一些系统的动态库
 
    [guangsujiqiang@su-ct7 static_library]$>ls /usr/lib
    lrwxrwxrwx.  1 root root    21 Oct 17 17:33 libjpeg.so -> /usr/lib64/libjpeg.so
    lrwxrwxrwx.  1 root root    24 Oct 17 17:33 libjpeg.so.62 -> /usr/lib64/libjpeg.so.62
    lrwxrwxrwx.  1 root root    28 Oct 17 17:33 libjpeg.so.62.1.0 -> /usr/lib64/libjpeg.so.62.1.0
  
查看一下我们生成的静态库文件的属性

    [guangsujiqiang@su-ct7 static_library]$>file libstack.a 
    libstack.a: current ar archive

#### 使用自定义的静态库文件

静态库文件制作完成,几乎main.c所有需要的信息都可以在静态库`libstack`中找到,将main.c**编译链接**在一起

    [guangsujiqiang@su-ct7 static_library]$>gcc main.c -L. -lstack -Istack -o main
    
解释一下参数

 - -L. `L`后跟在哪个目录寻找需要的库文件,`L.`代表在当前目录下寻找。编译器默查找的目录可以用`-print-search-dirs`命令查看
 - -lstack 小写的`l`标明编译器需要链接的库名 `-lstack` 告诉编译器要链接`libstack`库.**库文件名都是以lib开头的，静态库以.a作为后缀，
    表示Archive** 但是在链接时需要省略前面的`lib`前缀
    编译器会首先找有没有共享库libstack.so，如果有就链接它，如果没有就找有没有静态库libstack.a，如果有就链接它。
    **所以编译器是优先考虑共享库的**，如果希望编译器只链接静态库，可以指定`-static`选项  
 - -I. `-I`选项指明编译器去哪里找头文件

编译链接完成,观察可执行文件中`.text`段,每一个函数symbol都代表一段指令
    
    [guangsujiqiang@su-ct7 static_library]$>objdump -d main
    ... .text section :
    00000000004004ed <main>:
      4004ed:       55                      push   %rbp
      4004ee:       48 89 e5                mov    %rsp,%rbp
      4004f1:       bf 61 00 00 00          mov    $0x61,%edi
      4004f6:       e8 07 00 00 00          callq  400502 <push>
      4004fb:       b8 00 00 00 00          mov    $0x0,%eax
      400500:       5d                      pop    %rbp
      400501:       c3                      retq   
    
    0000000000400502 <push>:
      400502:       55                      push   %rbp
      400503:       48 89 e5                mov    %rsp,%rbp
      400506:       89 f8                   mov    %edi,%eax
      400508:       88 45 fc                mov    %al,-0x4(%rbp)
      40050b:       8b 05 1b 0b 20 00       mov    0x200b1b(%rip),%eax        # 60102c <top>
      400511:       83 c0 01                add    $0x1,%eax
      400514:       89 05 12 0b 20 00       mov    %eax,0x200b12(%rip)        # 60102c <top>
      40051a:       8b 05 0c 0b 20 00       mov    0x200b0c(%rip),%eax        # 60102c <top>
      400520:       48 98                   cltq   
      400522:       0f b6 55 fc             movzbl -0x4(%rbp),%edx
      400526:       88 90 60 10 60 00       mov    %dl,0x601060(%rax)
      40052c:       5d                      pop    %rbp
      40052d:       c3                      retq   
      40052e:       66 90                   xchg   %ax,%ax

在链接libc共享库时只是指定了动态链接器和该程序所需要的库文件，并没有真的做链接，可执行文件main中调用的libc库函数仍然是未定义符号，要在运行时做动态链接。
而在链接静态库时，链接器会把静态库中的目标文件取出来和可执行文件真正链接在一起。通过反汇编看上一步生成的可执行文件main：main.c只调用了push这一个函数，
所以链接生成的可执行文件中也只有push而没有pop和is_empty。
这是使用静态库的一个好处，链接器可以从静态库中只取出需要的部分来做链接。
(这里纠正了我以前的一个错误看法 我们写的每一个函数实质上就为1-N个汇编指令的集合,
每一个C文件中指令都尽量减少互相的依赖,这样我们使用的时候,就可以抽取最关键一段指令,而不是整个静态库中的所有指令,我以前一直以为链接合并静态库中的所有内容呢,
那链接了一个1G静态库文件后,可执行文件不得大的头秃... `file_size_静态库 + file_size_源文件 <= 物理文件大小之和` )
                                                                
    $ gcc main.c stack.o push.o pop.o is_empty.o -Istack -o main
    
如果是直接把那些目标文件和main.c编译链接在一起,则没有用到的函数也会链接进来。当然另一个好处就是使用静态库只需写一个库文件名，而不需要写一长串目标文件名。

### 动态库与静态库的区别

1 当源码文件与静态库编译链接时,链接器可以从静态库中只取出需要的部分来做链接。而不是全部链接
l 静态库对函数库的链接是放在编译时期完成的。
l 程序在运行时与函数库再无瓜葛，移植方便。(一些游戏里都是采用这种方式)
l 浪费空间和资源，因为所有相关的目标文件与牵涉到的函数库被链接合成一个可执行文件。

### 原文地址
    
https://docs.huihoo.com/c/linux-c-programming/ch20s03.html

todo https://www.sulianlian.com/Linux/2019-08-01-Linux_ffmpeg%E5%AE%89%E8%A3%85%E6%B6%89%E5%8F%8A%E5%88%B0%E7%9A%84%E7%9F%A5%E8%AF%86%E7%82%B9.html