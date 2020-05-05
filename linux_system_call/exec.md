## exec

用fork创建子进程后执行的是和父进程相同的程序（但有可能执行不同的代码分支），子进程往往要调用一种exec函数以执行另一个程序。
当进程调用一种exec函数时，该进程的用户空间代码和数据完全被新程序替换，从新程序的启动例程开始执行。

    #include <unistd.h>
    #include <stdlib.h>
    
    int main(void)
    {
        execlp("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
        perror("exec ps");
        exit(1);
    }