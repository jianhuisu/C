#include <stdio.h>
#include <string.h>
#define MAX_TITLE 40
#define MAX_AUTH 40
#define MAX_BOOK_NUM 40

char * s_gets(char *,int);
// 1 录入书籍信息
// 2 展示录入的信息

struct book
{
    char title[MAX_TITLE];
    char auth[MAX_TITLE];
    float price;
};

void main(void)
{
    struct book library[MAX_BOOK_NUM];
    int i = 1;

    printf("ready to entry you book\n");

    while(i < MAX_BOOK_NUM && s_gets(library[i].title,MAX_TITLE) != NULL && library[i].title[0] != '\0' )
    {
        printf("ready to entry you book\n");
        i++;
    }


    for(i ;i > 0 ;i--)
    {
        puts(library[i].title);
    }
}

char * s_gets(char * st,int n)
{
    char * ret_val;
    char * find;

    ret_val = fgets(st,n,stdin);

    if(ret_val)
    {
        find = strchr(st,'\n');
        *find = '\0';
    }
    else
    {
        // 清理 缓存中的输入行
        while(getchar() != '\n')
        {
            continue;
        }
    }
}