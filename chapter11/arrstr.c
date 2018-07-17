#include <stdio.h>
#define MAX 40
#define LIM 5
main(void)
{
    const char *my[LIM] = {
        "my name is ",
        "my name is 1 ",
        "my name is  2",
        "my name is 3 ",
        "my name is  4",
    };

    int i;



    for(i = 0;i< LIM;i++)
    {
        printf("%s \n",my[i]);
    }

}