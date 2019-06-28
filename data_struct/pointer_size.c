#include <stdio.h>

// question 指针变量的大小都是 1 字节吗
void main(void)
{
    int age = 5;
    char name[3] = "a";
    int * pint = &age;
    char * pchar = name;

    printf("size of int  pointer %d \n",sizeof(pint));
    printf("siez of char pointer %d \n",sizeof(pchar));

}