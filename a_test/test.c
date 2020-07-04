#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef char  ElemType; //数据类型

//定义二叉树结构
typedef struct BiTreeNode
{
    ElemType  data; //数据域
    struct BiTreeNode *lChild;
    struct BiTreeNode *rChlid;
} BiTreeNode, *BiTree;

//先序创建二叉树
void CreateBiTree(BiTree *T)//要改变指针，所以要把指针的地址传进来
{
    ElemType ch;

    ch = getchar(); // 只能输入一个英文字符
    getchar();  // 去除输入缓冲中遗留的换行/回车

    if (ch == '#'){
        *T = NULL;
        return;
    } else if(ch == 'Q'){
        // abort input
        return;
    } else {

        *T = (BiTree)malloc(sizeof(BiTreeNode));

        //检查是否分配成功
        if (!(*T)){
            exit(-1);
        }
        
        (*T)->data = ch;
        CreateBiTree(&(*T)->lChild);//printf("输入%d的左孩子：", ch);
        CreateBiTree(&(*T)->rChlid);//printf("输入%d的右孩子：", ch);
    }
}

//先序遍历二叉树
void PreOrder(BiTree T)
{
    if (T == NULL)
        return ;
    printf("%c ", T->data);
    PreOrder(T->lChild);
    PreOrder(T->rChlid);
}

//中序遍历二叉树
void InOrderBiTree(BiTree T)
{
    if (T == NULL)
        return ;
    InOrderBiTree(T->lChild);
    printf("%c ", T->data);
    InOrderBiTree(T->rChlid);
}

//后序遍历二叉树
void PostOrderBiTree(BiTree T)
{
    if (T == NULL)
        return ;
    PostOrderBiTree(T->lChild);
    PostOrderBiTree(T->rChlid);
    printf("%c ", T->data);
}

//主函数
int main(void)
{
    BiTree T;

    printf("请输入先序遍历顺序下各个结点的值,#表示没有结点:\n");
    CreateBiTree(&T);
    printf("先序遍历二叉树:\n");
    PreOrder(T);
    printf("\n");
    printf("中序遍历二叉树:\n");
    InOrderBiTree(T);
    printf("\n");
    printf("后序遍历二叉树:\n");
    PostOrderBiTree(T);
    printf("\n");

    return 0;
}
