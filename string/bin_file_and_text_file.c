//
// @author guangsu
// differ the difference between binary file and text file
// could found some difference below winOS

#include <stdio.h>

int show(char * file_name)
{
    FILE *fp;
    int c;

    fp = fopen(file_name,"r");
    while(1)
    {
        c = fgetc(fp);
        if( feof(fp) )
        {
            break ;
        }
        printf(" --> %c -->Hex: 0x%x \n", c);
    }

    fclose(fp);
    return(0);
}

void main(void)
{
    FILE *pfile1 = NULL;
    FILE *pfile2 = NULL;
    char file_name1[15] = "myfile.bin";
    char file_name2[15] = "myfile.txt";
    char ch = 0x7d;
    // CWD current work directory
    printf("character: %c dec: %d Hex: 0x%x Oct: %o \n",ch,ch,ch,ch);

    pfile1 = fopen(file_name1, "wb");
    pfile2 = fopen(file_name2, "w");

    size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    size_t wcount1 = fwrite(&ch, sizeof(char), 1, pfile1);
    size_t wcount2 = fwrite(&ch, sizeof(char), 1, pfile2);

    fclose(pfile1);
    fclose(pfile2);

    show(file_name1);
    show(file_name2);
    //return 0;

}

