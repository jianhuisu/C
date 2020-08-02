#ifndef _TREE_H
#define _TREE_H_

#include <stdbool.h>

#define SLEN 20
// 结点中的数据域
typedef struct item
{
    char name[SLEN];
} Item;

#define MAXITEMS 10

// 树中结点
typedef struct trnode
{
    Item item;             // 数据域
    struct trnode * left;  // 左指针域
    struct trnode * right; // 右指针域
} Trnode;

// 树
typedef struct tree
{
    Trnode * root;      // 指向根结点指针
    int size;           // 树中结点计数
} Tree;

/* 公共接口函数原型 */
void InitializeTree(Tree * ptree);
bool TreeIsEmpty(const Tree * ptree);
bool TreeIsFull(const Tree * ptree);
int TreeItemCount(const Tree * ptree);
bool AddItem(const Item * pi,Tree * ptree);
bool InTree(const Item * pi,const Tree * ptree);
bool DeleteItem(const Item * pi, Tree * ptree);
void Traverse(const Tree * ptree, void (* pfun)(Item item));
void DeleteAll(Tree * ptree);
void InOrder(const Trnode * root,void(*pfun)(Item item));
void PreOrder(const Trnode * root,void(*pfun)(Item item));
void PostOrder(const Trnode * root,void(*pfun)(Item item));
void LevelOrder(const Trnode * root,void(*pfun)(Item item));
int TreeDepth(const Trnode * root);

#endif