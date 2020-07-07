#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int a = 1;
    int * pi = &a;
    int ** pii = &pi;

    printf(" %p %d \n",pi,*pi);
    printf(" %p %p\n",pii,*pii);

    int b = 2;
    *pi = b;
    // *指针， 变量存储的常规变量的存储地址.
    // ** 指向指针的指针,就是二级指针，它第一级指针存储的的内容还是指针，该指针指向
    return 0;
}