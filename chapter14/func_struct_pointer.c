#include <stdio.h>
#include <string.h>
#define MAX_LEN 5
struct name{
    char first[MAX_LEN];
    char last[MAX_LEN];
    int letter;
};

void getInfo(struct name *);
void makeInfo(struct name *);
void showInfo(struct name *);
char * s_gets(char *,int);
void main(void)
{
    struct name joden;
    getInfo(&joden);
    makeInfo(&joden);
    showInfo(&joden);

}

void getInfo(struct name * pst)
{
    puts("please entry your first name");
    s_gets(pst->first,MAX_LEN);
    puts("please entry your last name");
    s_gets(pst->last,MAX_LEN);
}


void makeInfo(struct name * pst)
{
    pst->letter = strlen(pst->last) + strlen(pst->first);
}

void showInfo(struct name * pst)
{
    printf("%s : %s : %d \n",pst->first,pst->last,pst->letter);
}

char * s_gets(char * pt,int len)
{
    char * result_val;
    char * find;

    result_val = fgets(pt,len,stdin);

    // 如果读取输入成功
    if(result_val)
    {
         find = strchr(pt,'\n');

         if(find)
         {
            *find = '\0';
         }
         else
         {
            // 如果没有找到换行符 清空缓存区
            while( getchar() != '\n' ) continue;

         }
    }

    return result_val;

}

