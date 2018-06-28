第三章 数据

    这一章需要记忆的知识点比较多 读起来有点蒙

    字不如图，图不如表，表不如视频

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