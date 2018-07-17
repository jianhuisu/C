#include <stdio.h>
#define LEN 5

void main(void)
{
    char words[LEN];
    int i;

    while(fgets(words,LEN,stdin) != NULL && words[0] != '\n')
    {

        i = 0;
        while(words[i] != '\n' && words[i] != '\0')
        {
            printf("%c     %d \n",words[i],i);
            i++;
        }

         if(words[i] == '\n') {
             words[i] == '\0';
         } else {
                while(getchar() != '\0')
                {
                    continue;
                }
         }

    }

    return;
}