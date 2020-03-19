## size

UNIX下可使用size命令查看**可执行文件**的段大小信息。如`size a.out`

    [guangsujiqiang@su-ct7 static_library]$>size main
    text    data     bss     dec     hex filename
    1215     544     544    2303     8ff main

复习下ELF文件的内容

 - .text   代码段
 - .data   数据段之一  主要存储已初始化的全局变量和已初始化的局部静态变量
 - .bss    数据段之一  主要存储未初始化的全局变量和未初始化局部静态变量 （Block Started by Symbol） (read + write)
 - .rodata 数据段之一 主要存储字符串常量 read only  
 
