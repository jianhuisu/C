//
// Created by guangsujiqiang on 3/18/20.
//

#include <stdio.h>

//extern void set_name(char * name);
void set_name(char * name);

int main(void)
{
	extern int top;
	printf(" %d \n",top);
	set_name("sujianhui");
	return 0;
}

