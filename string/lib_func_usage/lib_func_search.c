#include <stdio.h>
#include <string.h>

int main(void)
{
    char name1[10] = "su";
    char name2[10] = "jianhuisu";
    char find_char = 's';

    if(strchr(name2,find_char)){
        printf("character in str\n");
    } else {
        printf("character not in str\n");
    }

    if(strrchr(name2,find_char)){
        printf("character in str\n");
    } else {
        printf("character not in str\n");
    }

    if(strstr(name2,name1)){
        printf("string founded\n");
    } else {
        printf("string not founded\n");
    }

    return 0;
}

/*
 *
    /home/sujianhui/CLionProjects/C/cmake-build-debug/test
    character in str
    character in str
    string founded

*/