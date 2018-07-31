#include <stdio.h>
void befor_exit(void);

void main(void)
{
    atexit(befor_exit);  // 注册退出时调用函数 先注册的后调用 最多注册32个
    puts("hello world");
}

void befor_exit(void)
{
    puts(__FILE__);
}