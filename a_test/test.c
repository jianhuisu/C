#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int global = 0;       // 全局初始化区域
char * p1;            // 全局未初始化区域

int main(void)
{
    int a;               // 栈空间
    char s[] = "abcdefg";// 栈空间
    char * p2;           // 栈空间

    char *p3 = "1234567890";  // "1234567890" 在常量区 p3在栈上
    static int c = 0;         // 全局静态初始化区

    p1 = (char * )malloc(100 * sizeof(char));  // 申请的100字节 属于堆空间
    p2 = (char *)malloc(200 * sizeof(char));   // 申请 200字节属于堆空间

    strcpy(p1,"123456789");

    return 0;
}