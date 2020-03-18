## 预处理 宏

宏是一种预处理语言,一种用于保障C代码的可移植性的工具
cpp 是预处理器,预处理不做C语法检查

### 预处理指令的定义

一条预处理指示由一个逻辑代码行组成，以#开头，后面跟若干个预处理Token，**在预处理指示中允许使用的空白字符只有空格和Tab**。
(空白符主要有空格符、回车换行符、制表符三种字符)
经过预处理器处理的文本可以称为`C Token`,之前称为`预处理 Token`

以前我们用过的`#define N 20`或`#define STR "hello, world"`这种宏定义可以称为变量式宏定义（Object-like Macro），宏定义名可以像变量一样在代码中使用。
另外一种宏定义可以像函数调用一样在代码中使用，称为函数式宏定义（Function-like Macro）

### 函数式宏定义的使用场景 Function-like Macro

vim func_macro_define.c

    #define STR "hello world"               /* 变量式宏定义（Object-like Macro） 展开时替换源码中的宏 未使用则不替换*/
    #define MAX(a,b) ((a)>(b)?(a):(b))      /* 函数式宏定义（Function-like Macro） */
    //k = MAX(i&0x0f, j&0x0f)
    
    int min(int a,int b)
    {
    	return a > b ? b : a;
    }
    
    int main(int argc,char ** argc)
    {
    	int o = 1;
    	int p = 1;
    	int q = 1;
    	int r = 1;
    	int s = 1;
    
    	r = MAX(o,p);
    	r = MAX(o,q);
    	r = MAX(o,s);
    
    	r = min(o,p);
    	r = min(o,q);
    	r = min(o,s);
    
    	return 0;
    }

预处理展开 

    [guangsujiqiang@su-ct7 preprocessing]$>cpp func_macro_define.c 
    # 1 "macro_define.c"
    # 1 "<built-in>"
    # 1 "<command-line>"
    # 1 "/usr/include/stdc-predef.h" 1 3 4
    # 1 "<command-line>" 2
    # 1 "macro_define.c"
    # 9 "macro_define.c"
    int min(int a,int b)
    {
     return a > b ? b : a;
    }
    
    int main(int argc,char ** argc)
    {
     int o = 1;
     int p = 1;
     int q = 1;
     int r = 1;
     int s = 1;
    
     r = ((o)>(p)?(o):(p));
     r = ((o)>(q)?(o):(q));
     r = ((o)>(s)?(o):(s));
    
     r = min(o,p);
     r = min(o,q);
     r = min(o,s);
    
     return 0;
    }

观察预处理的输出
    
    // 这里是函数式宏定义的展开结果
    r = ((o)>(p)?(o):(p));
    r = ((o)>(q)?(o):(q));
    r = ((o)>(s)?(o):(s));
    
    // 这里是真正的常规函数调用
    r = min(o,p);
    r = min(o,q);
    r = min(o,s);

当对预处理完成的文件进行编译时,`((o)>(p)?(o):(p))`会被重复编译多次(这里展开三次 所以重复调用3三次),即**展开N次 编译N次**
而下面的`min(o,p)`会被当作函数调用来编译,这里只会编译为几条简单的传参指令和call指令,即**一次编译,多次调用**

**所以** :

使用函数式宏定义编译生成的**目标文件会比较大**,使用函数式宏定义也往往会导致较低的代码执行效率,
尽管函数式宏定义和真正的函数相比有很多缺点，但只要小心使用还是会显著提高代码的执行效率，毕竟省去了分配和释放栈帧、传参、传返回值等一系列工作，
因此那些简短并且被频繁调用的函数经常用函数式宏定义来代替实现。

我的个人理解：

 - 当函数式宏的函数体编译后的执行开销小于C函数调用的栈帧分配/释放/传参/传递返回值一系列操作开销之和时,选择函数式宏定义方式会显著提高代码的执行效率)
 - 当函数体实现比较复杂时,优先选择常规函数调用方式,复杂函数使用函数式宏定义容易出现语法错误 逻辑错误,增加调试难度

### Func macro like

宏必须要定义成为一条逻辑行,可以使用`\`把一条逻辑行分割成为多条物理行

正确方式

    #define device_init_wakeup(dev,val) \
    do { \
            device_can_wakeup(dev) = !!(val); \
            device_set_wakeup_enable(dev,val); \
    } while(0)

错误方式

    #define device_init_wakeup(dev,val) \
        device_can_wakeup(dev) = !!(val); \
        device_set_wakeup_enable(dev,val);
    if (n > 0)
    	device_init_wakeup(d, v);
    
### 内联函数

C99引入一个新关键字inline，用于定义内联函数（inline function）。这种用法在内核代码中很常见
inline关键字告诉编译器，这个函数的调用要尽可能快，可以当普通的函数调用实现，也可以用宏展开的办法实现(具体选择哪种方式 由编译器决定)
这里的宏展开意思就是,将函数式宏定义所代表的一系列操作`复制`到宏的调用处,而不是声明一个函数,然后调用传参
    
    // 这里使用了 inline 关键字
    inline int MAX(int a, int b)
    {
    	return a > b ? a : b;
    }
    
    int a[] = { 9, 3, 5, 2, 1, 0, 8, 7, 6, 4 };
    
    int max(int n)
    {
    	return n == 0 ? a[0] : MAX(a[n], max(n-1));
    }
    
    int main(void)
    {
    	max(9);
    	return 0;
    }

编译后观察 汇编指令

    $ gcc main.c -g 
    $ objdump -dS a.out
    ...
    int max(int n)
    {
     8048369:       55                      push   %ebp
     804836a:       89 e5                   mov    %esp,%ebp
     804836c:       83 ec 0c                sub    $0xc,%esp
            return n == 0 ? a[0] : MAX(a[n], max(n-1));
     804836f:       83 7d 08 00             cmpl   $0x0,0x8(%ebp)
     8048373:       75 0a                   jne    804837f <max+0x16>
     8048375:       a1 c0 95 04 08          mov    0x80495c0,%eax
     804837a:       89 45 fc                mov    %eax,-0x4(%ebp)
     804837d:       eb 29                   jmp    80483a8 <max+0x3f>
     804837f:       8b 45 08                mov    0x8(%ebp),%eax
     8048382:       83 e8 01                sub    $0x1,%eax
     8048385:       89 04 24                mov    %eax,(%esp)
     8048388:       e8 dc ff ff ff          call   8048369 <max>
     804838d:       89 c2                   mov    %eax,%edx
     804838f:       8b 45 08                mov    0x8(%ebp),%eax
     8048392:       8b 04 85 c0 95 04 08    mov    0x80495c0(,%eax,4),%eax
     8048399:       89 54 24 04             mov    %edx,0x4(%esp)
     804839d:       89 04 24                mov    %eax,(%esp)
     80483a0:       e8 9f ff ff ff          call   8048344 <MAX>  // -----------------> max函数体中 调用 MAX 函数 ,内联函数被当作普通函数调用
     80483a5:       89 45 fc                mov    %eax,-0x4(%ebp)
     80483a8:       8b 45 fc                mov    -0x4(%ebp),%eax
    }
    ...

`gcc -g`参数表示需要在目标文件中生成符号信息 便于将生成的汇编指令与源码建立对应关系,如果不使用 -g 选项,则目标文件中没有源码信息,
反汇编的输出中只包含汇编代码,而没有源码标注,可读性差.(原来一直以为 不使用-g 编译完成的目标文件则无法反汇编)

如果指定优化选项编译，然后反汇编：

    $ gcc main.c -g -O
    $ objdump -dS a.out
    ...
    int max(int n)
    {
     8048355:       55                      push   %ebp
     8048356:       89 e5                   mov    %esp,%ebp
     8048358:       53                      push   %ebx
     8048359:       83 ec 04                sub    $0x4,%esp
     804835c:       8b 5d 08                mov    0x8(%ebp),%ebx
            return n == 0 ? a[0] : MAX(a[n], max(n-1));
     804835f:       85 db                   test   %ebx,%ebx
     8048361:       75 07                   jne    804836a <max+0x15>
     8048363:       a1 a0 95 04 08          mov    0x80495a0,%eax
     8048368:       eb 18                   jmp    8048382 <max+0x2d>
     804836a:       8d 43 ff                lea    -0x1(%ebx),%eax
     804836d:       89 04 24                mov    %eax,(%esp)
     8048370:       e8 e0 ff ff ff          call   8048355 <max>
    inline int MAX(int a, int b)
    {
            return a > b ? a : b;
     8048375:       8b 14 9d a0 95 04 08    mov    0x80495a0(,%ebx,4),%edx
     804837c:       39 d0                   cmp    %edx,%eax
     804837e:       7d 02                   jge    8048382 <max+0x2d>
     8048380:       89 d0                   mov    %edx,%eax
    int a[] = { 9, 3, 5, 2, 1, 0, 8, 7, 6, 4 };
    
    int max(int n)
    {
            return n == 0 ? a[0] : MAX(a[n], max(n-1));
    }
     8048382:       83 c4 04                add    $0x4,%esp
     8048385:       5b                      pop    %ebx
     8048386:       5d                      pop    %ebp
     8048387:       c3                      ret    
    ...

反汇编结果中可以观察到，并没有call指令调用MAX函数，MAX函数的指令是内联在max函数中的，
由于源代码和指令的次序无法对应，max和MAX函数的源代码也交错在一起显示。
!!!所以 内联的概念与函数调用的概念再某程度上是相对的

todo 继续理解吧 现在注意力无法集中 效率有点低 做点别的 https://docs.huihoo.com/c/linux-c-programming/ch21s02.html

### 条件预处理指示

常见条件预处理指令

    #ifndef HEADER_FILENAME
    #define HEADER_FILENAME
    /* body of header */
    #endif
    
    #if MACHINE == 68000
        int x;
    #elif MACHINE == 8086
        long x;
    #else    /* all others */
        #error UNKNOWN TARGET MACHINE
    #endif

undef的使用,代码用`#undef`确保取消一些宏的定义，已经定义的宏重复定义会导致错误,如果先前没有定义过CONFIG_DUMMY，用#undef CONFIG_DUMMY取消它的定义没有任何作用，也不算错。

    ...
    /*
     * Network device support
     */
    #define CONFIG_NETDEVICES 1
    #undef CONFIG_DUMMY
    #undef CONFIG_BONDING
    #undef CONFIG_EQUALIZER
    #undef CONFIG_TUN
    ...
    
要定义一个宏不一定非得在代码中用#define定义，使用用gcc的-D选项定义一个宏DMACHINE。可以写成类似这样的命令：gcc -c -DMACHINE=8086 main.c。
这种办法需要给每个编译命令都加上适当的选项，相较于修改公共头文件中的宏定义就可以在很多源文件中生效 显的有点麻烦.

最后通过下面的例子说一下#if后面的表达式：

    #define VERSION  2
    #if defined x || y || VERSION < 3
    
首先处理defined运算符，defined运算符一般用作表达式中的一部分，如果单独使用，#if defined x相当于#ifdef x，而#if !defined x相当于#ifndef x。在这个例子中，如果x这个宏有定义，则把defined x替换为1，否则替换为0，因此变成#if 0 || y || VERSION < 3。

然后把有定义的宏展开，变成#if 0 || y || 2 < 3。

把没有定义的宏替换成0，变成#if 0 || 0 || 2 < 3，注意，即使前面定义了一个变量名是y，在这一步也还是替换成0，因为#if的表达式必须在编译时求值，其中包含的名字只能是宏定义。

把得到的表达式0 || 0 || 2 < 3像C表达式一样求值，求值的结果是#if 1，因此条件成立。