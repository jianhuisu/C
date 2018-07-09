#include <stdio.h>
void main(void)
{
        const int mon_day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        int index;

        for(index = 0;index < 12;index++)
        {
             printf("month %d has  %d  days \n",index+1,*(mon_day + index));
        }
}