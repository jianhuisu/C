#include <stdio.h>
#include <stdbool.h>
#ifndef LIST_H
#define LIST_H
#define TSIZE 40

// 定义 Item 类型
typedef struct film {
    char title[TSIZE];
    int rating;
}Item;

// 定义存储 Item 的链节 结构
// node 是结构的标记名
// Node 是结构的类型名
typedef struct node{
     Item item;
     struct node * next;
}Node;

// 定义指向链表开始处的指针 类型名
typedef Node * List;

void InitializeList(List * plist);
bool ListIsEmpty(const List * plist);
bool ListIsFull(const List * plist);
unsigned int ListItemCount(const List * plist);
bool AddItem(Item item,List * plist);
void Traverse(const List * plist,void(*pfun)(Item item));
void EmptyTheList(List * plist);


#endif

