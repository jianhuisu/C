#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"

// 初始化队列
void InitializeQueue( Queue * pQueue )
{
    //pQueue = NULL;
    pQueue->first = NULL;
    pQueue->last = NULL;
    pQueue->items = 0;

}

// 判断队列是否为空
bool QueueIsEmpty(const Queue * pQueue)
{
    // return pQueue->items == 0 ? true : false ;
    return pQueue->items == 0 ;
}

// 判断队列是否已满
bool QueueIsFull(const Queue * pQueue)
{
    return pQueue->items == MAX_QUEUE_LEN ;
}

// 统计队列项数
unsigned int QueueItemCount(const Queue * pQueue)
{
    return pQueue->items;
}

// 插入节点
/*

    1 创建新节点
    2 copy新节点
    3 设置当前节点next 值 ，新节点 next 值
    4 设置 last
    5 统计项 + 1
    6 处理特殊情况

*/
bool InsertQueueItem(Item item,Queue * pQueue)
{

//    判断是否已满 单独成为函数 解耦合
//    if(QueueIsFull(pQueue))
//    {
//        // 队列已满
//        return false;
//    }

    // question Node * pNew = (Node *) malloc(sizeof(struct Node));
    Node * pNew = (Node *) malloc(sizeof(Node));

    if(pNew == NULL)
    {
        printf("unable to allocate memory");
        exit(1);
    }


    // copy 新节点
    pNew->item = item;
    pNew->next = NULL;

    // 方法 1 首元素
//    if(QueueIsEmpty( pQueue ))
//    {
//        pQueue->first = pNew;
//        pQueue->last = pNew;
//    }

// pQueue->last->next = pNew;

    // 方法 2 与 方法 1 作用相同 但是比第一种好
    if(QueueIsEmpty( pQueue ))
    {
        pQueue->first = pNew;
    }
    else
    {
        pQueue->last->next = pNew;
    }


    pQueue->last = pNew;

    // 计数器
    pQueue->items++;  // question ++ -> 优先级

    return true;

}

// 删除节点并返回
/*
    1 计数器 - 1
    2 删除首元素
    3 重置 first
*/
bool DeleteQueueItem(Queue * pQueue)
{

    Node * OldFirst;

    // 首元素
    if(QueueIsEmpty(pQueue))
    {
        return false;
//         printf("queue is empty \n");
//         exit(1);
    }

    OldFirst = pQueue->first;
    pQueue->first = pQueue->first->next;

    // 原首元素
    free(OldFirst);

    pQueue->items--;
    if(pQueue->items == 0)
    {
        pQueue->last = NULL;

    }

    return true;
}

//清空队列
void EmptyTheQueue(Queue * pQueue)
{
    Item ti;
    while(QueueIsEmpty(pQueue))
    {
       DeleteQueueItem(pQueue);
    }

}

// question 遍历队列  本方法有错误 等待解答
void Traversal(Queue * pQueue,void (*pfun)(Item item))
{
    Node * tp = pQueue->first;

    int count = 0;

    while(count < pQueue->items )
    {

        (*pfun)(tp->item);
        tp = tp->next;

        count++;
    }


}
