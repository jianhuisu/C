#include <stdio.h>

void main(void)
{
    int i = 0;
    while(i < 100)
    {
        printf("%d \n",i);
        if(i == 10)
        {
            puts("break here");
            break;
        }
        i++;
    }
}