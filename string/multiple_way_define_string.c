//
// Created by guangsujiqiang on 3/3/20.
//
#include <stdio.h>

int main(int argc, char * argv[])
{
    char name1[20] = "ddddddddddddddd";

    char name2[20];
    *name2 = "sssssssssssssss";

    char * name3;
    name3 = "xxxxxxxxxxxxxxxx";

    printf(" %s \n",name1);
    printf(" %s \n",name2);
    printf(" %s \n",name3);


    return 0;

}

/*

第二种定义方式是错误的

[guangsujiqiang@su-ct7 C]$>gcc test.c && ./a.out
test.c: In function ‘main’:
test.c:17:12: warning: assignment makes integer from pointer without a cast [enabled by default]
 *name2 = "sssssssssssssss";
        ^
ddddddddddddddd
P
xxxxxxxxxxxxxxxx


 */