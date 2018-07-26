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
