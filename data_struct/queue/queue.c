//
//  queue.c
//  data_structure
//
//  Created by 苏建辉 on 2019/6/26.
//  Copyright © 2019 sujianhui. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

void createQueue(Queue *pt)
{
    pt->first = NULL;
    pt->last  = NULL;
    pt->items = 0;
}

bool queueIsEmpty(Queue * pt)
{
    return pt->items == 0 ? true : false ;
}

bool queueIsFull(Queue * pt)
{
    return pt->items >= 20 ? true : false ;
}

/*
    only insert in queue tail
 */
bool insertQueueNode(Item book,Queue * pt)
{
    // first try to apply memory from HEAP space
    Node * pointForNewNode = (Node *) malloc(sizeof(Node));
    
    // there is no free space in HEAP space
    if( !pointForNewNode ){
        return false;
    }
    
    pointForNewNode->item = book;
    pointForNewNode->next = NULL;
    
    // register node address to queue
    if( queueIsEmpty(pt) ){
        pt->first = pointForNewNode;
        pt->last  = pointForNewNode;
    }else{
        pt->last->next = pointForNewNode;
        pt->last = pointForNewNode;
        
    }
    
    pt->items++;
    
    printf("%p \n",pointForNewNode);
    return true;
    
}

/*
    only delete node in the tail of queue
*/
bool deleteQueueNode(Queue *pt){
    
    if( queueIsEmpty(pt) ){
        return false;
    }
    
    Node * pNode = pt->first;
    pt->first = pNode->next;
    
    free(pNode);
    pt->items--;
    
    return true;
    
}

int getQueueItemCounts(Queue * pt)
{
    return pt->items;
}

bool resetQueue(Queue * pt){
    
    Node * tmpAddress = NULL;
    
    while( pt->first ){
        
        tmpAddress = pt->first;
        pt->first = pt->first->next;
        free(tmpAddress);
    }
    
    pt->items = 0;
    
    return true;
}

void traversal(Queue * pt,void (* pfun)(Item book)){
    
    Node * tmpBook = pt->first;
    int count = 0;

    while(count < pt->items )
    {
        //printf(" %s \n",tmpBook->item.title);
        (* pfun)(tmpBook->item);
        tmpBook = tmpBook->next;
        count++;
    }

}
