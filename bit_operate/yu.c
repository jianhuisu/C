#include <stdio.h>

void main(void)
{

// c 语言中不能直接定义二进制数 虽然数据保存都是以二进制的形式 只可以直接定义十进制 八进制 十六进制

    unsigned int age = 15;
    unsigned int newage = ~age;

    printf("%d \n",sizeof(int));

}