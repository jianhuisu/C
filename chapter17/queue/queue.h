#ifndef _QUEUE_H_  // 防止重复包含
#define _QUEUE_H_
#include <stdio.h>
#include <stdbool.h>
#define TLIZE 20
#define MAX_QUEUE_LEN 10

typedef struct item {
    char title[TLIZE];
    int rating;
}Item;

typedef struct node {
    Item item;
    struct node * next;
    // 此时 typedef Node 的简写还没有生效 不可以使用  Node * next 定义
}Node;

typedef struct queue {
    Node * first; // 指向队列首项的指针
    Node * last; // 指向队列末尾的指针
    int items; // 队列项计数
}Queue;

// 初始化队列
void InitializeQueue(Queue * pQueue);

// 判断队列是否为空
bool QueueIsEmpty(const Queue * pQueue);

// 判断队列是否已满
bool QueueIsFull(const Queue * pQueue);

// 统计队列项数
unsigned int QueueItemCount(const Queue * pQueue);

// 插入节点
bool InsertQueueItem(Item item,Queue * pQueue);

// 删除节点并返回
bool DeleteQueueItem(Queue * pQueue);

//清空队列
void EmptyTheQueue(Queue * pQueue);

//遍历队列
void Traversal(Queue * pQueue,void (*pfun)(Item item));

#endif