## `wait` and `wait_pid`

`wait`等待**第一个终止的子进程**，而`waitpid`可以通过`pid`参数指定等待哪一个子进程.
(这意味着 如果fork了多个子进程,`wait`只会等待第一个,而不会等待其它的子进程),也就是说
`wait`只有在父进程的所有子进程都还在运行时**阻塞**.

#### waitpid

`waitpid`等待接收指定子进程,如果有多个子进程,其它子进程先于指定子进程结束,`waitpid`仍然阻塞,先结束的子进程处于僵死状态,如下

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
`waitpid`最常用的选项是`WNOHANG`，它告知内核在没有已终止子进程时不要阻塞。

linux中的wait函数等到一个子进程退出就会返回，恢复到执行状态。要想等所有子进程退出可以用waitpid函数
    
    pid_t wait(pid_t pid,int * status,int options);
    
 - pid>0时，只等待pid与该参数相同的子进程，如果该子进程一直没有退出，那么父进程会一直阻塞；
 - pid=0时，会等待同一个进程组的子进程，若子进程加入了其他进程组，waitpid()不再关心它的状态；
 - pid=-1时，waitpid()与wait()函数相同，将阻塞等待并回收一个子进程；
 - pid<-1时，会等待指定进程组的任何子进程，进程组的id等于pid的绝对值；