//
// Created by guangsujiqiang on 3/3/20.
//
#include <stdio.h>

int main(int argc, char * argv[])
{
    // method.1 correct
    char name1[20] = "ddddddddddddddd";

    // method.2 error
    char name2[20];
    *name2 = "sssssssssssssss";

    // method.3 correct
    char * name3;
    name3 = "xxxxxxxxxxxxxxxx";

    // method.4 correct
    char name4[20]={'a', 'b', 'c','\n'};

    printf(" %s \n",name1);
    printf(" %s \n",name2);
    printf(" %s \n",name3);
    printf(" %s \n",name4);

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