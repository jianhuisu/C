#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 80

int main(void)
{
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) { /* parent */

        printf(" %d \n ",pid);
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
        wait(NULL);
        while(1); // 这是为了便于观察进程打开文件描述符 未包含任何阻塞操作的话 这个死循环会占满CPU
    } else {       /* child */
        printf(" %d \n ",pid);
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }

    return 0;
}