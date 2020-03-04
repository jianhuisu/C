## coredump

### 1 什么是 Core Dump

首先解释什么是Core Dump。当一个进程要异常终止时,可以选择把进程的用户空间内存数据全部保存到磁盘上,文件名通常是core,这叫做Core Dump。进程异常终止通常是因为有Bug,比如非法内存访问导致段错误,事后可以用调试器检查core文件以查清错误原因,这叫做Post-mortem Debug。一个进程允许产生多大的core文件取决于进程的Resource Limit（这个信息保存在PCB中）。默认是不允许产生core文件的,因为core文件中可能包含用户密码等敏感信息,不安全。在开发调试阶段可以用ulimit命令改变这个限制,允许产生core文件。

### 2 如何生成core dump文件

在终端中输入命令 ulimit -c ,输出的结果为 0,说明默认是关闭 core dump 的,即当程序异常终止时,也不会生成 core dump 文件。
可以使用命令开启 core dump 功能,并且不限制 core dump 文件的大小作为生成条件； 

    ulimit -c unlimited 

如果需要限制文件的大小,将 unlimited 改成你想生成 core 文件最大的大小,注意单位为 blocks（KB）。

#### 永久开启 

way 1：

...修改配置文件（没测过  没必要 不希望这样干 太危险）

way 2：

登陆 LINUX 服务器,任意位置键入

    echo "ulimit -c 1024" >> /etc/profile
    source /etc/profile

#### 手动模拟生成coredump文件

    kill -s SIGSEGV $$  // 关闭当前shell进程

### 3 coredump文件的存储位置

默认路径和名字是在执行路径下生成core文件,生成文件存放的路径和名字可以自己设置
不要用vi编辑这个文件,这个文件的正确编辑方法是:

    sudo echo "/data/coredump/core-%e-%p-%t" > /proc/sys/kernel/core_pattern

这是一个长的像文件的特殊文件

在path_name路径下,生成corefile_pid_uid_signal_id.注意：如果配置的path 没有写入权限,不会生成coredump文件

 - %p - insert pid into filename 添加 pid
 - %u - insert current uid into filename 添加当前 uid
 - %g - insert current gid into filename 添加当前 gid
 - %s - insert signal that caused the coredump into the filename 添加导致产生 core 的信号
 - %t - insert UNIX time that the coredump occurred into filename 添加 core 文件生成时的 unix 时间
 - %h - insert hostname where the coredump happened into filename 添加主机名
 - %e - insert coredumping executable name into filename 添加命令名

### 4 关闭 coredump

    ulimit -c 0

### 5 产生coredump的原因

1 内存溢出  局部变量中使用大变量
2 非法指针
3 内存访问越界
4 多线程程序使用了非线程安全函数
5 多线程未读写保护

### 6 how to use gdb debug

method 1 :

    gdb ./test [core file]
    gdb  可执行文件 coredump文件

method 2 :

    gdb -c [core file]
    gdb -c coredump文件


### 参考资料

 - https://blog.csdn.net/follow_blast/article/details/82117390
 - https://blog.csdn.net/MOU_IT/article/details/88903668
 - https://docs.huihoo.com/c/linux-c-programming/ch33s02.html  宋劲杉
