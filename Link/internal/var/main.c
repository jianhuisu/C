//
// Created by guangsujiqiang on 3/18/20.
//

#include <stdio.h>

int main(void)
{
	// 声明一个 具有external Linkage 属性的变量,注意不是定义一个变量，定义操作在其它目标文件中实现
	// 并且该变量具有块作用域
	extern int top;
	printf("%d \n ",top);
	return 0;
}

