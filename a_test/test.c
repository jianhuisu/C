#include <stdio.h>

int main(void)
{
    char name[4][5] = {
            {'a','b','c','d','e'},
            {'a','b','c','d','e'},
            {'a','b','c','d','e'},
            {'a','b','f','d','e'},
    };

    int i;
    for(i = 0;i< 4 * 5;i++)
    {
        printf("name[%d][%d] => %c ",i/5,i%5,name[i/5][i%5]);
        if( (i + 1) % 5  == 0 ){
            printf("\n");
        }
    }

    return 0;
}