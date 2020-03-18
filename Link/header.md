## 头文件的由来以及使用

main.c 

    #include <stdio.h>
    
    int a, b = 1;
    
    // 标注1
    extern void push(char);
    extern char pop(void);
    extern int is_empty(void);
    
    int main(void)
    {
        push('a');
        push('b');
        push('c');
    
        while(!is_empty())
        {
            putchar(pop());
        }
    
        putchar('\n');
        return 0;
    }
    
stack.c

    char stack[512];
    int top = -1;
    
    void push(char c)
    {
    	stack[++top] = c;
    }
    
    char pop(void)
    {
    	return stack[top--];
    }
    
    int is_empty(void)
    {
    	return top == -1;
    }
    
    
标注1：

我们可以把这三条声明理解为一个占位符号 ,在链接阶段 ,Linker Editor会补充占位符所代表地址 ,每一个相对独立的程序都要为引用的外部符号提前声明占位符号。
比如main.c中使用stack.c中的pop/push/is_empty函数,需要在main.c中提前声明,然后才可以使用

    extern void push(char);
    extern char pop(void);
    extern int is_empty(void);
    
实际开发中,使用这个模块(即使用stack.o目标文件中符号)的每个程序文件都要写三个函数声明，假设又有一个foo.c也使用这个模块，main.c和foo.c中各自要写三个函数声明。
这是很麻烦的,而且是重复的代码总是应该尽量避免的.**所以衍生出了头文件的概念**, 这样在main.c中只需`include`这个头文件就可以了，而不需要写三个函数声明.

### 为什么要包含.h文件而不是.c文件    

既然要#include头文件，那我不如直接在main.c中#include "stack.c"得了。这样把stack.c和main.c合并为同一个程序文件，
虽然这样也能编译通过，但是在一个规模较大的项目中不能这么做，假如又有一个foo.c也要使用stack.c这个模块怎么办呢？
如果在foo.c里面也#include "stack.c"，就相当于push、pop、is_empty这三个函数在main.c和foo.c中都有定义，那么main.c和foo.c就不能链接在一起了。
如果采用包含头文件的办法，那么这三个函数只在stack.c中定义了一次，最后可以把main.c、stack.c、foo.c链接在一起。

还有一个重要的问题,**头文件中的变量和函数声明一定不能是定义**。如果头文件中出现变量或函数定义，这个头文件又被多个.c文件包含，那么这些.c文件就不能链接在一起了。

### 头文件的引入顺序

    #include <stdio.h>   // 尖括号在标准目录中寻找    对于用角括号包含的头文件，gcc首先查找-I选项指定的目录，然后查找系统的头文件目录
    #include "stack.h"     // 双引号在自定义目录中寻找  gcc首先查找包含头文件的.c文件所在的目录，然后查找-I选项指定的目录，然后查找系统的头文件目录

假如三个代码文件都放在当前目录下：

    $ tree
    .
    |-- main.c
    |-- stack.c
    `-- stack.h
    
    0 directories, 3 files
    
则可以用`gcc -c main.c`编译，gcc会自动在main.c所在的目录中找到stack.h。假如把stack.h移到一个子目录下：

    $ tree
    .
    |-- main.c
    `-- stack
        |-- stack.c
        `-- stack.h
    
    1 directory, 3 files
    
则需要用`gcc -c main.c -Istack`编译。用-I选项告诉gcc头文件要到子目录stack里找。
如果把上面的代码改成`#include "stack/stack.h"`，那么编译时就不需要加-Istack选项了，
因为gcc会自动在main.c所在的目录中查找，而头文件相对于main.c所在目录的相对路径正是`stack/stack.h`。

### 多次引用同一个头文件会发生什么
    
 - 是使预处理的速度变慢了，要处理很多本来不需要处理的头文件。(使用 Header Guard避免 `#ifndef STACK_H和#endif`)
 - 是如果有foo.h包含bar.h，bar.h又包含foo.h的情况，预处理器就陷入死循环了（其实编译器都会规定一个包含层数的上限）。
 - 是头文件里有些代码不允许重复出现，虽然变量和函数允许多次声明（只要不是多次定义就行），但头文件里有些代码是不允许多次出现的，
   比如typedef类型定义和结构体Tag定义等，在一个程序文件中只允许出现一次。

### 参考资料 

宋劲杉 https://docs.huihoo.com/c/linux-c-programming/ch20s02.html