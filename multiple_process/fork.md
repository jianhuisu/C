## fork

fork调用的一个奇妙之处就是它仅仅被调用一次，却能够返回两次，它可能有三种不同的返回值：

    1）在父进程中，fork返回新创建子进程的进程ID；
    2）在子进程中，fork返回0；
    3）如果出现错误，fork返回一个负值；

通过/bin/bash 执行一个命令时, /bin/bash fork 一个子进程,Shell进程的环境变量PATH传给了子进程，
父进程在创建子进程时会复制一份环境变量给子进程，但此后二者的环境变量互不影响。

子进程结束,但是父进程不结束也未wait子进程,那么它一直为defunct,不能使用kill清除僵尸进程,kill用来停止进程,僵尸进程已经停止了
如果父进程先于子进程结束,子进程的父进程改变为init(pid为1)

在UNIX 系统中，一个进程结束了，但是他的父进程没有等待(调用wait / waitpid)他， 那么他将变成一个僵尸进程。
但是如果该进程的父进程已经先结束了，那么该进程就不会变成僵尸进程， 因为每个进程结束的时候，系统都会扫描当前系统中所运行的所有进程， 
看有没有哪个进程是刚刚结束的这个进程的子进程，如果是的话，就由Init 来接管他，成为他的父进程……


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

#### 多个子进程时的等待状态 

waitpid 只会等待接收指定子进程,如果有多个子进程,其它子进程先于指定子进程结束,waitpid仍然阻塞,先结束的子进程处于僵死状态,如下

    #include <stdio.h>
    #include <unistd.h>
    #include <sys/wait.h>
    #include <stdlib.h>
    
    int main(int argc,char ** argv)
    {
        pid_t pid;
    
        pid = fork();
    
        if(pid < 0){
            perror("fork");
        }
    
        if(pid == 0){
            // this is child process
            int n = 5;
            for(n;n>0;n--){
                sleep(1);
                printf(" --> %d \n",n);
            }
    
            while(1);  // kill -9
            exit(3);
    
        } else {
    
    
            pid_t pid_2;
            pid_2 = fork();
    
            if(pid_2 == 0){
                // child
                while(1)
                    sleep(1);
            } else {
    
                // parent
                // this is parent process
                int child_stat_val;
    
                waitpid(pid,&child_stat_val,0);
    
                if (WIFEXITED(child_stat_val)){
                    printf("Child exited with code %d \n ", WEXITSTATUS(child_stat_val));
                } else if (WIFSIGNALED(child_stat_val)){
                    printf("Child terminated abnormally, signal %d \n", WTERMSIG(child_stat_val));
                }
            }
    
        }
    
    }
    
编译执行以后,可以分别kill两个子进程观察父进程的反应.    

#### 僵尸进程 

如何查找僵尸进程

    ps -A | grep defunct
    
如何杀死僵尸进程

 - 1 找到僵尸进程的父进程， kill 父进程
 - 2 重启