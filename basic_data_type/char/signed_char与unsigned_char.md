## signed char 与 unsigned char 的区别

#### 遇到问题

今天有一个困扰的问题，就是`char`与`signed char`, `unsigned char`这三个概念之间的区别.

#### char的定义

C标准中对char是 `Impementation Defined`，就是未明确定义.那它由什么定义？
也就是说由具体的编译器明确定义`char`，`char`更像是`signed char`或`unsigned char`两者中一个的简称.
比如说`VC编译器`、x86上的`GCC`都把`char`定义为`signed char`，而`arm-linux-gcc`却把`char`定义为`unsigned char`.

#### char的使用

 - 用`char`来表示一个字符,比如`ASCII`的128个字符.此时最高位弃用.
 - 用`char`来表示一个很小的整数.因为整型里面的最小类型`short int`占用两个字节,比char多一个字节.在我们表示位数组时char经常会被用到.

