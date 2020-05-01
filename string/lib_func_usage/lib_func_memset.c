#include <stdio.h>
#include <string.h>

char global_name[10];

int main(void)
{
    // 全局变量或者静态变量 自动初始化为0 (因为位于 .bss段)
    printf(" string : [%s]\n",global_name);

    // 如果变量是局部变量 声明后没有初始化 ，则初值是不确定的
    char name[10];
    printf(" string : [%s]\n",name);

    // void *memset(void *s, int c, size_t n);
    // memset函数把s所指的内存地址开始的n个字节都填充为c的值。通常c的值为0，把一块内存区清零
    // 由malloc分配的内存初值也是不确定的，需要用memset清零
    memset(name,0,10);
    printf(" string : [%s] \n",name);
    return 0;

}

/*

 /home/sujianhui/CLionProjects/C/cmake-build-debug/test
 string : []
 string : [�;�]
 string : []

Process finished with exit code 0


*/