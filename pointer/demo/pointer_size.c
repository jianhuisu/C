#include <stdio.h>

// 指针的长度由谁决定

void main(void)
{
    int age = 5;
    char name[20] = "a";  // 20 = sizeof(name)/sizeof(char)
    int * pint = &age;
    char * pchar = name;

    printf("size of int pointer use %d bytes \n",sizeof(pint));
    printf("size of int age use %d bytes \n",sizeof(age));
    printf("int address show : %p \n",pint);
    printf("siez of char pointer use %d bytes  \n",sizeof(pchar));
    printf("siez of char array use %d bytes  \n",sizeof(name));
    printf("char address show :%p \n",pchar);

}

/*
 *
    [guangsujiqiang@su-ct7 data_struct]$>cat /proc/cpuinfo | grep "address sizes"
    address sizes   : 39 bits physical, 48 bits virtual

    [guangsujiqiang@su-ct7 data_struct]$>gcc pointer_size.c -o a.out && ./a.out
    size of int pointer use 8 bytes
    size of int age use 4 bytes
    int address show : 0x7ffcae1860ec
    siez of char pointer use 8 bytes
    siez of char array use 20 bytes
    char address show :0x7ffcae1860d0

    sizeof用来求一个对象(类型，变量，……)所占的内存大小(以字节为单位)

    12位16进制 等价于 48位二进制 , 即指针大小为 48bits
    所以：所以指针的大小由CPU的逻辑寻址总线宽度决定,并且所有数据的指针长度都是一致的,但是占用的内存空间可能不一致
 */
