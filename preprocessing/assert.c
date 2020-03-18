//
// Created by guangsujiqiang on 3/18/20.  这个断言就像php的 xdebug debug_backtrace()；exit() 组合使用一样,用来协助我们调试错误的利器
//
#include <stdio.h>
#include <math.h>
#include <assert.h>

void main(void)
{
    float x,y,z;
    while(scanf("%1f%1f",&x,&y) == 2 && (x != 0 || y != 0))
    {
        z = x*x - y*y;
        assert( z >= 0 );
        printf("answer is %f \n",sqrt(z));
    }

    puts("Done");


}

// gcc assert.c -lm -o main
// 会产生coredump文件  kill -6   或者 kill -SIGABRT -pid