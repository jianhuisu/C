#include <stdio.h>
#include "tree.h"
static void ppp(Item item);

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

// 广度优先遍历二叉树，使用队列实现
void breadthFirstOrder(BinaryTreeNode* root)
{
    if(root==NULL) return;
    queue<BinaryTreeNode*> queue;
    queue.push(root);
    while(!queue.empty())
    {
        BinaryTreeNode* cur=queue.front();
        cout<<" "<<cur->m_key;//visit
        queue.pop();
        if(cur->m_pLeft!=NULL) queue.push(cur->m_pLeft);
        if(cur->m_pRight!=NULL) queue.push(cur->m_pRight);
    }
}
