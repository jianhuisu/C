#include <stdio.h>

int main(void)
{
    int a = 1;
    int * p = &a;
    int * p2;
    p2 = p+1;
    //*p++;
    printf("p2 : %p , p : %p",p2,p);
    return 0;
}
