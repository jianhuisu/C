#include <stdio.h>
#include <string.h>
char * s_gets(char *,int);

struct book{
    char title[40];
    char auth[40];
    float price;
};


void main(void)
{
    struct book library;
    s_gets(library.title,20);

    puts(library.title);
}

// 从标准输入中读取参数 赋值给变量
char * s_gets(char * st,int len)
{
    char * ret_val;
    char * find;

    ret_val = fgets(st,len,stdin);

    if(ret_val)
    {
        find = strchr(st,'\n');
        if(find)
        {
            *find = '\0';
        }
        else
        {
            while(getchar() != '\n')
            {
                continue;
            }
        }
    }

   return ret_val;
}


