//
// Created by 苏建辉 on 2020/1/11.
//
#include <stdio.h>

int main(int argc,char * argv[]) {
    struct compound_struct {
        char name[10];
        char title[10];
    };

    struct compound_struct z1 = {"sujianhui"};

    printf(" %s  : %s \n",z1.name,z1.title);
    return 0;
}

/*

 [sujianhui@ struct_declare]$>gcc memberwise_initializer.c -Wall && ./a.out
  sujianhui  :

  未显式初始化的空间被默认初始化为 0 值
*/