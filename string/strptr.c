#include <stdio.h>
int main(void)
{
    printf("%s %p %c \n","we","are",*"asdfa9fadfasdfad");
}
#if 0

字符串
定义

    使用双引号括起来的内容成为 字符串字面量(string literal) 或者 字符串常量(string constant)
    编译器编译时会在字符串末尾添加 \0 字符 作为字符串存储在内存中

    如果字符串常量之间没有间隔或者使用空格间隔 视为同一字符串
    char greeting[51] = "M" "y""is su";
    等价于 char greeting[51] = "My is su";

声明

    "" 双引号操作符实际返回的是 字符串数组的首字符地址

    printf("%s %p %c \n","we","are",*"asdfa9fadfasdfad");
    we 0x4005f3 a

    字符串常量属于 静态存储类别  存在于程序的整个声明周期
#endif

