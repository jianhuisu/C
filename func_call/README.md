##

### 要点

 - 除了整数类型外,所有形参都以指针形式传递
 

### 为什么需要函数原型

todo  
https://docs.huihoo.com/c/linux-c-programming/ch20s02.html

在上一节我们把两个程序文件放在一起编译链接，main.c用到的函数push、pop和is_empty由stack.c提供，其实有一点小问题，我们用-Wall选项编译main.c可以看到：

    $ gcc -c main.c -Wall
    main.c: In function ‘main’:
    main.c:8: warning: implicit declaration of function ‘push’
    main.c:12: warning: implicit declaration of function ‘is_empty’
    main.c:13: warning: implicit declaration of function ‘pop’
    
这个问题我们在第 2 节 “自定义函数”讨论过，由于编译器在处理函数调用代码时没有找到函数原型，只好根据函数调用代码做隐式声明，把这三个函数声明为：
(没有函数原型 编译器自行隐式声明了函数原型 隐式声明是从函数调用代码推导而来的 不够精准 规定返回值都是int型的)

    int push(char);
    int pop(void);
    int is_empty(void);
    
    
    
#### for


    for(i=0;;i++){
        if(a == NULL){
            break;
        }
    }
    
`;;` 表示一直为真，直到依靠`break`跳出循环.