//
// Created by guangsujiqiang on 3/4/20.
// produce a zombie process , kill child process by kill it's parent process
//

#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    pid_t pid;
    int n;
    char *message;

    pid = fork();

    if(pid < 0){
        perror("fork");
    }

    if(pid == 0){
        message = "this is child";
        n=6;
    }else{
        message = "this is parent";
        n=3;
        while(1);
    }

    for(;n>0;n--){
        //sleep(1);
        printf(" %s \n ",message);
    }

    return 0;
}
