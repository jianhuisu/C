第一章 快速上手

1 文件命名
    hello.h  存储函数原型 俗称 头文件 
    hello.c  存储实际源码

2 注释规则
    /* statement */
    注释不能嵌套

    注释块代码 采用逻辑注释方式
    #if 0
        statement
    #endif
3 预处理指令(preprocessor directive)
    预处理器处理 预处理指令

    #include
    #define

4 main() 函数

    每一个c程序都必须要有main函数,因为main函数是程序执行的起点

int 表示 main() 函数返回值类型
void 表示 main 函数不接受任何参数

int  main(void)
{
    printf("hello world\n");
    return 1;
}

5 编译、运行
    gcc main.c
    gcc -o ~/c.out main.c

