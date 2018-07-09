#include <stdio.h>
#define SIZE 10
void foo1(int *,int);
void foo2(int *,int *);

void main(void)
{
    int rain[SIZE] = {1,2,3,4,5,6,7,8,9,0};
    foo1(rain,SIZE);
    printf("------------------------------");
    foo2(rain,rain + SIZE);
}

foo1(int * ar,int n)
{
    int index;
    for(index = 0;index < n;index++)
    {
        printf("value is %d \n",ar[index]);
    }
}

foo2(int * start,int * end)
{

    int total = 0;
    // 注意 这里 end 指针指向的是数组最后元素的下一个位置
    while(start < end)
    {
        printf("value is %d \n",*start);
        total += *start;
        start++;

    }

    printf("--------value is %d \n",total);
}