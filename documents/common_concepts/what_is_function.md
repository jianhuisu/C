()  函数调用符
printf 函数名
" %d \n",1 Arguments 函数参数

printf(" %d \n",1);  这是一个函数调用表达式语句

    printf也是一个函数，上例中的printf("sin(pi/2)=%f\nln1=%f\n", sin(pi/2), log(1.0))是带三个参数的函数调用，而函数调用也是一种表达式，
    因此printf语句也是表达式语句的一种。但是printf感觉不像一个数学函数，为什么呢？
    因为像log这种函数，我们传进去一个参数会得到一个返回值，我们调用log函数就是为了得到它的返回值，至于printf，
    我们并不关心它的返回值（事实上它也有返回值，表示实际打印的字符数），我们调用printf不是为了得到它的返回值，
    而是为了利用它所产生的副作用（Side Effect）－－打印。
    函数的正作用是获取返回函数计算的结果。

C语言的函数可以有Side Effect，这一点是它和数学函数在概念上的根本区别。

函数的两大属性

    类型
    返回值

    foo();              可以通过编译，但是不推荐。该写法等价于 int foo(void); 如果没有显式指定函数返回值的类型，那么会隐式声明（Implicit Declaration）为 int
                        C标准为了兼容旧的代码仍然保留了这种语法，但读者绝不应该继续使用这种语法。

    void foo(void);     推荐写法  ， 如果函数 foo() 的返回值为 void ，那么 foo() + 1 这样的表达式就无法通过语义检查
    int  foo(int age);  推荐写法

只有带函数体的声明才叫函数定义。
上一章讲过，只有分配存储空间的变量声明才叫变量定义，其实函数也是一样，
编译器[只有见到函数定义才会生成指令]，而指令在程序运行时当然也要占存储空间。那么没有函数体的函数声明有什么用呢？
它为编译器提供了有用的信息，编译器在翻译代码的过程中，只有见到函数原型（不管带不带函数体）之后才知道这个函数的名字、参数类型和返回值，
这样碰到函数调用时才知道怎么生成相应的指令，所以函数原型必须出现在函数调用之前，这也是遵循“先声明后使用”的原则。

函数的参数

    我们所说的“参数”是指形参（Parameter），当我们讨论传一个参数23给函数时，我们所说的“参数”是指实参（Argument）

    // 主调函数
    void main(void){
        int age=11;
        foo(age);
    }

    // 被调函数
    void foo(int func_age){
        printf(" %d\n",func_age);
    }

Call by Value

    主调函数中  将常量 11 存到  变量 age所表示的内存空间中，
    主调函数调用foo()函数，编译器为被调函数的形参变量 func_age 分配空间，并将 主调中 age 空间中的值，也就是11 Copy 到func_age代表的内存空间中
    foo() 函数体内的语句操作 func_age ,其值变化不会影响到主调中age空间内的值

Call by address

    将地址传递到被调，被调中按地址操作 ，会影响主调中的变量值