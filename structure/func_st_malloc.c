#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct name{
	char * first;
	char * last;
	double letter;
};

void getInfo(struct name *);
void cleanUp(struct name *);
void main(void)
{
	struct name student;
	getInfo(&student);
}

void getInfo(struct name * pt)
{

	char tmp[30];
	pt->first = (char *)malloc( strlen(tmp) + 1 )	;
	puts("please entry your first name");
	fgets(tmp,30,stdin);

	// 把姓名 copy到临时分配的内存中
	strcpy(pt->first,tmp);
	puts(pt->first);	
}


void cleanUp(struct name * pt)
{
    free(pt->first);
    // free(pt->last);  非 malloc 分配的内存不能使用 free 释放
}

#if 0
assignment makes integer from pointer without a cast

把指针赋值给了整形

struct name{
	char  first;
	char  last;
	double letter;
};


pt->first = (char *)malloc( strlen(tmp) + 1 )	;

first 是整型 但是 malloc() 函数返回指针 造成以上错误

#endif
