#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main(int argc,char * argv[])
{

    FILE *ifp;
    FILE *ofp;
    char ch;
    char name[10];
    int count = 0;

    if(argc < 2)
    {
        printf("is not set filename\n");
        exit(EXIT_FAILURE);
    }

    if( ( ifp = fopen(argv[1],"r") ) == NULL )
    {
        printf("can't read file %s\n",argv[1]);
        exit(EXIT_FAILURE);
    }

    ofp = fopen("new.txt","w");

    while( ( ch = getc(ifp) ) != EOF )
    {

        if(count%3 == 0)
        {
            putc(ch,ofp);
        }

        count++;

    }


    fclose(ifp);
    fclose(ofp);
    return;
}