## 守护进程

 - 创建守护进程最关键的一步是调用`setsid`函数创建一个新的`Session`，并成为`Session Leader`。
 - 当前进程不允许是进程组的`Leader`，否则该函数返回-1。要保证当前进程不是进`程组的Leader`也很容易，只要先`fork`再调用`setsid`就行了。
 - 守护进程通常采用以d结尾的名字 eg. `gcc test.c -o mydaemond && ./mydatemond`


    #include <stdlib.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <unistd.h>
    
    void daemonize(void)
    {
        pid_t  pid;
    
        /*
         * Become a session leader to lose controlling TTY.
         */
        if ((pid = fork()) < 0) {
            perror("fork");
            exit(1);
        } else if (pid != 0){
            /* parent */
            exit(0);
        }
    
        // child begin 
    
        setsid();
    
        /*
         * Change the current working directory to the root.
         */
        if (chdir("/") < 0) {
            perror("chdir");
            exit(1);
        }
    
        /*
         * Attach file descriptors 0, 1, and 2 to /dev/null.
         */
        close(0);
        open("/dev/null", O_RDWR);
        dup2(0, 1);
        dup2(0, 2);
    }
    
    int main(void)
    {
        daemonize();
    
        // 父进程fork完事之后 直接exit,而子进程会从daemonize函数返回,继续执行 也就是 执行 while(1);
    
        // ！！！！！！！！ 只有子进程会执行到这里
        while(1);
        return 0;
    }