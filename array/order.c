#include <stdio.h>
void main(void)
{
     // * 与 ++ 运算符混用优先级问题
    int a[2] = {100,200};
    int b[2] = {300,400};

    int *p1,*p2,*p3;

    p1 = p2 = a;
    p3 = b;

    printf("*p1 is %d ,*p2 is %d , *p3 is %d \n",*p1,*p2,*p3);
    printf("*p1 is %d ,*p2 is %d , *p3 is %d \n",*p1++,*++p2,(*p3)++);
    printf("*p1 is %d ,*p2 is %d , *p3 is %d \n",*p1,*p2,*p3);

}

#if 0
[root@vagrant-centos65 chapter8]# t order.c
*p1 is 100 ,*p2 is 100 , *p3 is 300
*p1 is 100 ,*p2 is 200 , *p3 is 300
*p1 is 200 ,*p2 is 200 , *p3 is 301

printf("*p1 is %d ,*p2 is %d , *p3 is %d \n",*p1++,*++p2,(*p3)++);

我们来解析一下这条语句

第一个打印参数
*p1++
根据结合律 从右向左开始计算 后缀++ 操作符先生效 , 后缀++ 操作的运算规则是 先用后加 ,在这里 先由 * 操作符进行指向操作、传递参数 最后再进行 累加操作
等价于

tmp = *p1
printf("*p1 is %d ,*p2 is %d , *p3 is %d \n",tmp,.....);
p1++

对于第二个参数
*++p2  从右向左结合 前缀++生效  对指针p2 先进行 加一单元操作 , 然后解引用 *(p2 + 1) ,最后传递到打印函数
p2 = p2 + 1
tmp = *p2
printf("",tmp)

#endif
