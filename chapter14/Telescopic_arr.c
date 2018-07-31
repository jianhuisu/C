#include <stdio.h>
#include <stdlib.h>

struct book{
    char size_t;
    double count;
    double hobby[];
};

void main(void)
{
    struct book * pst;
    pst = malloc(sizeof(struct book) +  5 * sizeof(double) );
    pst->count = 12.99;
    int i;
    printf("%f \n",pst->count);

    for(i = 0;i < 5;i++)
    {
        pst->hobby[i] = i;
    }

    for(i = 0;i < 5;i++)
    {
        printf("%f \n",pst->hobby[i]);
    }

    free(pst);

}