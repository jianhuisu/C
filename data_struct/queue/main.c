//
//  main.c
//  data_structure
//
//  Created by 苏建辉 on 2019/6/26.
//  Copyright © 2019 sujianhui. All rights reserved.
//

#include <stdio.h>
#include "queue.h"

typedef void(* FP)(Item pbook);
void show(Item pbook);

int main(int argc, const char * argv[]) {
    
    Queue cronTask;
    Queue * pointerForCronTask = &cronTask;
    
    createQueue(&cronTask);
    
    if( queueIsEmpty( pointerForCronTask) )
    {
        printf("queue is empty \n");
    }else{
        printf("queue is not empty \n");
    }
    
    Item book  = {"dao mu bi ji",0};
    Item book1 = {"dao mu bi ji",1};
    Item book2 = {"dao mu bi ji",2};
    Item book3 = {"dao mu bi ji",3};
    
    insertQueueNode(book,pointerForCronTask);
    insertQueueNode(book1,pointerForCronTask);
    insertQueueNode(book2,pointerForCronTask);
    insertQueueNode(book3,pointerForCronTask);

    printf("insert success,now queue has %d elements \n",cronTask.items);
    FP pfun = show;
    
    printf("after traversal, queue has %d elements \n",cronTask.items);
    
    return 0;
}

void show(Item book){
    printf(" book name is : %s , and sub version is %d \n",book.title,book.rating);
}

