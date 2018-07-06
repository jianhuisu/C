#include <stdio.h>

/*
    tip1 通常 类型说明符* 与 指针名之间的空格可有可无 char * c  与 char *c 均可用 一般 声明时  使用空格 解引用时 不使用空格
    tip2 指针变量 p 的值为无符号整数 但是不可以对指针变量使用一般整数运算公式 实际上指针变量的值是一种新的数据类型 使用%p转换符打印
    tip3 int * p;  表示指针指向的值(*p) 类型为整数
    tip4 声明指针变量时必须指定指针变量的类型 因为不同类型变量在内存中存储方式不一样

*/
void main(void)
{
    int * p;
    char * c;
    int a = 1;
    char b = 'c';

    p = &a;
    c = &b;

    printf("hello world %p %p \n",p,c);
}




