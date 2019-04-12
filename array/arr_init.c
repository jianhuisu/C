#include <stdio.h>
#define SIZE 12
void de(void);
void full(void);

void main(void)
{
    const int mon_day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int index;

    for(index = 0;index < 12;index++)
    {
         printf("month %d days is %d\n",index+1,mon_day[index]);
    }

    de();
    full();
}

void de(void)
{
        int ran[SIZE];
        int x;

        for(x = 0;x < SIZE;x++)
        {
             printf(" is %d\n",ran[x]);
        }
}

void full(void)
{
        int ran[] = {34,43,5,6,46,57,8,8,9,9,0};
        int x;
        putchar('******************************\n');
        printf("result is %d\n",sizeof ran);  // 数组占用了44 个字节 ，而不是数组中 有 44 个元素
        for(x = 0;x < sizeof ran / sizeof ran[0];x++)
        {
             printf(" is %d\n",ran[x]);
        }
}