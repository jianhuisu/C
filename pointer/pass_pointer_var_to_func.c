#include <stdio.h>

void * swap(char *px,char *py)
{
    char temp;
    temp = *py;
    *py = *px;
    px = &temp;
    return px;
}

int main(int argc ,char **argv)
{
    char name1 = 'A';
    char name2 = 'B';
    char *pn = swap(&name1,&name2);

    printf(" %c , %c %c \n",name1,name2,*pn);
}