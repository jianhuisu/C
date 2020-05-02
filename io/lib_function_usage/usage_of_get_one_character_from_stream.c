#include <stdio.h>

int main(int argc, char *argv[])
{

    printf("0x%x 0x%x 0x%x\n",-1,EOF,'0xff');

    int ch;
    char path[] = "/home/sujianhui/CLionProjects/C/a_test/example.txt";
    FILE * fd = fopen(path,"r");
    while( (ch = fgetc(fd)) != EOF ){
        printf("\n");
        fputc(ch,stdout);
    }

    return 0;
}

// man getchar(), fgetc() , getc()