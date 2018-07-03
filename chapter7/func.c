#include <stdio.h>

void main(void)
{
    int key = 9;
    int array[10] = {1,2,3,4,9,5,6,8};
    int *p;
    p = find_int(key,array,sizeof(array));

    printf("special key addr is %d\n",p);

}

int *
find_int(int key , int array[],int array_len)
{
    int i;

    for(i = 0;i < array_len;i++)
    {
        // 检查这个位置的值 是否为需要查找的值
        if(array[i] == key)
        {
            return &array[i];
        }
    }

    return NULL;
}