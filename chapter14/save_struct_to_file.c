#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TITLE 20
#define MAX_AUTH 20

char * s_gets(char *,int n);

struct book{
    char title[MAX_TITLE];
    char auth[MAX_AUTH];
    float value;

};


void main(void)
{
    struct book libraries[3] = {
        {"daomubiji","nanpaisanshu",11},
        {"xiedu","yanyujiangnan",12},
        {"zhuxian","xiaoding",13},
    };

    FILE * pbooks;
    int size = sizeof(struct book);
    int i;

    if( (pbooks = fopen("books.dat","a")) == NULL)
    {
        puts("file open fail");
        exit(EXIT_FAILURE);
    }

    puts("success");
    fwrite(libraries,size,3,pbooks);

    rewind(pbooks);

    // 打开的文件流数据存储在缓存中 关闭文件流减轻缓存压力
    fclose(pbooks);

}



char * s_gets(char * pst,int n)
{
    char * result_val;
    char * find;

    result_val = fgets(pst,n,stdin);
    if( result_val )
    {
        find = strchr(pst,'\n');

        if(find)
        {
            *find = '\0';
        }
        else
        {
            while( getchar() != '\n')
            {
                continue;
            }
        }
    }

    return result_val;
}