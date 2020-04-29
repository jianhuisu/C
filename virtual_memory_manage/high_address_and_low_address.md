## 内存地址中的高地址与低地址

可以把主存看成一本空白的作业本，你现在要在笔记本上记录一些内容，他的页码排序是

    第一页  : 0x0000001
    第二页  : 0x0000002
    ...
    最后一页: 0x0000092

1 如果你选择`从前向后记录`(用完第一页，用第二页,类推)这就是先使用低地址，后使用高地址.

    0x0000001 -> 0x0000002-> ...  -> 0x0000092

业内有这样表述:动态分配内存时堆空间向高地址增长,说的就是这种情况.
这个向高地址增长就是先使用低地址,后使用高地址的意思.

2 如果你选择`从后往前记录`(先用笔记本的最后一页,用完后使用倒数第二页，类推) 这就是先使用高地址,后使用低地址

    0x0000092 -> ... ->0x0000002 -> 0x0000001
    
业内表述：`0xbfac 5000-0xbfad a000`是栈空间，其中高地址的部分保存着进程的环境变量和命令行参数，低地址的部分保存函数栈帧，**栈空间是向低地址增长的**.
这个向低地址增长就是先使用高地址,后使用低地址的意思.
    
这个`高地址`与`低地址`容易与`高位``低位`产生混淆.

比如我这个月工资为`1234`(一千二百叁拾肆块),那么这串数字的左边我们称呼为高位，右边称为低位.
(这个高低来自于人类的阅读习惯,数字从左向右,表示由大到小)

在计算机中以`int`类型存储工资,假设`int`占用四个字节,假设每个字节占一个地址,每个字节地址如下
    
    0x00008
    0x00009
    0x0000a 
    0x0000b
 
把工资加载到内存中时，就会有两种存储方式，如下:

    // 大端法
    0x00008   => 1
    0x00009   => 2
    0x0000a   => 3 
    0x0000b   => 4
    
或者
    
    // 小端法
    0x00008   => 4
    0x00009   => 3
    0x0000a   => 2 
    0x0000b   => 1    

内存中的低地址存储工资中的高位这种方式称为`大端法`.如果把上边的存储方式反过来,内存中的高地址存储工资中的高位,则称为`小端法 little endian`.
(注释:可以采用异或方法来记忆 低地址存低位为小端法-> `弟弟小` ^O-O^).
主机采用大端还是小端表示数据由CPU的架构决定,如果两个主机只见交互数据,但是字节序表示不同,需要同化.

#### 如何查询自己的CPU采用哪种字节序

找一个可执行文件,查看ELF Header:

    [root@ share_library]$>readelf -a libstack.so.1.0 
    Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
    Class:                             ELF64
    
    // ---------->这里呦
    Data:                              2's complement, little endian  
    
    Version:                           1 (current)
    OS/ABI:                            UNIX - System V
    ABI Version:                       0
    Type:                              DYN (Shared object file)
    Machine:                           Advanced Micro Devices X86-64
    Version:                           0x1
    Entry point address:               0x660
    Start of program headers:          64 (bytes into file)
    Start of section headers:          8080 (bytes into file)
    Flags:                             0x0
    Size of this header:               64 (bytes)
    Size of program headers:           56 (bytes)
    Number of program headers:         7
    Size of section headers:           64 (bytes)
    Number of section headers:         33
    Section header string table index: 30

