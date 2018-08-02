#创建一个List
#创建一个Item
#
#初始化链表
#判断链表是否已满
#    未满 添加item
#展示

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
char * s_gets(char * pst,int n);

void main(void)
{

    // 声明指向链表头元素的指针变量
    List movies;
    Item tmp;

    Initialize(&movies);

    if(ListIsFull(&movies))
    {
        printf("链表已满 \n");
        exit(EXIT_FAILURE);
    }

    puts("Enter first movie title")
    if(s_gets(tmp.title,TSIZE) != ) ;

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