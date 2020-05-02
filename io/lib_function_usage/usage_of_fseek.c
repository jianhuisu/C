#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ch;
    char path[] = "/home/sujianhui/CLionProjects/C/a_test/example.txt";
    FILE * fp = fopen(path,"r+");
    while( (ch = fgetc(fp)) != EOF ){
        printf("\n");
        fputc(ch,stdout);
    }

    if (fseek(fp, 10, SEEK_SET) != 0) {
        perror("Seek file textfile");
        exit(1);
    }

    fputc('K', fp);
    fclose(fp);
    return 0;
}
