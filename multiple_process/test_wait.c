//
// Created by guangsujiqiang on 3/4/20.
//

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
        // while(1);  // kill -9
        exit(3);

    } else {

        // this is parent process
        int child_stat_val;

        // 如果父进程的所有子进程都还在运行，调用wait将使父进程阻塞
        // wait等待 [第一个终止] 的子进程，而waitpid可以通过pid参数指定等待哪一个子进程
        waitpid(pid,&child_stat_val,0);

        if (WIFEXITED(child_stat_val)){
            printf("Child exited with code %d \n ", WEXITSTATUS(child_stat_val));
        } else if (WIFSIGNALED(child_stat_val)){
            printf("Child terminated abnormally, signal %d \n", WTERMSIG(child_stat_val));
        }

    }

}