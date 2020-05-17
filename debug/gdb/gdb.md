## gdb overview 
    
这部分超有用

    watch  观察点                   设置观察点  // (gdb) watch input[5]  ,设置了观察点之后 可以使用 c 运行到下一个观察点
    info（或i） watchpoints	       查看当前设置了哪些观察点
    x	                           从某个位置开始打印存储单元的内容，全部当成字节来看，而不区分哪个字节属于哪个变量
    
    (gdb) x/7b input
    0xbfb8f0a7:	0x31	0x32	0x33	0x34	0x35	0x00	0x00
    
    x命令打印指定存储单元的内容。7b是打印格式，b表示每个字节一组，7表示打印7组
    
    detach  将debug从原程序中剥离,无debug模式运行原程序  
    
    
    
eg.

    gdb -Wall -g break.c -o main
    gdb main
    ...
    list 
    start 
    n
    n
    watch input[5]
    info watchpoints
    c
    ...
    c
    finish
    ...
    q
    
### gdb debug php source code

    ./configure --prefix=/home/sujianhui/php/output/php7.1/ --enable-fpm --enable-debug
    make && make install
    gdb /home/sujianhui/php/output/php7.1/bin/php
    ...
    break ECHO_SPEC_CV_HANDLER
    r 1.php
    
    
### gdb 附加一个进程到调试模式 
    
    ps aux | grep php //  find master process pid 
    gdb -p 
    ps aux | grep php-fpm 

### gdb调试coredump

    gdb ./server.c core.8982
    ->bt 或者 where  // 查看调用堆栈 找到出错位置    
    
 - 在带上调试信息的情况下，我们实际上是可以看到core的地方和代码行的匹配位置。
 - 在不带调试信息的情况下，使用过滤法( 但往往正常发布环境是不会带上调试信息的，因为调试信息通常会占用比较大的存储空间，一般都会在编译的时候把-g选项去掉。)
    
eg.

    -> f 1
    -> disassemble
    -> 在汇编代码中找到leave那一行
    
https://blog.csdn.net/sunxiaopengsun/article/details/72974548