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

    him 是一个指向结构的指针
    him->face 代表该指针所指向结构的一个成员

    如果 library 是一个结构变量 那么需要使用 &library 形式获取变量地址
    区别于数组名为数组首元素的地址

        him = &library   （library 等价于 &coll[0] coll是数据结构数组）
        him = &coll[0];
        *him 等价于 library
        library.face 等价于 (*him).face

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


结构与malloc()

    声明结构时 结构成员为指针变量
    初始化结构成员时 , 将使用 malloc() 分配的匿名存储变量的地址赋值给结构的成员

结构数组

struct name docters[2] = {
    {},
    {},
}




复合字面量

    构建一个临时数据结构变量

    声明
    (struct book){"daomubiji"," si xiang hui "}

    使用
    readlist  = (struct book){"daomubiji"," si xiang hui "};


带伸缩型数组的数据结构

    声明要求
        1 结构中至少包含一个成员
        2 伸缩型数据为结构中最后一个成员
        3 不能直接为伸缩数组赋值

    声明方式
        struct book{
            char name[10];
            char sex[10];
            char hobby[];
        };

    hobby 为伸缩型数组

    带伸缩型数组的机构使用特殊要求

    1 不能用于结构的赋值与拷贝
    2 不要使用带伸缩数组的结构作为嵌套结构的成员
    3 不能按值传递


匿名结构
    anonymous.c

将数据保存到文件中
    save_struct_to_file.c
    由于结构可以存储不同类型的信息,所以它是构建数据库的重要工具

联合 union

枚举
enum.c

枚举类型 是整数类型

共享名称空间 namespace

    相同名称空间的同名函数会冲突
    不同名称空间的同名函数不会冲突
    c中相同名称空间内 同名的标记与变量名不会冲突，因为 c 没有把 标记与普通变量放置在同一空间
    c++中相同名称空间内 标记与变量名重名会冲突


typedef

    功能与#define类似

    1 typedef 创建的符号只受限于类型 不能作用于值
    2 typedef 由编译器处理 不由预处理器解释
    3 在受限范围内 比 define 要灵活

typedef 并没有创建新的类型 只不过是为现有类型创建了简写


其它复杂的声明

    * （）  [] 的优先级
    1 数组名后面的 [] 与函数名后面的() 优先级相同 并高于 *
    2 [] () 优先级相同
    3 从左向右结合

    int * uuf[3]

        [] 的优先级高于 * ,首先这个一个包含 3 个元素的数组 ,然后确定数组元素的类型 : 指向 int 的指针
        这是一个包含三个指针元素的指针数组

    int (* uuf)[3]

        question: 从左向右结合  * uuf 先结合,这是一个指针 (不理解)

    int sex[12][50]
    12 个包含 50个 int元素数组 组成的二维数组

    int * uuf[3][4]
    3*4 的二维数组 元素为int 型指针

    int (* uuf)[3][4]
    一个指向 3*4 二维数组的指针


指向函数的指针（这一块还需要深造）

    void ToUpper(char *);
    void ToLower(char *);
    int round(double);

    // 定义指向函数的指针
    void (*pf)(char *);

    pf = ToUpper; // 有效 ToUpper 就是该类型的地址  函数名也是指针
    pf = ToLower; // 有效 ToLower 就是该类型的地址

    pf = round ; // 无效 round 与指针 类型不匹配
    pf = ToUpper() // 无效 ToUpper(char *) 不是一个地址



    char mis[] = "Nina Metier"


    ToUpper(mis)
    pf(mis)  // 语法 1
    (*pf)(mis)  // 语法 2








