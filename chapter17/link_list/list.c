#include <stdio.h>
#include <stdlib.h>
#include "list.h"  // list.h 只需要在主函数中包含过一次即可

// 局部用函数 并非供外部使用接口
static void CopyToNode(Item item,Node * pnew);

void InitializeList(List * plist)
{
    *plist = NULL;
}

bool ListIsEmpty(const List * plist)
{
    if(*plist == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ListIsFull(const List * plist)
{
    Node * pt ;
    bool full;

    // 以不能分配一个Node结构空间来判断 链表是否已满
    pt = (Node *)malloc(sizeof(Node));
    if(pt == NULL)
    {
        full = true;
    }
    else
    {
        full = false;
    }

    free(pt);

    return full;
}

unsigned int ListItemCount(const List * plist)
{
    unsigned int count = 0;
    Node * beginPt = *plist;

    while(beginPt != NULL)
    {
        count++;
        beginPt = beginPt->next ;
    }

    return count;
}

/* 传递指针 可以直接操作原始数据 将赋值操作等细节隐藏在接口中 如果传递变量副本 需要在主调函数处处理返回值 违背了接口设计原则 暴露了实现细节 */
bool AddItem(Item item,List * plist)
{
    /* List 是 Node 类型的指针 , plist 为 List 类型的指针  即 plist 的值为 (指向 Node 指针变量) 的地址 */
    Node * NewP;
    Node * TempP = *plist;

    NewP = (Node *) malloc(sizeof(Node));
    
    // 分配内存失败
    if(NewP == NULL)
    {
        return false;
    }

    CopyToNode(item,NewP);
    NewP->next = NULL;

    // 如果是空链表  那么将头指针的值设为NewP
    if(TempP == NULL)
    {
        *plist = NewP;
    }
    // 如果不是空链表 需要找到链表的末尾 将 NewP 添加到末尾
    else
    {
        while(TempP->next != NULL)
        {
            TempP = TempP->next;
        }

        TempP->next = NewP;
    }

    return true;
}

void Traverse(const List * plist,void(*pfun)(Item item))
{
    Node * EvItem;
    EvItem = *plist;

    while(EvItem != NULL)
    {
        (*pfun)(EvItem->item);  // 调用回调函数
        EvItem = EvItem->next;  // 切换到下一项
    }

}

void EmptyTheList(List * plist)
{
    Node * pn;

    while(*plist != NULL)
    {
        pn = (*plist)->next;
        free(*plist);
        *plist = pn;
    }

}

static void CopyToNode(Item item,Node * pnew)
{
    /* 结构类型数据 允许将一个结构赋值给另外一个结构 , 数组则不可以 采用结构赋值还有另外一种好处 Item 结构需要修改时 copy函数不需要修改 */
    // 拷贝结构
    pnew->item = item;

//    pnew->item->title = item.title;
//    pnew->item->rating = item.rating;

}

