#include <stdio.h>
#line 100 "cor.h"
#error not c11
void main(void)
{
    puts("hello");
}

#if 0
[root@vagrant-centos65 chapter16]# t line.c
cor.h:100:2: error: #error not c11
hello
#endif