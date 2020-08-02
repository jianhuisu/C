#include <stdio.h>
#include "tree.h"
static void ppp(Item item);


void FloorPrint(pTreeNode Tree)  //层序遍历
{
    pTreeNode temp[100];   //创建pTreeNode指针类型的指针数组
    int in = 0;
    int out = 0;

    temp[in++] = Tree;  //先保存二叉树根节点

    while (in > out)
    {
        if (temp[out])
        {
            cout << temp[out]->data << " → ";
            temp[in++] = temp[out]->leftPtr;
            temp[in++] = temp[out]->rightPtr;
        }
        out++;
    }
}


int main(void)
{
    printf("二叉树的遍历 \n");

    /*
                C
          A            E
      nil    B     D      nil

     */

    Item original_seq[] = {
            {"C"},
            {"A"},
            {"B"},
            {"E"},
            {"D"},
            {"F"},
    };

    int len = sizeof(original_seq) / sizeof(Item);
    Tree cbt;
    InitializeTree(&cbt);
    int i;

    for(i =  0;i < len;i++){
        AddItem(&original_seq[i],&cbt);
    }

    printf("二叉树共有 %d 个结点 \n",TreeItemCount(&cbt));
    printf("树的深度为 %d \n",TreeDepth(cbt.root));

    printf("先序遍历:");
    PreOrder(cbt.root,ppp);
    puts("");

    printf("中序遍历:");
    InOrder(cbt.root,ppp);
    puts("");

    printf("后序遍历:");
    PostOrder(cbt.root,ppp);
    puts("");



    DeleteAll(&cbt);
    return 0;
}

static void ppp(Item item)
{
    printf("%s ",item.name);
}
