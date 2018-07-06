#include <stdio.h>
void interchange(int *,int *);
void change(int,int);
void main(void)
{
    int x = 5;
    int y = 10;
    printf("x value is %d and y value is %d\n",x,y);
    change(x,y);
    printf("x value is %d and y value is %d\n",x,y);
    interchange(&x,&y);
    printf("x value is %d and y value is %d\n",x,y);
}

void interchange(int *u,int *v)
{
    int temp;

    temp = *u;
    *u = *v;
    *v = temp;
}

void change(int u,int v)
{
        int temp;

        temp = u;
        u = v;
        v = temp;
}