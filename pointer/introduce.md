第五章 指针


指针变量的声明

指针是一个值为内存地址的变量

间接运算符 * indirction operator  别名（解引用运算符  dereferencing operator）

    后接一个变量名 或者地址时  * 给出存储在指针指向地址上的值
    & 后接一个变量时 给出该变量的存储地址

乘法运算符   *

虽然他们符号相同 但是语法功能不相同

void main(void)
{
    int a = 2;

    // 声明一个 整型指针 类型变量
    int *b = &a;

    printf("%d\n",b);  // 打印指针变量 b 的存储的地址
    printf("%d\n",*b); // 打印指针变量 b 存储地址指向的值
}

[root@vagrant-centos65 chapter6]# t pointer.c
1365218292
2

#include <stdio.h>
void main(void)
{
    int a = 2;
    int c = 4;

    // 声明一个 整型指针 类型变量 变量
    int *b;

    // *b = c;  // 这种写法是错误的   Segmentation fault  访问不可访问的内存地址
    //   b = c;   //  assignment makes pointer from integer without a cast
    //   *b = &c;  //  assignment makes pointer from integer without a cast
     b = &c;  // 这种写法正确


    // *d 的右值为 b所存储地址指向的值 4
    // *d 的左值为 b所存储的地址值

    printf("%d\n",b);  // 打印指针变量 b 的存储的地址
    printf("%d\n",*b); // 打印指针变量 b 存储地址指向的值


    /*
        知识点：
         不能简单的通过检查数据的位来判断它的类型
    */
}


声明一个指针变量并不会自动分配任何内存
对指针进行间接访问之前 必须对指针变量进行初始化

NULL指针

指针运算


优先级等级口诀
圆方括号、箭头一句号， 自增自减非反负、针强地址长度，
乘除，加减，再移位，
小等大等、等等不等，
八位与，七位异，六位或，五与，四或，三疑，二赋，一真逗。
其中“，”号为一个等级分段。



