#include <stdio.h>
int count = 0;
void report_count(int);


void main(void)
{
    int value;
    register i;

    while(scanf("%d",&value) == 1 && value > 0 )
    {
        printf("this is %d\n",value);
        count++;
        for(i = value;i>= 0 ;i--)
        {
            accmulate(i);
        }
    }

}

void report_count(int i)
{
    printf("loop executed %d times \n",i);
}