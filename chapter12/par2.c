#include <stdio.h>
extern int count;

void accmulate(int);
static int total = 0;

void accmulate(int k)
{
    static int sub_total = 0;
    if(k <= 0)
    {
        printf("total cycle is %d \n",count);
        printf("total : %d,sub_total :%d \n",total,sub_total);
        sub_total = 0;
    }
    else
    {
        total += 1;
    }


}