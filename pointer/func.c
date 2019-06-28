#include <stdio.h>
#define WIDTH 20
void starbar(void);

void main(void)
{
    starbar();
    printf("My Name Is sujianhui\n");
    starbar();
}

void starbar(void)
{
    int count;
    for(count = 1;count < WIDTH;count++)
    {
        putchar('*');
    }

    putchar('\n');
}