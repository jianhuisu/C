//
// Created by guangsujiqiang on 3/4/20.
//

#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int counter;
    alarm(1); // 这个程序的作用是1秒钟之内不停地数数，1秒钟到了就被SIGALRM信号终止
    for(counter=0; 1; counter++)
    {
        printf("counter=%d \n", counter);
    }

    return 0;
}