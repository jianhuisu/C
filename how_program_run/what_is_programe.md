编程语言

    Low Level
        机器语言  汇编语言 (汇编语言指令与机器语言的指令是一一对应的,并且依赖于运行平台)
    High Level
        C C++ java 一条高级语言指令可能对应 1 - N 条机器语言,
        高级语言需要被翻译为机器语言才可以运行,翻译程序负责处理各平台之间
        instruction set 的差异，这就使得高级语言具有 portable ，或者 platform independent

        高级语言翻译执行的两种类型(两种方式各有优缺点)

            编译器 compiler
                编译器由平台的提供商提供，一次翻译，多次执行  例如 C
                gcc是Linux平台的C编译器
                MinGW（Minimalist GNU on Windows） Windows平台下的C编译器
                Clang是一个由Apple公司主导编写,Unix平台编译器

            解释器 interpreter 解释一条，执行一条

                shell脚本，每一行都是一条命令


自然语言与形式语言

    关于Token的规则称为词法（Lexical）规则
    而关于结构的规则称为语法（Grammar）规则

错误的类型

    编译时错误
    运行时错误   Run-time error
    语义错误

Debug

    Debug能力与Program能力同样重要
    一个好的习惯是打开gcc的-Wall选项，也就是让gcc提示所有的警告信息，不管是严重的还是不严重的，然后把这些问题从代码中全部消灭。
    gcc -Wall main.c

