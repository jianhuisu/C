#include <stdio.h>
#define MSG "My Name is Wali"
int main(void)
{
    char arr[] = MSG;
    char * pt = MSG;

    printf("address arr is %p \n","My Name is Wali");
    printf("address arr is %p \n",arr);
    printf("address pt is %p \n",pt);
    printf("address MSG is %p \n",MSG);

}

#if 0
    [root@vagrant-centos65 chapter11]# t address.c
    address arr is 0x400658
    address arr is 0x7fff030dcd00
    address pt is 0x400658
    address MSG is 0x400658

    1 数组变量地址在程序运行时分配 为动态内存
    2 字符串常量存储在静态内存
    3 数组是字符串常量的一个副本

    指针表示法声明 字符串 与 数组表示法声明字符串 方式有差别
#endif

