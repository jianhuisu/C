#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
void showQueueItem(Item item);

void main(void)
{
    int i;
    Item inputs[5] = {
        {"dao mu bi ji",1},
        {"piao miao shen",2},
        {"lan di mei chen",3},
        {"zhu xian",4},
        {"xie du",5}
    };

    // 一个包含队列 头尾配置的结构
    Queue pQueue;

    // 初始化队列  参数为 队列配置结构 指针
    InitializeQueue( &pQueue );

    // 判断队列是否为空
    if( QueueIsEmpty( &pQueue) )
    {
        printf("%s \n","queue is empty");
    }


    // 插入项
    for(i = 0 ;i < 5 ; i++)
    {

        if( QueueIsFull( &pQueue ) )
        {
            fprintf(stderr,"%s \n","队列已满");
            exit(1);
        }

        if( InsertQueueItem( inputs[i], &pQueue ) )
        {
            fprintf(stdout,"%20s insert success \n",inputs[i].title);
        }

    }

    printf("item total %d \n",pQueue.items);

    Traversal(&pQueue,showQueueItem);

    // 删除项
    DeleteQueueItem(&pQueue);

    printf("item total  %d \n",pQueue.items);

    Traversal(&pQueue,showQueueItem);

    // 清空队列
    EmptyTheQueue(&pQueue);

}

void showQueueItem(Item item)
{
   printf("title: %20s rating: %d \n",item.title,item.rating);
}