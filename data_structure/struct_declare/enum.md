## enum

### 枚举类型的优势

提高程序的可读性.可维护性.比如我们经常会使用int数字来代表各种色值:
    
    red       1
    yellow    2 
    blue      3 
    black     4
    white     5
    ...
    
那么下面两种代码的可读性的优劣便非常明显.
    
    // 代码段 1 
    int color_from_input;
    scanf("%d",&color_from_input);
    
    if( color_from_input == 1){
        printf("you choose red color ");
    } else if(color_from_input == 2) {
        ...
    }
    
    // 代码段 2
    int color_from_input;
    scanf("%d",&color_from_input);
    
    if( color_from_input == red){
        printf("you choose red color ");
    } else if(color_from_input == yellow) {
        ...
    }

枚举类型在`case`语句中使用非常方便

### 命名空间问题 
    
虽然`结构体的成员名`和当前域内`变量名`不在同一命名空间中，但`枚举的成员名`却和当前域内`变量名`在同一命名空间中，所以会出现命名冲突.
例如这样是不合法的(同一命名空间中符号表冲突)：

    int main(void)
    {
        enum coordinate_type { RECTANGULAR = 1, POLAR };
        int RECTANGULAR;
        printf("%d %d\n", RECTANGULAR, POLAR);
        return 0;
    }

下面的则无冲突(这是因为全局变量 与 局部变量不在一个命名空间中)

    #include <stdio.h>

    enum coordinate_type { RECTANGULAR = 1, POLAR };

    int main(void)
    {
        int RECTANGULAR;
        printf("%d %d\n", RECTANGULAR, POLAR);
        return 0;
    }

那么用`#define`定义的常量和枚举常量有什么区别呢？

 - define不仅用于定义常量，也可以定义更复杂的语法结构，称为宏（Macro）定义。
 - define定义是在预处理阶段处理的，而枚举是在编译阶段处理的。




    
    