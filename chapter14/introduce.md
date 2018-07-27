第十四章 结构和其它数据形式

structure variable 结构变量

定义

定义数据结构模板
struct  结构标识符 {

};

eg :
    struct book {
        char title[40];
        char auth[40];
        float price;
    };

定义数据结构变量

struct 结构标识符 变量名;

eg:
    struct book library;



简写形式

struct book{
    char title[40];
    char auth[40];
    float price;
}library;

struct{
    char title[40];
    char auth[40];
    float price;
}library;



访问数据结构成员（member） 或 访问数据结构字段 （field）

结构成员运算符： .

    library.title
    library.auth
    library.price


结构变量初始化

    可以在声明的时候初始化

    struct book library = {
        "first book title",
        "first book author",
        56.9
    }

    各成员间使用逗号 隔开


    结构的初始化器
    struct book library = {
            .title = "first book title",
            .auth  = "first book author",
            .price = 56.9
        }

    可以按照任意顺序


结构变量的嵌套

struct love{
    char man[40];
    char woman[40];
};

struct{
    struct love m1;
    char title[40];
    char auth[40];
    float price;
}library;


指向数据结构的指针

    him 是一个指向结构的指针 但是 him->face 是该指针所指向结构的一个成员

    如果 library 是一个结构变量 那么需要使用 &library 形式获取变量地址

        him = &library   （library 等价于 &coll[0] ）
        进而推导出  him = &coll[0];

        *him 等价于 library
        那么
        (*him).face 等价于 library.face

现在的C允许把一个结构的值 赋值  给另外一个结构,但是数组不可以

struct name aaa;
struct name bbb = {
    "jian",
    "hui",
}

aaa = bbb;

结构和结构指针的选择

实例代码
    func_struct_pointer.c
    func_struct_arr.c

将结构变量当做参数传递给函数时，我们有两种方式可以选择

传递给函数指针，或者传递给函数结构变量


传递指针:

    优点: 直接操作原始数据,不用生成数据副本 效率高
    缺点：可读性较差
          无法保护原始数据 (可以使用 const 限定符禁止修改)


传递结构变量:

    优点: 可读性高,操作对象为数据副本 原始数据安全
    缺点: (自动变量)生成数据副本,消耗时间、空间


    总结: 数据规模小时采用 传递 结构变量
          数据规模较大时  传递 结构指针









