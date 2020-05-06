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