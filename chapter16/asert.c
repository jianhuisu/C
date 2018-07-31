#include <stdio.h>
#include <math.h>
#include <assert.h>

void main(void)
{
    float x,y,z;
    while(scanf("%1f%1f",&x,&y) == 2 && (x != 0 || y != 0))
    {
        z = x*x - y*y;
        assert( z >= 0 );
        printf("answer is %f \n",sqrt(z));
    }

    puts("Done");


}