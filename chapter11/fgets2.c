#include <stdio.h>
#define LEN 5
void main(void)
{
    char str[LEN];

    while(fgets(str,LEN,stdin) != NULL && str[0] != '\n')
    {

        fputs(str,stdout);
        puts("---------------\n");
    }

    puts("Done.");
}