## 进程间通信 IPC(InterProcess Communication) 

每个进程各自有不同的用户地址空间，任何一个进程的全局变量在另一个进程中都看不到，所以进程之间要交换数据必须通过内核，
在内核中开辟一块缓冲区，进程1把数据从用户空间拷到内核缓冲区，进程2再从内核缓冲区把数据读走，内核提供的这种机制称为进程间通信

### 管道

管道是一种最基本的IPC机制，由pipe函数创建：

    #include <unistd.h>
    int pipe(int filedes[2]);
    
调用pipe函数时在内核中开辟一块缓冲区（称为管道）用于通信，它有一个读端一个写端，然后通过filedes参数传出给用户程序两个文件描述符，
filedes[0]指向管道的读端，filedes[1]指向管道的写端（很好记，就像0是标准输入1是标准输出一样）。
所以管道在用户程序看起来就像一个打开的文件，通过read(filedes[0]);或者write(filedes[1]);向这个文件读写数据其实是在读写内核缓冲区。
pipe函数调用成功返回0，调用失败返回-1。

    man 3 pipe
    
查看进程打开的fd列表
    
    [guangsujiqiang@su-ct7 bp]$>ll /proc/21671/fd
    total 0
    lrwx------ 1 guangsujiqiang guangsujiqiang 64 Mar  3 17:00 0 -> /dev/pts/4
    lrwx------ 1 guangsujiqiang guangsujiqiang 64 Mar  3 17:00 1 -> /dev/pts/4
    lrwx------ 1 guangsujiqiang guangsujiqiang 64 Mar  3 16:59 2 -> /dev/pts/4
    l-wx------ 1 guangsujiqiang guangsujiqiang 64 Mar  3 17:00 4 -> pipe:[2638542]
    [guangsujiqiang@su-ct7 bp]$>lsof -p 21671
    COMMAND   PID           USER   FD   TYPE DEVICE SIZE/OFF      NODE NAME
    a.out   21671 guangsujiqiang  cwd    DIR   8,17       54 554209124 /home/guangsujiqiang/CLionProjects/C/IPC
    a.out   21671 guangsujiqiang  rtd    DIR   8,17     4096        96 /
    a.out   21671 guangsujiqiang  txt    REG   8,17     8768 554681442 /home/guangsujiqiang/CLionProjects/C/IPC/a.out
    a.out   21671 guangsujiqiang  mem    REG   8,17  2156160     84085 /usr/lib64/libc-2.17.so
    a.out   21671 guangsujiqiang  mem    REG   8,17   163400     84078 /usr/lib64/ld-2.17.so
    a.out   21671 guangsujiqiang    0u   CHR  136,4      0t0         7 /dev/pts/4
    a.out   21671 guangsujiqiang    1u   CHR  136,4      0t0         7 /dev/pts/4
    a.out   21671 guangsujiqiang    2u   CHR  136,4      0t0         7 /dev/pts/4
    a.out   21671 guangsujiqiang    4w  FIFO    0,9      0t0   2638542 pipe

单个管道只能实现单向通信
    
### 其它IPC机制

进程间通信必须通过内核提供的通道，而且必须有一种办法在进程中标识内核提供的某个通道，
上一节讲的管道是用打开的文件描述符来标识的。如果要互相通信的几个进程没有从公共祖先那里继承文件描述符，
它们怎么通信呢？内核提供一条通道不成问题，问题是如何标识这条通道才能使各进程都可以访问它？文件系统中的路径名是全局的，
各进程都可以访问，因此可以用文件系统中的路径名来标识一个IPC通道。
`FIFO`和`UNIX Domain Socket`这两种IPC机制都是利用文件系统中的特殊文件来标识的。可以用mkfifo命令创建一个FIFO文件：

    $ mkfifo hello
    $ ls -l hello
    prw-r--r-- 1 akaedu akaedu 0 2008-10-30 10:44 hello
    
FIFO文件在磁盘上没有数据块，仅用来标识内核中的一条通道，各进程可以打开这个文件进行read/write，
实际上是在读写内核通道（根本原因在于这个file结构体所指向的read、write函数和常规文件不一样），
这样就实现了进程间通信。UNIX Domain Socket和FIFO的原理类似，也需要一个特殊的socket文件来标识内核中的通道，例如/var/run目录下有很多系统服务的socket文件：
    
    [guangsujiqiang@su-ct7 bp]$>ls -l /var/run/ | grep ^s
    srw-rw-rw-  1 root           root              0 Mar  3 13:42 gssproxy.sock
    srw-rw-rw-  1 root           root              0 Mar  3 13:42 rpcbind.sock
    
文件类型s表示socket，这些文件在磁盘上也没有数据块。UNIX Domain Socket是目前最广泛使用的IPC机制

一些常见的IPC机制

 - 管道
 - FIFO
 - mmap函数，几个进程可以映射同一内存区
 - SYS V IPC，以前的SYS V UNIX系统实现的IPC机制，包括消息队列、信号量和共享内存，现在已经基本废弃
 - UNIX Domain Socket，目前最广泛使用的IPC机制 
 
 IPC包括LPC/RPC,LPC
 
`管道` `FIFO` `mmap` 适合 LPC , `UNIX Domain Socket` 适合RPC

## 参考资料

笔记摘自宋劲杉老师的书,因为怕以后资源被封.所以这里摘录以下 