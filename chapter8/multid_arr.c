#include <stdio.h>

void main(void)
{
    int arr[5][4] = {
        {1,1,1,1},
        {2,2,2,2},
        {3,3,3,3},
        {4,4,4,4},
        {5,5,5,5},
    };

    printf("pointer is %p \n",arr);
    printf("pointer is %p \n",&arr[0]);
    printf("pointer is %p \n",&arr[0][0]);

    printf("pointer is %d \n",sizeof(arr));
    printf("pointer is %d \n",sizeof(arr[0]));
    printf("pointer is %d \n",sizeof(arr[0][0]));

}