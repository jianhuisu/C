第十二章 存储类别、链接和内存管理

作用域

    块作用域  block scope

        if  while for

    函数作用域 function scope

    函数原型作用域 function prototype scope

    文件作用域 file scope

链接类型
    内部链接
        文件作用域（单个翻译单元使用)

    外部链接
        文件作用域（多文件程序中使用）

    无链接
        块作用域
        函数作用域
        函数原型作用域

    如何区别内部链接、外部链接 根据 static 关键字

    #include <stdio.h>
    int age = 18
    static sex = 1

    age 外部链接
    sex 内部链接

存储期
    自动存储期   局部变量所使用的存储方式
    静态存储期
    动态分配存储期  （使用 内存分配函数   malloc() calloc() 申请、free() 释放 手动控制）
    线程存储期



5种存储类别

    自动存储
    寄存器
    静态、无连接
    静态、内部链接
    静态、外部链接


类型限定符
    _Atomic 原子
    restrict
    volatile
    const      限定指针时 可以限定指针指向值不允许改变或者指针本身不允许改变、由 const 所在位置决定
存储类别说明符
    static     声明为内部变量
    external   声明使用外部变量
    register   请求存储在寄存器中

内存管理模型














