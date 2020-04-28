## string

### 定义

在C中,以Null字符('\0')结尾的一串字符都叫字符串

### 初始化

如果要用一个字符串字面值准确地初始化一个字符数组，最好的办法是不指定数组的长度，让编译器自己计算：

    char str[] = "Hello, world.\n";  // 15

数组可以像结构体一样初始化，如果是字符数组，也可以用一个字符串字面值来初始化：

    char str[10] = "Hello";

等价于：

    char str[10] = { 'H', 'e', 'l', 'l', 'o', '\0' }; // str的后4个元素没有指定，自动初始化为0，即Null字符

### 易错点

如果用于初始化的字符串字面值比数组还长，比如：

    char str[10] = "Hello, world.\n";  // 只会包含 "Hello, wor"

数组str只包含字符串的前10个字符，不包含Null字符

### printf %s

    printf("string: %s\n", str);

`%s`格式化占位符指定`printf`会从数组str的开头一直打印到`Null`字符为止，`Null`字符本身是`Non-printable`字符，不打印。