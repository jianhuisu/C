## 系统资源配额

Linux系统对于每个用户都会限制其资源使用,可以用`ulimit -a`来显示当前用户的各种限制。

    [sujianhui@nlp a_test]$ ulimit -a
    core file size          (blocks, -c) 0
    data seg size           (kbytes, -d) unlimited
    scheduling priority             (-e) 0
    file size               (blocks, -f) unlimited
    pending signals                 (-i) 30911
    max locked memory       (kbytes, -l) 64
    max memory size         (kbytes, -m) unlimited
    open files                      (-n) 1024
    pipe size            (512 bytes, -p) 8
    POSIX message queues     (bytes, -q) 819200
    real-time priority              (-r) 0
    stack size              (kbytes, -s) 8192
    cpu time               (seconds, -t) unlimited
    max user processes              (-u) 4096
    virtual memory          (kbytes, -v) unlimited
    file locks                      (-x) unlimited

相应的解释:
    
    ...
    -m     The maximum resident set size (many systems do not honor this limit)
    -v     The maximum amount of virtual memory available to the shell and, on some systems, to its children
    
    // 开启coredump功能后,当dump内容占用空间超过该项值时,生成corefile进行保存
    -c     The maximum size of core files created
    // 单个进程的数据段最大长度
    -d     The maximum size of a process's data segment 
    // 每个进程最大打开的文件描述符数
    -n     The maximum number of open file descriptors (most systems do not allow this value to be set)
    // 每个用户允许创建的最大进程数 默认为 4096个
    -u     The maximum number of processes available to a single user
    // 进程栈空间的大小
    -s     The maximum stack size
    ...

进程可以申请的最大空间受到多方面因素的影响，以32位架构平台为例子,从进程的角度来看,每个进程可以拥有4G字节的虚拟空间.
 
 - 最高的1G字节(从虚拟地址0xC0000000到0xFFFFFFFF)，供内核使用，称为`内核空间`.
 - 较低的3G字节(从虚拟地址0x00000000到0xBFFFFFFF)，供用户进程使用，称为`用户空间`.

TODO 有时间可以研究一下redis的内存管理机制,印证一下进程可以使用的最大内存空间问题.

临时更改值使用`ulimit`即可,永解更改需要修改配置文件`vi /etc/security/limits.conf`:

    # 添加如下的行
    * soft noproc 11000
    * hard noproc 11000
    * soft nofile 4100
    * hard nofile 4100
        
注释：`*`代表针对所有用户，`noproc`是代表最大进程数，`nofile`是代表最大文件打开数