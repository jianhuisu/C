#include <stdio.h>

int main(void)
{
    int a = 0;

    if( a ) {
        printf("int a 被当做布尔真值");
    } else {
        printf("int a 被当做布尔假值");
    }
}