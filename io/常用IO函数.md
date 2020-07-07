#### 常用IO函数

根据使用场景不同,主要分为以下三种,便于记忆.

 - 以字节为单位的IO函数  `int fgetc(FILE *stream);`  `int getchar(void);`  使用此类函数读取汉字会存在乱码问题.
 - 以字符串为单位的IO函数 `char *fgets(char *s, int size, FILE *stream);`  `char *gets(char *s);`
 - 以记录为单位的IO函数  `size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);`  `size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);`    

备注：记忆小技巧

    fgetc = f + get + c = f + get + char 
    fgets = f + get + s = f + get + string 
 
#### I/O常见种类

 - 本地文件I/O   `file`
 - 联机网络I/O   `sockets`

#### 乱码问题
 
        char ch;
        char b;
    
        ch = getchar();
        printf("-%c- \n",ch);
        b = getchar();
        printf("-%c- \n",b);
        printf("------\n");
 
当你的输入是一个汉字,赋值给到`ch`的只是汉字编码中的部分字节,输入缓冲中还遗留着部分字节.打印的时候,不但为乱码,第二次输出也不为空.
    
    gcc test.c && ./a.out
    /home/sujianhui/CLionProjects/C/cmake-build-debug/test
    我
    -�- 
    -�- 
    ------ 
    
但是,如果我的输入为一个英文子母时,发现有输入缓冲中由两个字符,依次是子母`s`,特殊字符`\r`.

    /home/sujianhui/CLionProjects/C/cmake-build-debug/test
    请输入先序遍历顺序下各个结点的值,#表示没有结点:
    s
    -s- 
    -
    - 
    ------
    
    
#### `fopen()` 与 `fclose()`

fopen调用应该和fclose调用配对，打开文件操作完之后一定要记得关闭。
不调用`fclose()`，在进程退出时系统会自动关闭文件.
但是不能因此就忽略`fclose()`调用，如果写一个长年累月运行的程序（比如网络服务器程序），打开的文件都不关闭，堆积得越来越多，就会占用越来越多的系统资源。
换句话说,可能某天你封装的函数就会在常驻内存程序中引用,显然,如果你成对使用`fopen()/fclose()`，你就可以放心的引用了.

#### `perror()` 与 `errno`

所以一个系统函数错误返回后应该马上检查errno，在检查errno之前不能再调用其它系统函数。
    
    #include <stdio.h>
    #include <errno.h>
    #include <stdlib.h>
     
    if (fp == NULL) {
            perror("Open file abcde");
            printf("errno: %d\n", errno);
            exit(1);
    }
   
`printf`打印的错误号可能并不是`fopen`产生的错误号，也有可能是`perror`产生的错误号.
`errno`是一个全局变量，很多系统函数都会改变它.
大多数系统函数都有一个`Side Effect`，就是有可能改变`errno`变量.
虽然`perror`可以打印出错误原因，传给`perror`的字符串参数仍然应该提供一些额外的信息，以便在看到错误信息时能够很快定位.

`strerror`函数可以根据错误号返回错误原因字符串.

    #include <string.h>
    char *strerror(int errnum);
    
这个函数返回指向静态内存的指针(返回值：错误码`errnum`所对应的字符串).有些函数的错误码并不保存在`errno`中，而是通过返回值返回，
就不能调用`perror`打印错误原因了，这时`strerror`就派上了用场.

    int n = func_call(...);
    fputs(strerror(n), stderr);
    
### `fgetc` / `getchar()` / `getc()`

系统对于每个打开的文件都记录着当前读写位置在文件中的地址（或者说距离文件开头的字节数），也叫偏移量`Offset`。
当文件打开时，读写位置是`0`，每调用一次`fgetc`，读写位置向后移动一个字节，因此可以连续多次调用`fgetc`函数依次读取多个字节。

从终端设备读有点特殊。当调用`getchar()`或`fgetc(stdin)`时，如果用户没有输入字符，`getchar()`函数就阻塞等待，
所谓阻塞是指这个函数调用不返回，也就不能执行后面的代码，这个进程阻塞了，操作系统可以调度别的进程执行。
**从终端设备读还有一个特点，用户输入一般字符并不会使`getchar()`函数返回，仍然阻塞着，只有当用户输入回车或者到达文件末尾时`getchar()`才返回**。
这个程序的执行过程分析如下：

    $ ./a.out
    hello
    // 输入hello并回车，这时第一次调用getchar返回，读取字符h存到文件中，然后连续调用getchar五次，读取ello和换行符存到文件中,当第七次调用getchar()时阻塞
    hey
    // 输入hey并回车，第七次调用getchar返回,读取字符h存到文件中，然后连续调用getchar三次，读取ey和换行符存到文件中，第11次调用getchar()时阻塞
    // 这时输入Ctrl-D，第11次调用getchar返回EOF，跳出循环，进入下一个循环，回到文件开头，把文件内容一个字节一个字节读出来打印，直到文件结束
    hello
    hey

操作打开文件的`offset`的函数

操作读写位置的函数

 - `rewind`函数把读写位置移到文件开头. `void rewind(FILE *stream);`
 - `ftell`可以返回当前的读写位置. `long ftell(FILE *stream);`
 - `fseek`可以任意移动读写位置. `int fseek(FILE *stream, long offset, int whence);`

fseek的whence和offset参数共同决定了读写位置移动到何处，whence参数的含义如下：

 - SEEK_SET  从文件开头移动offset个字节
 - SEEK_CUR  从当前位置移动offset个字节
 - SEEK_END  从文件末尾移动offset个字节

`offset`可正可负，负值表示向前（向文件开头的方向）移动，
正值表示向后（向文件末尾的方向）移动，如果向前移动的字节数超过了文件开头则出错返回，
如果向后移动的字节数超过了文件末尾，再次写入时将增大文件尺寸，从原来的文件末尾到fseek移动之后的读写位置之间的字节都是0。        

### `fgets()` / `fputs()`
        
 - gets函数的存在只是为了兼容以前的程序，我们写的代码都不应该调用这个函数. 
 - 输入输出函数应该配套使用，`fgets() + fputs()` 而不是`fgets() + puts()`,否则会因为对结束特殊处理方式不同,而出现一些意外问题.
 
现在解释一下`fgets()`函数的工作流程:

    char buf[5];
    while( fgets(buf,5,fp) !=  NULL ){
        fputs(buf,stdout);
    }

 1. 假设输入字符串为"mynameissujianhui", **读取以`'\n'`结尾的一行（包括`'\n'`在内）** 存到`缓冲区buf`中.因为一行内容超过缓冲区容量(`buf`只能容纳五个字节),所以需要多次读取,才能完整的读取完成输入字符串.
 2. 当`fgets()`每次从`句柄 fp`读取`5-1`(缓冲区长度size-1)个字符时,还没有读取到`'\n'`字符,
    已经读到的`size-1`个字符 + `一个'\0'字符`存入缓冲区(正好填满缓冲区)，剩下的部分可以在下次调用`fgets`时继续读.
 1. 如果一次`fgets`调用在读入若干个字符后到达文件末尾，则将已读到的字符串加上'\0'存入缓冲区并返回.
 1. 再次调用`fgets`则返回`NULL`，可以据此判断是否读到文件末尾.(使用gdb调试观察)
 
意：`fgets`只适合读文本文件而不适合读二进制文件，并且文本文件中的所有字符都应该是可见字符，不能有`'\0'`.(想一想为什么 跟`'/0'`有关)

