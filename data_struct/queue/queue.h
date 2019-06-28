//
//  queue.h
//  data_structure
//
//  Created by 苏建辉 on 2019/6/26.
//  Copyright © 2019 sujianhui. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdbool.h>

typedef struct item {
    char title[20];
    int rating;
}Item;

typedef struct node {
    Item item;
    struct node * next;
}Node;

typedef struct queue {
    Node * first;
    Node * last;
    int items;
}Queue;


void createQueue(Queue * pt);

bool queueIsFull(Queue * pt);

bool queueIsEmpty(Queue * pt);

int getQueueItemsCount(Queue * pt);

bool insertQueueNode(Item book,Queue * pt);

bool deleteQueueNode(Queue * pt);

bool resetQueue(Queue * pt);

void traversal(Queue * pt, void(*pfun)(Item item));

#endif /* queue_h */
