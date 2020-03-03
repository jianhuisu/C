//
// Created by guangsujiqiang on 3/3/20.
//
#include <stdio.h>
#include <unistd.h>

int main(int argc,char * argv[])
{
    int n;
    char *message;
    pid_t pid;
    pid = fork();

    if(pid < 0){
        perror("fork error");
    }

    if(pid == 0){
        // this is child
        message = "child";
        n = 6;
    } else {
        // this is parent
        message = "parent";
        n = 3;
    }

    for(;n>0;n--)
    {
        sleep(1);
        printf("this is from %s \n",message);
    }

}
