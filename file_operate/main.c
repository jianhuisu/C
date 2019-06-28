#include <stdio.h>
#include <stdlib.h>


int main(int argc,char * argv[])
{
    int ch;
    FILE *fp;
    unsigned long count = 0;

    if(argc < 2)
    {
        puts("can't get filename ");
        exit(EXIT_FAILURE);
    }

    if( (fp = fopen(argv[1],"w") ) == NULL )
    {
        printf("can't read file %s \n",argv[1]);
        exit(EXIT_FAILURE);
    }

    while( (ch = getc(fp) ) != EOF )
    {
        putc(ch,stdout);
        count++;
    }

    fclose(fp);
    printf("file %s total has %d character \n",argv[1],count);

    return 0;
}