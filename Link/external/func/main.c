//
// Created by guangsujiqiang on 3/18/20.
//

#include <stdio.h>

int a, b = 1;

// 在这里extern关键字表示这个标识符具有External Linkage。
// External Linkage的定义在上一章讲过，但现在应该更容易理解了，
// push这个标识符具有External Linkage指的是：如果把main.c和stack.c链接在一起，
// 如果push在main.c和stack.c中都有声明（在stack.c中的声明同时也是定义），那么这些声明指的是同一个函数，
// 链接之后是同一个GLOBAL符号，代表同一个地址。函数声明中的extern也可以省略不写，
// 不写extern的函数声明也表示这个函数具有External Linkage。

// !!! 我们可以把这三条声明理解为一个占位符号 ,在链接阶段 ,Linker Editor会补充占位符的地址 ,每一个相对独立的程序都要为引用的外部符号提前声明占位符号
// 使用这个模块(即使用stack.o目标文件中符号)的每个程序文件都要写三个函数声明，
// 假设又有一个foo.c也使用这个模块，main.c和foo.c中各自要写三个函数声明。这是很麻烦的,而且是重复的代码总是应该尽量避免的
// !!! 所以 衍生出了头文件的 概念, 这样在main.c中只需包含这个头文件就可以了，而不需要写三个函数声明
extern void push(char);
extern char pop(void);
extern int is_empty(void);

int main(void)
{
	push('a');
	push('b');
	push('c');

	while(!is_empty())
	{
		putchar(pop());
	}

	putchar('\n');
	return 0;
}