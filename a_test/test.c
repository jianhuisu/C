#include <stdio.h>

int main(void)
{
    printf("int: %d , char : %d \n",sizeof(int),sizeof(char));

    int a = 1;
    int * pi = &a;

    char  b = 'A';
    char * pc = &b;

    // 指针+1 操作 实质为 当前指针地址 + 1 * （指针类型所占字节数）
    printf("int origin value is %p , char origin value is %p \n",pi,pc);
    printf("int after+ value is %p , char after+ value is %p \n",++pi,++pc);
}
