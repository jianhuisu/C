#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *str1, *token;
    char *saveptr1;
    int j;
    char name[] = "root:x::0:root:/root:/bin/bash:";

    for (j = 1, str1 = name; ; j++, str1 = NULL) {
        token = strtok_r(str1, ":", &saveptr1);
        if (token == NULL){
            break;
        }
        printf("%d: %s\n", j, token);
    }

    exit(EXIT_SUCCESS);
}
