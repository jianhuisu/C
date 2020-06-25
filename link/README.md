## 多目标文件的链接

链接器也是一种编辑器，vi和emacs编辑的是源文件，而链接器编辑的是目标文件，所以链接器也叫Link Editor

使用nm查看目标文件的符号表
 
    [guangsujiqiang@su-ct7 Link]$>nm a.out
    // The symbol value | The symbol type | The symbol name 
    0000000000601044 B a
    0000000000601034 D b
    000000000060103c B __bss_start
    0000000000601040 b completed.6355
    0000000000601030 D __data_start
    0000000000601030 W data_start
    0000000000400470 t deregister_tm_clones
    00000000004004e0 t __do_global_dtors_aux
    0000000000600e18 t __do_global_dtors_aux_fini_array_entry
    0000000000400678 R __dso_handle
    0000000000600e28 d _DYNAMIC
    000000000060103c D _edata
    0000000000601260 B _end
    0000000000400664 T _fini
    0000000000400500 t frame_dummy
    0000000000600e10 t __frame_dummy_init_array_entry
    0000000000400820 r __FRAME_END__
    0000000000601000 d _GLOBAL_OFFSET_TABLE_
                     w __gmon_start__
    0000000000400680 r __GNU_EH_FRAME_HDR
    00000000004003e0 T _init
    0000000000600e18 t __init_array_end
    0000000000600e10 t __init_array_start
    0000000000400670 R _IO_stdin_used
    00000000004005da T is_empty
    0000000000600e20 d __JCR_END__
    0000000000600e20 d __JCR_LIST__
    0000000000400660 T __libc_csu_fini
    00000000004005f0 T __libc_csu_init
                     U __libc_start_main@@GLIBC_2.2.5
    000000000040052d T main
    00000000004005bc T pop
    0000000000400590 T push
                     U putchar@@GLIBC_2.2.5  // ---------------------------------------------> 这个符号未定义 链接生成可执行文件main时可以做符号解析，而putchar是libc的库函数，在可执行文件main中仍然是未定义的，要在程序运行时做动态链接。
    00000000004004a0 t register_tm_clones
    0000000000601060 B stack
    0000000000400440 T _start
    0000000000601040 D __TMC_END__
    0000000000601038 D top

### 函数的 external Linkage 与 internal Linkage

#### external Linkage
main.c

    #include <stdio.h>
    
    int a, b = 1;
    
    int main(void)
    {
        push('a');
        push('b');
        push('c');
        
        while(!is_empty())
            putchar(pop());
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

如果把main.c和stack.c链接在一起，如果push在main.c和stack.c中都有声明（在stack.c中的声明同时也是定义），
那么这些声明指的是同一个函数，链接之后是同一个GLOBAL符号，代表同一个地址。
函数声明中的extern也可以省略不写，不写extern的函数声明也表示这个函数具有External Linkage。

#### internal Linkage

main.c

    #include <stdio.h>
    
    void set_name(char * name);
    
    int main(void)
    {
    	set_name("sujianhui");
    	return 0;
    }
    
stack.c
    
    #include <stdio.h>
    
    static void set_name(char * name)
    {
        printf(" %s \n",name);
    }

编译链接

    [guangsujiqiang@su-ct7 internal]$>gcc main.c stack.c 
    /tmp/ccwhd9Fm.o: In function `main':
    main.c:(.text+0xa): undefined reference to `set_name'
    collect2: error: ld returned 1 exit status
 
stack.c中使用 static 关键字声明 `set_name`函数,该函数只具有Internal Linkage,
意思就是不允许外部目标文件引用该函数。函数名set_name在其中是一个LOCAL的符号，**不参与链接过程**，所以在链接时，
main.c中用到一个External Linkage的foo函数，链接器却找不到它的定义在哪儿，无法确定它的地址，也就无法做符号解析，只好报错。
(有没有很像类中的私有方法 不允许其它类调用)(LOCAL / GLOBAL 不在一个空间，就不会引起冲突)

!!!重点：凡是被多次声明的变量或函数，必须有且只有一个声明是定义，如果有多个定义，或者一个定义都没有，链接器就无法完成链接。
比如说 stack.c 与 main.c 中都实现了对`pop()`函数的声明与定义,那么 stack.c与main.c就不能链接在一起.此时可以使用include公共头文件的
方法,在stack.c中声明一次,定义一次,在main.c中声明一次,未进行重复定义,stack.c 与 main.c可以链接在一起.

### 变量的 external Linkage 与 internal Linkage

main.c

    #include <stdio.h>
    
    int main(void)
    {
        // 声明一个 具有external Linkage 属性的变量,注意不是定义一个变量，定义操作在其它目标文件中实现
        // 并且该变量具有块作用域
        extern int top;
        printf("%d \n ",top);
        return 0;
    }

变量声明和函数声明有一点不同，函数声明的extern可写可不写，而变量声明如果不写extern意思就完全变了，如果上面的例子不写extern就表示在main函数中声明一个局部变量top。
另外要注意，stack.c中的定义是`int top = -1;`而main.c中的声明不能加Initializer，如果上面的例子写成`extern int top = -1;`则编译器会报错。

在main.c中可以通过变量声明来访问stack.c中的变量top，但是从实现stack.c这个模块的角度来看，top这个变量是不希望被外界访问到的，
变量top和stack都属于这个模块的内部状态，外界应该只允许通过push和pop函数来改变模块的内部状态，这样才能保证堆栈的LIFO特性，
如果外界可以随机访问stack或者随便修改top，那么堆栈的状态就乱了。那怎么才能阻止外界访问top和stack呢？答案就是用static关键字把它们声明为Internal Linkage的：

stack.c

    static int top = -1;
        
这样，即使在main.c中用extern声明也访问不到stack.c的变量top和stack。从而保护了stack.c模块的内部状态，这也是一种封装（Encapsulation）的思想。
(有没有很像类的私有成员变量)

用static关键字声明具有Internal Linkage的函数也是出于这个目的。在一个模块中，有些函数是提供给外界使用的，也称为导出（Export）给外界使用，(在go中,这个概念尤为明显)
这些函数声明为`External Linkage的`。有些函数只在模块内部使用而不希望被外界访问到，则声明为`Internal Linkage`的。




