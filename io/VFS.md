## VFS virtual file system 虚拟文件系统

Linux支持各种各样的文件系统格式，如`ext2`、`ext3`、reiserfs、FAT、NTFS、iso9660等等，不同的磁盘分区、
光盘或其它存储设备都有不同的文件系统格式，然而这些文件系统都可以mount到某个目录下，使我们看到一个统一的目录树，
各种文件系统上的目录和文件我们用ls命令看起来是一样的，读写操作用起来也都是一样的，这是怎么做到的呢？
Linux内核在各种不同的文件系统格式之上做了一个抽象层，使得文件、目录、读写访问等概念成为抽象层的概念，
因此各种文件系统看起来用起来都一样，这个抽象层称为虚拟文件系统（VFS，Virtual Filesystem）。

ext2 ext3 为Linux常用文件系统格式,兼容性最好.

### 巧妙的数据结构

    PCB
        -> file  descriptors table
            item_1 fd:1 ----------------> kernel space : file struct
                                                                -- f_op : file_operations struct {lseek/open/write/read/release...}   
                                                                -- ...   
                          
每个file结构体都指向一个`file_operations`结构体，这个结构体的成员都是函数指针，指向实现各种文件操作的内核函数。
比如在用户程序中`read`一个文件描述符，`read`通过系统调用进入内核，然后找到这个文件描述符所指向的`file`结构体，
找到`file`结构体所指向的`file_operations结构体`，调用它的`read成员`所指向的内核函数以完成用户请求。

在用户程序中调用lseek、read、write、ioctl、open等函数，最终都由内核调用file_operations的各成员所指向的内核函数完成用户请求。
file_operations结构体中的release成员用于完成用户程序的close请求，之所以叫release而不叫close是因为它不一定真的关闭文件，而是减少引用计数，只有引用计数减到0才关闭文件。
对于同一个文件系统上打开的常规文件来说，read、write等文件操作的步骤和方法应该是一样的，调用的函数应该是相同的。
**如果打开一个字符设备文件，那么它的read、write操作肯定和常规文件不一样，不是读写磁盘的数据块而是读写硬件设备，
所以file结构体应该指向不同的file_operations结构体，其中的各种文件操作函数由该设备的驱动程序实现。**                                        
          
          
### 参考资料

http://akaedu.github.io/book/ch29s02.html                                                  