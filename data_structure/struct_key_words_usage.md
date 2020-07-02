struct

eg.
    struct BOOK{
        char name[50];
        int age;
    }bk;

BOOK ： 数据结构模板
bk ：   数据结构类型简写

注意
    结构模板声明末尾需要添加分号表示结束
    函数原型声明末尾需要添加分号表示结束

易错点解析

    -- 这种 declare 方式可以编译通过

    struct Node{
        char name[50];
        int age;
    };

    struct List{
        char cla[];
        struct Node dn;
    };

-- 这种 declare 无法通过编译 ,提示 error: unknown type name ‘dNode’

    typedef struct Node{
        char name[50];
        int age;
    }dNode;

    struct List{
        char cla[];
        dNode dn;
    };

-----------------------------------------------------------

无法通过编译
typedef 发生的编译阶段,而且该关键字仅仅是生成一个类型简写

即先后顺序为：
    1 声明结构
    2 创建简写

但是在声明阶段【1】中就引用了 类型简写，so struct abbreviation must be declared before use

    typedef struct Node{

        dNode * left;
        dNode * right;

    }dNode;

    // 无法通过编译
    typedef struct Node{

        struct Node left;
        struct Node right;

    }dNode;

// 可以通过编译
这个声明和前面那个声明的区别在于left right 是一个指针而不是结构
[编译器在结构的长度确定之前就已经知道了指针的长度，所以其自引用是合法的]

    typedef struct Node{

        struct Node * left;
        struct Node * right;

    }dNode;

