// 存储结构：二叉链表/三叉链表 （这里的叉指 结点结构中包含了几个指针域）
// 逻辑结构：二叉树（普通二叉树/完全二叉树/满二叉树）

// 在具体的应用中采用什么存储结构(什么样的 struct 构成) 取决于你要做什么操作.




#include <stdio.h>

typedef int Status;

// 真实存储结点值的
typedef struct  node_value{
    int age;
}Node;

typedef  struct tree_node{
    Node data;    // 二叉树结点的数据域
    Node * left;  // 二叉树结点的左指针域
    Node * right; // 二叉树结点的右指针域
}TreeNode;

typedef struct binary_tree{
   TreeNode root;
   int count;
}T;

// 二叉树的操作
// 构建一棵二叉树
// 销毁一棵二叉树
// 清空一个二叉树
// 判断二叉树是否为空

// 先序遍历二叉树
// 中序遍历二叉树
// 后序遍历二叉树
// 层序遍历二叉树

// 插入一个结点：感觉在叶子结点上进行插入操作还比较好 在非叶子结点上进行替换操作比较卡靠谱
// 删除一个结点

// 获取二叉树的高度/深度
// 获取二叉树的结点个数

// 在二叉树中查找一个结点
// 返回一个结点的双亲


int main(void)
{
    TreeNode adc = {18,NULL,NULL};
    printf("node value %d %p %p \n",adc.data.age,adc.left,adc.right);
    return 0;
}

