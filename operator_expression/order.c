#include <stdio.h>
int func1(void);
int func2(void);

int main(void)
{
    int a;

    a = (func1()) + (func2());
    printf("%d\n",a);
    return 0;

}

int func1()
{
    printf("func1\n");
    return 1;
}

int func2()
{
    printf("func2\n");
    return 2;
}
