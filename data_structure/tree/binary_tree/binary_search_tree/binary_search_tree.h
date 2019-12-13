//
// Created by guangsujiqiang on 12/12/19.
//

#ifndef C_BINARY_SEARCH_TREE_H
#define C_BINARY_SEARCH_TREE_H

typedef struct DT{
    char name[50];
    float price;
}dDT;

typedef struct Node{

    dDT data_item;
    struct Node * left;
    struct Node * right;

}dNode;

struct BSTree{
    dNode * root;
}

initBSTree();

#endif //C_BINARY_SEARCH_TREE_H
