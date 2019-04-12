#include <stdio.h>

void main(void)
{
    int arr_int[] = {1,2,3,4,5};
    size_t sz;
    sz = sizeof(arr_int);

    printf("size of array arr_int is %d bytes \n",sz);
    printf("array variable name is a pointer variables,it's point address is %p\n",arr_int);
    printf("%d\n",*arr_int);

    // 这两种用法非法
    // int** a;
    // int (*a)[4]

    // int *p[]和int (*p)[]
    // 前者是指针数组，后者是指向数组的指针。更详细地说。
    printf("%p\n",a);

}