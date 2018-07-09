#include <stdio.h>
void main(void)
{

    int a[4] = {1,2,3,4};

    printf("array is add is %p \n",a);

    int * next = a + 1;
    printf("array is add is %p \n",next);
    int i = 1;
    printf("array is add is %d \n",sizeof(i));

}

#if 0
[root@vagrant-centos65 chapter8]# t operating.c
array is add is 0x7fff7478d900
array is add is 0x7fff7478d904

两个地址 相差 一个 int  类型占据内存大小 4 字节
#endif