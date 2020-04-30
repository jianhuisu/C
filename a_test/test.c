#include <stdio.h>

int main(void)
{
    enum coordinate_type { RECTANGULAR = 1, POLAR };
    int RECTANGULAR;
    printf("%d %d\n", RECTANGULAR, POLAR);
    return 0;
}
