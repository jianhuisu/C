#include <stdio.h>

int main(void)
{
    char str[] = "my name is su jian hui";

    printf(" %s \n",str);

    int i,pre_char_is_space;
    int word=1;

    for(i = 0;(str[i] !='\0');i++){
        if( str[i] == ' ' ){
            word++;
        }
    }

    printf(" words count is : %d \n",word);
    return 0;
}