## fork

### fork 过程解析

 1. 父进程初始化
 1. 父进程调用fork，这是一个系统调用，因此进入内核。
 1. 内核根据父进程复制出一个子进程，父进程和子进程的PCB信息相同，用户态代码和数据也相同
    (注释:两个进程的代码完全相同,不同的是两者之间将要执行的代码分支不同,这些差异性设置保存在PCB中,父进程 子进程之间的数据是相互隔离的)
    因此，子进程现在的状态看起来和父进程一样，做完了初始化，**刚调用了fork进入内核，还没有从内核返回**。
    现在有两个一模一样的进程看起来都调用了`fork`进入内核等待从内核返回（实际上fork只调用了一次），
    **此外系统中还有很多别的进程也等待从内核返回**。(注释:此时内核要进行系统任务调度了,而不是立即返回).
    是父进程先返回还是子进程先返回，还是这两个进程都等待，先去调度执行别的进程，这都不一定，取决于内核的调度算法。
    父、子进程中相同编号的文件描述符在内核中指向同一个file结构体，也就是说，**file结构体的引用计数要增加**。

fork调用的一个奇妙之处就是它仅仅被调用一次，却能够返回两次，它可能有三种不同的返回值：

    1）在父进程中，fork返回新创建子进程的进程ID；
    2）在子进程中，fork返回0；
    3）如果出现错误，fork返回一个负值；

通过`/bin/bash`执行一个命令时, `/bin/bash fork `一个子进程,`Shell`进程的环境变量`PATH`传给了子进程，
父进程在创建子进程时会复制一份环境变量给子进程，但此后二者的环境变量互不影响。

#### 如何产生一个僵尸进程

一个进程在终止时会关闭所有文件描述符(释放FILE结构体)，释放在用户空间分配的内存，但它的PCB还保留着(PCB结构体还没有释放)，
内核在其中保存了一些信息：

 - 如果是正常终止则保存着退出状态.
 - 如果是异常终止则保存着导致该进程终止的信号是哪个.

该子进程的父进程可以调用`wait`或`waitpid`获取这些信息，然后彻底清除掉这个进程.

子进程结束,但是父进程不结束也未`wait`子进程,那么它一直为`defunct`,不能使用`kill`清除僵尸进程,`kill`用来停止进程,僵尸进程已经是停止状态了.
(注释:所以结束该子进程的父进程是清除僵尸进程的一个好办法)
如果父进程先于子进程结束,子进程的父进程改变为`init`.(注释:因为每个进程结束的时候，系统都会扫描当前系统中所运行的所有进程，
看有没有哪个进程是刚刚结束的这个进程的子进程，如果是的话，就由Init来接管他，成为他的父进程).任何进程在刚终止时都是僵尸进程,后续.

由此一个产生僵尸进程的例子:
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    
    int main(void)
    {
        pid_t pid = fork();
    
        if(pid == -1 ){
            perror("fork error");
            exit(EXIT_FAILURE);
        }
    
        if(pid == 0){
            
            // 子进程先于父进程结束 
            printf("this is child \n");
    
        } else {
             
            while(1){
                printf("this is parent \n");
                sleep(5);
            }
    
        }
   
        return 0;
    }
   
如果`main`里面这样实现则不会产生僵尸进程

    int main(void)
    {
        pid_t pid = fork();
    
        if(pid == -1 ){
            perror("fork error");
            exit(EXIT_FAILURE);
        }
    
        if(pid == 0){
    
            sleep(10);
            printf("this is child \n");
    
        } else {
            printf("this is parent \n");
    
        }
    
        return 0;
    }   
   

    
#### 以树状查看进程父子关系

    [guangsujiqiang@su-ct7 multiple_process]$>ps u
    // 找出父进程 pid 
    [guangsujiqiang@su-ct7 multiple_process]$>pstree -p 21157
    a.out(21157)─┬─a.out(21158)
                 └─a.out(21159)
                 
#### 查看一个进程的父进程

    [guangsujiqiang@su-ct7 multiple_process]$>pstree -p 1 | grep -A10 -B10 19713
    [guangsujiqiang@su-ct7 multiple_process]$>pstree -p 1 | head

或者

    [guangsujiqiang@su-ct7 multiple_process]$>sudo ps -ef | grep 19713
    guangsu+ 19713     1  0 13:26 pts/0    00:00:00 ./a.out
    guangsu+ 23847 16728  0 14:05 pts/4    00:00:00 grep --color=auto 19713

#### 父进程如何获取子进程的退出信息

    #include <sys/types.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(void)
    {
        pid_t pid;
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }
        if (pid == 0) {
            int i;
            for (i = 3; i > 0; i--) {
                printf("This is the child\n");
                sleep(1);
            }
            exit(3);
        } else {
            int stat_val;
            waitpid(pid, &stat_val, 0);
            if (WIFEXITED(stat_val))
                printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
            else if (WIFSIGNALED(stat_val))
                printf("Child terminated abnormally, signal %d\n", WTERMSIG(stat_val));
        }
        return 0;
    }

子进程的终止信息在一个`int`中包含了多个字段，用宏定义可以取出其中的每个字段：

 - 如果子进程是正常终止的，`WIFEXITED`取出的字段值非零，`WEXITSTATUS`取出的字段值就是子进程的退出状态.
 - 如果子进程是收到信号而异常终止的，`WIFSIGNALED`取出的字段值非零，`WTERMSIG`取出的字段值就是信号的编号.


