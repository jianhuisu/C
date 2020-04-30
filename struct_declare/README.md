## struct

struct complex_struct {
	double x, y;
};

这一句定义了标识符complex_struct（同样遵循标识符的命名规则），这种标识符在C语言中称为**Tag**，
这一句定义了标识符complex_struct 是一个复合类型，如果用这个类型名来定义变量，可以这样写：

struct complex_struct {
	double x, y;
} z1, z2;

如果在定义结构体类型的同时定义了变量，也可以不必写Tag，例如：

    struct {
        double x, y;
    } z1, z2;

**但这样就没办法再次引用这个结构体类型了，因为它没有名字。**

#### 初始化的问题

    struct complex_struct z = { 3.0, 4.0 };
    // struct complex_struct z = { 3.0, 4.0 ,};

Initializer中的数据依次赋给结构体的各成员。

 - 如果Initializer中的数据比结构体的成员多，编译器会报错，但如果只是末尾多个逗号则不算错。
 - 如果Initializer中的数据比结构体的成员少，未指定的成员将用0来初始化，就像未初始化的全局变量一样。

Designated Initializer是C99引入的新特性，用于初始化稀疏（Sparse）结构体和稀疏数组很方便。
有些时候结构体或数组中只有某一个或某几个成员需要初始化，其它成员都用0初始化即可，
用Designated Initializer语法可以针对每个成员做初始化（Memberwise Initialization），很方便。例如：

    struct complex_struct z1 = { .y = 4.0 }; /* z1.x=0.0, z1.y=4.0 */

#### 把结构体当作一个函数参数

结构体变量之间使用赋值运算符是允许的，用一个结构体变量初始化另一个结构体变量也是允许的，例如：

    struct complex_struct z1 = { 3.0, 4.0 };
    struct complex_struct z2 = z1;
    z1 = z2;

同样地，z2必须是局部变量才能用变量z1的值来初始化。既然结构体变量之间可以相互赋值和初始化，也就可以当作函数的参数和返回值来传递：

    struct complex_struct add_complex(struct complex_struct z1, struct complex_struct z2)
    {
        z1.x = z1.x + z2.x;
        z1.y = z1.y + z2.y;
        return z1;
    }

这个函数实现了两个复数相加，如果在main函数中这样调用：

    struct complex_struct z = { 3.0, 4.0 };
    z = add_complex(z, z);

虽然结构体complex_struct的存储表示做了这样的改动，add_complex、sub_complex、mul_complex、div_complex这几个复数运算的函数却不需要做任何改动，
仍然可以用，**原因在于这几个函数只把结构体complex_struct当作一个整体来使用，而没有直接访问它的成员，因此也不依赖于它有哪些成员**。
complex_struct结构体的格式变了，只需要修改复数存储表示层的函数

--------------------------------------------------
这里是一种抽象的思想。其实“抽象”这个概念并没有那么抽象，简单地说就是“提取公因式”：ab+ac=a(b+c)。
如果a变了，ab和ac这两项都需要改，但如果写成a(b+c)的形式就只需要改其中一个因子。

这里的复数存储表示层和复数运算层称为抽象层（Abstraction Layer），从底层往上层来看，复数越来越抽象了，
把所有这些层组合在一起就是一个完整的系统。
组合使得系统可以任意复杂，而抽象使得系统的复杂性是可以控制的，
任何改动都只局限在某一层，而不会波及整个系统。
著名的计算机科学家Butler Lampson说过：“All problems in computer science can be solved by another level of indirection.”
这里的indirection其实就是abstraction的意思。
---------------------------------------------------

### 结构体中的数据类型标志(非常重要 而且常用)

我们通过一个复数存储表示抽象层把complex_struct结构体的存储格式和上层的复数运算函数隔开，complex_struct结构体既可以采用直角座标也可以采用极座标存储。
但有时候需要同时支持两种存储格式，比如先前已经采集了一些数据存在计算机中，有些数据是以极座标存储的，有些数据是以直角座标存储的，
如果要把这些数据都存到complex_struct结构体中怎么办？

一种办法是规定complex_struct结构体采用直角座标格式，直角座标的数据可以直接存入complex_struct结构体，而极座标的数据先转成直角座标再存，
但由于浮点数的精度有限，转换总是会损失精度的。

这里介绍另一种办法(非常实用 例如php的zval结构体实现)，complex_struct结构体由一个数据类型标志和两个浮点数组成，

 - 如果数据类型标志为0，那么两个浮点数就表示直角座标.
 - 如果数据类型标志为1，那么两个浮点数就表示极座标.

这样，直角座标和极座标的数据都可以适配（Adapt）到complex_struct结构体中，**无需转换和损失精度**.

    enum coordinate_type { RECTANGULAR, POLAR };
    struct complex_struct {
        enum coordinate_type t;
        double a, b;
    };

`enum`关键字的作用和`struct`关键字类似，把`coordinate_type`这个标识符定义为一个`Tag`，
`struct complex_struct`表示一个结构体类型，而`enum coordinate_type`表示一个枚举（`Enumeration`）类型。
枚举类型的成员是常量，它们的值由编译器自动分配，例如定义了上面的枚举类型之后，
`RECTANGULAR`就表示常量`0`，`POLAR`表示常量`1`。如果不希望从`0`开始分配，可以这样定义：

    enum coordinate_type { RECTANGULAR = 1, POLAR };

这样，`RECTANGULAR`就表示常量`1`，而`POLAR`表示常量`2`.枚举常量也是一种整型，其值在编译时确定，
因此也可以出现在常量表达式中，可以用于初始化全局变量或者作为`case`分支的判断条件。

