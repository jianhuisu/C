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



第二章 基本概念

1 环境
编译环境与运行环境可以不处于同一机器上

翻译环境 translation environment

    compile main.c

    预处理器处理 预处理指令
        进行 include 、常量替换等文本操作
    解析 parse
        语句解析
        [优化器  optimizer]

    生成目标代码  target code
        main.o
    连接器  linker
        链接启动代码

    可执行文件
        a.out

    gcc -c -o /home/www/main.out main.c

        -c  Compile or assemble the source files
        -o  指定目标代码名称



执行环境 execution environment

        加载到内存
        宿主环境
            由操作系统完成
        自由环境
            加载到ROM中


         一个C程序的源代码可能分布于多个文件中 , 但是一个函数只能完整的出现在一个文件中

第三章 数据

    这一章需要记忆的知识点比较多 基础差 压力大啊

    变量的属性：
        生命周期：何时创建， 何时销毁
        存储位置
        作用域
        数据类型


1    整型


      char
      signed char
      unsigned char

      int

        int age;
        age = 1;

        int age = 1;

        int values[20];

        数组的下标总是从 0 开始
        编译器不检查程序对数组下标的引用是否合法
        数组当做参数传递到函数时，是按地址引用，其余类型是按值引用

      unsigned int

      short int
      unsigned short int

      long int
      unsigned long int



      enum 枚举
      字面值常量 是一种实体 （不能出现在 = 号 左边，值不允许改变）
      int age = 333





2    浮点类型

        float
        double
        long double

3    指针

       指针可以有效地实现 tree 、list 这种高级的数据结构
            声明指针 int *a ;
                     int *b,*a,*c;

                     声明并赋值

                     int *a = "hello world";

                     指针变量和它所指向的实体

       指针常量
       字符串常量

4  typedef 为各种数据类型定义新的名字


5    常量

    define

    const


    变量类型
        局部变量
        全局变量
        形参


    变量的作用域
        文件作用域
        函数作用域
        代码块作用域
        原型作用于


    变量存储类型  storage class

        三个地方存储变量

        普通内存：静态变量
            从程序开始到结束
            凡是任何在代码块之外声明的变量全部存储于静态内存中
            static
        堆栈：局部变量
             从代码块开始到结束
             代码块之内声明的变量缺省值为 automatic 存储于堆栈

             int age  = 3;
             auto age = 3;


             该变量所在代码块被执行时 该变量在堆栈中创建
             代码块执行完毕 该变量在堆栈中销毁

        寄存器内存
            register



    链接属性  linkage

        当多个源文件中出现同一标识符时,标识符的链接属性决定 该标识符是否指向同一实体

        external  外部
        internal  内部
        none      无


        链接属性由 关键字 与 变量的声明位置决定

        关键字：用于在变量的声明中 修饰变量的链接属性

        static

            如果某个声明在正常情况下具有 external 属性 那么经过 static 关键字修饰后 链接属性变为 internal
            意思是 该变量被当前源文件私有化 在其它源文件中 reference 同名变量时 不同于该变量

            同理用于函数

        extern

            该关键字将变量属性定义为 external , 可以访问在其它任何地方定义的该变量




        static 关键字特殊说明：
            当static 关键字用于代码块之外时 用于修饰标识符的链接属性
            当static 关键字用于代码块内部   用户修饰标识符的存储类型


    这一章需要以后再完善


第四章 结构语句

    c 的语句与php的语句结构基本一致 所以权当复习一下

if else

if(express)
{
    ; /* 这是一个空语句*/
}

while( express )
{
    statement

}

在 while 的循环体中 使用 break 语句 永久退出循环
在 while 的循环体中 使用 continue 语句 退出当前循环 执行 express 判断

for

for(express1;express2;express3)
{
    statement;
}

express1 初始化部分  只在循环开始时执行一次
express2 条件部分    循环体每次执行之前调用
express3 调整部分    条件部分执行之前调用

do while
switch

switch 语句书中表述的逻辑非常清晰 这里引用一下

express 的结果必须是整形值

case 标签并不是把 语句列表划分为几部分 而是确定语句列表的 进入点 而已
如下 express 值为 3 时  ，从 case 3 进入语句列表开始执行 一直贯穿至语句列表末尾（case6：statement6）

switch(express)
{
    case 1 :
    case 2 :
    case 3 :
        statement 3
    case 4 :
    case 5 :
    case 6 :
        statement 6
    default:
}

那么如何阻止执行贯穿呢 这里引出 break 的定义
break：划分语句列表为不同部分

备注：每个switch 都要有 default 子句;

goto

goto 语句标签;

语句标签定义:
    标识符:
    example

    goto FUNC_END;
        ...

    FUNC_END:
        printf("jump to here");

goto 语句使用场景 跳出多层循环
出于程序异常反馈角度 作者建议我们尽量避免使用 goto 语句