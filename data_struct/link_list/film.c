#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

char * s_gets(char * pst,int n);
void showMovies(Item item);
void main(void)
{

    // 声明指向链表头元素的指针变量
    List movies;
    Item tmp;

    InitializeList(&movies);

    if(ListIsFull(&movies))
    {
        printf("list is full \n");
        exit(EXIT_FAILURE);
    }

    puts("Enter first movie title");

    while(s_gets(tmp.title,TSIZE) != NULL && tmp.title[0] != '\0')
    {
        puts("Enter your rating <1-10>");

        scanf("%d",&tmp.rating);  // 读取第一个输入项

        // 清空缓存 对于 sex girl  这个字符串 scanf 只会读取 sex 空格+girl 依然会留在输入缓存中
        while(getchar() != '\n')
        {
            continue;
        }

        if(AddItem(tmp,&movies) == false)
        {
            fprintf(stderr,"problem allocating memory!\n");
            break;
        }

        if(ListIsFull(&movies))
        {
            fprintf(stderr,"%s","链表已满 \n");
            break;
        }

        puts("enter next movie title");

    }

    // 数据录入完毕后 显示链表数据
    if(ListIsEmpty(&movies))
    {
        // 输出显示字符串
        puts("no data input");
    }
    else
    {
        puts("here is the list");
        Traverse(&movies,showMovies);
    }

    // show movies count
    printf("total input %d movies \n",ListItemCount(&movies));

    // clear list
    EmptyTheList(&movies);


}

void showMovies(Item item)
{
    printf("movie title is  %s; movie rating is  %d \n",item.title,item.rating);
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