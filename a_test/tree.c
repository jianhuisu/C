#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

typedef struct pair {
    Trnode * parent;
    Trnode * child;
} Pair;

/* 局部函数原型 */
static Trnode * MakeNode(const Item * pi);
static bool ToLeft(const Item * i1,const Item * i2);
static bool ToRight(const Item * i1,const Item * i2);
static void AddNode(Trnode * new_node,Trnode * root);
static Pair SeekItem(const Item * pi,const Tree * ptree);
static void DeleteNode(Trnode ** ptr);
static void DeleteAllNodes(Trnode * root);

/*函数定义*/
/* 函数定义——公共函数实现*/
void InitializeTree(Tree * ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
}

// 对指针指向的内存单元操作是只读的
bool TreeIsEmpty(const Tree * ptree)
{
    if(ptree->root == NULL){
        return true;
    }else{
        return false;
    }
}

bool TreeIsFull(const Tree * ptree)
{
    if(ptree->size == MAXITEMS){
        return true;
    } else {
        return false;
    }
}

int TreeItemCount(const Tree * ptree)
{
    return ptree->size;
}

bool AddItem(const Item * pi,Tree * ptree)
{
    Trnode * new_node;

    // 树是否已满
    if(TreeIsFull(ptree)){
        fprintf(stderr,"Tree is full\n");
        return false;
    }

    // 二叉树中不允许存在重复的结点
    if(SeekItem(pi,ptree).child != NULL ){
        fprintf(stderr,"Attempted to add duplicate item \n");
        return false;
    }

    new_node = MakeNode(pi);
    if(new_node == NULL){
        fprintf(stderr,"Couldn't create node  \n");
        return false;
    }

    ptree->size++;

    if(ptree->root == NULL){
        ptree->root = new_node;
    } else {
        AddNode(new_node,ptree->root);
    }

    return true;

}

bool InTree(const Item * pi,const Tree * ptree)
{
    return (SeekItem(pi,ptree).child == NULL) ? false : true;
}

bool DeleteItem(const Item * pi,Tree * ptree)
{
    Pair look;
    look = SeekItem(pi,ptree);

    if(look.child == NULL){
        return false;
    }

    if(look.parent == NULL){
        DeleteNode(&ptree->root);
    } else if(look.parent->left == look.child){
        DeleteNode(&look.parent->left);
    } else {
        DeleteNode(&look.parent->right);
    }

    ptree->size--;

    return true;
}

void Traverse(const Tree * ptree,void(*pfun)(Item item))
{
    if(ptree != NULL ){
        InOrder(ptree->root,pfun);
        //PostOrder(ptree->root,pfun);
        //PreOrder(ptree->root,pfun);
    }
}

void DeleteAll(Tree * ptree)
{
    if(ptree != NULL ){
        DeleteAllNodes(ptree->root);
    }
    ptree->root = NULL;
    ptree->size = 0;
}

void InOrder(const Trnode * root,void(*pfun)(Item item))
{
    // 每一个结点都会被访问三次 最后一次访问的时候输出
    if(root != NULL ){
        if(root->left != NULL ){
            InOrder(root->left,pfun);
        }
        (*pfun)(root->item);
        if(root->right != NULL ){
            InOrder(root->right,pfun);
        }
    }
}

void PreOrder(const Trnode * root,void(*pfun)(Item item))
{
    // 该结点不为空,那么继续判断左右子树是否为空
    if(root != NULL ){
        // 第一次访问结点的时候 就要输出
        (*pfun)(root->item);
        if(root->left != NULL){
            PreOrder(root->left,pfun);
        }

        if(root->right != NULL ){
            PreOrder(root->right,pfun);
        }

    }
}

void PostOrder(const Trnode * root,void(*pfun)(Item item))
{
    // 每一个结点都会被访问三次 最后一次访问的时候输出
    if(root != NULL ){
        if(root->left != NULL){
            PostOrder(root->left,pfun);
        }
        if(root->right != NULL){
            PostOrder(root->right,pfun);
        }
        (*pfun)(root->item);
    }
}

void LevelOrder(const Trnode * root,void(*pfun)(Item item))
{
    Trnode temp[100];   //创建pTreeNode指针类型的指针数组
    int in = 0;
    int out = 0;

    temp[in++] = *root;  //先保存二叉树根节点

    while (in > out)
    {
        if (temp[out] != NULL)
        {
            temp[in++] = temp[out]->leftPtr;
            temp[in++] = temp[out]->rightPtr;
        }
        out++;
    }
}

/**
 * 我们可以从根结点即左右子树来理解二叉树的深度。对于任意一棵非空二叉树，有如下四种情况：
 * （1）如果一颗树只有一个结点，它的深度是 1；
 * （2）如果根结点只有左子树而没有右子树，那么二叉树的深度应该是其左子树的深度加 1；
 * （3）如果根结点只有右子树而没有左子树，那么二叉树的深度应该是其右树的深度加 1；
 * （4）如果根结点既有左子树又有右子树，那么二叉树的深度应该是其左右子树的深度较大值加 1。
 * @param root
 * @return
 */
int TreeDepth(const Trnode * root)
{
    if(root == NULL) {
        return 0;
    }

    int nLeft  = TreeDepth(root->left);
    int nRight = TreeDepth(root->right);
    return nLeft > nRight ? nLeft+1: nRight+1 ;

}

/* 函数定义——局部函数实现*/
static void DeleteAllNodes(Trnode * root)
{
    Trnode * pright;
    if(root != NULL ){
        pright = root->right;
        DeleteAllNodes(root->left);
        free(root);
        DeleteAllNodes(pright);
    }

}

static void AddNode(Trnode * new_node , Trnode * root)
{
    if(ToLeft(&new_node->item,&root->item)){
        if(root->left == NULL ){
            root->left = new_node;
        } else {
            AddNode(new_node,root->left);
        }

    } else if( ToRight(&new_node->item,&root->item)){
        if(root->right == NULL ){
            root->right = new_node;
        } else {
            AddNode(new_node,root->right);
        }
    } else {
        fprintf(stderr,"location error in AddNode(), maybe duplicate item \n");
        exit(1);
    }

}

// 因为item不是数字 且要实现双重比较 需要自己定义比较函数
static bool ToLeft(const Item * i1,const Item * i2)
{
    int comp1;
    if( (comp1 = strcmp(i1->name,i2->name)) < 0){
        return true;
    } else {
        return false;
    }
}

// 因为item不是数字 需要自己定义比较函数
static bool ToRight(const Item * i1,const Item * i2)
{
    int comp1;
    if( (comp1 = strcmp(i1->name,i2->name)) > 0){
        return true;
    } else {
        return false;
    }
}

static Trnode * MakeNode(const Item * pi)
{
    Trnode * new_node;
    // 从堆中申请空间 不会撑爆栈空间
    new_node = (Trnode *) malloc(sizeof(Trnode));
    if(new_node != NULL){
        new_node->item = *pi;
        new_node->left = NULL;
        new_node->right = NULL;
    }

    // todo 如果这里是嵌套结构变量 还可以直接返回吗 
    return new_node;
}

// 按中序遍历在树中查找item
static Pair SeekItem(const Item * pi,const Tree * ptree)
{
    Pair look;

    // 从根结点开始
    look.parent = NULL;
    look.child = ptree->root;

    if(look.child == NULL){
        return look;
    }

    while(look.child != NULL ){
        if(ToLeft(pi,&(look.child->item))){
            look.parent = look.child;
            look.child = look.child->left;
        } else if(ToRight(pi, &(look.child->item))){
            look.parent = look.child;
            look.child = look.child->right;
        }else{
            break;
        }
    }

    return look;
}

static void DeleteNode(Trnode **ptr)
{
    Trnode * temp;

    // 子结点的右子树 必定还是父结点的右子树
    if( (*ptr)->left == NULL ){
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    } else if( (*ptr)->right == NULL ){
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    } else {
        // 被删除的结点有两个子结点
        // 找到重新连接右子树的位置

        for(temp = (*ptr)->left;temp->right != NULL;temp = temp->right){
            // 优先查看结点的右子树是否为空，如果不为空，继续向下先序遍历.
        }
        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }

}


