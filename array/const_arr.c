#include <stdio.h>
void del_con_a(const int ar[]);
void del_a(int ar[]);
void pri_arr(int *a);

void main(void)
{
    int arr[4] = {1,2,3,4};
    del_a(arr);
    pri_arr(arr);
    //del_con_a(arr);
}

void del_con_a(const int ar[])
{
    int index;
    for(index = 0 ; index < 4;index++ )
    {
        // 这种用法是不合法的
        printf("this pointer value is %d \n",++ar[index]);
    }
}

void del_a(int ar[])
{
    int index;
    for(index = 0 ; index < 4;index++ )
    {
        printf("this pointer value is %d \n",++ar[index]);
    }
}

void pri_arr(int *a)
{
    int * start = a;
    int * end = start + 4;

    while(start < end)
    {
        printf("this pointer value is %d \n",*start);
        start++;
    }
}

