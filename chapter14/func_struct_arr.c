#include <stdio.h>
#include <string.h>
#define MAX_LEN 5
struct name{
    char first[MAX_LEN];
    char last[MAX_LEN];
    int letter;
};

struct name getInfo(void);
struct name makeInfo(struct name);
void showInfo(struct name);
char * s_gets(char *,int);

void main(void)
{
    struct name joden;
    joden = getInfo();
    joden = makeInfo(joden);
    showInfo(joden);

}

struct name getInfo(void)
{
    struct name tmp;
    puts("please entry your first name");
    s_gets(tmp.first,MAX_LEN);
    puts("please entry your last name");
    s_gets(tmp.last,MAX_LEN);

    // 返回一个结构到 主调函数 , 结构可以用另一个结构来赋值 但是数组不可以
    return tmp;
}


struct name makeInfo(struct name tmp)
{
   tmp.letter = strlen(tmp.first) + strlen(tmp.last);
   return tmp;
}

void showInfo(struct name tmp)
{
    printf("%s : %s : %d \n",tmp.first,tmp.last,tmp.letter);
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

