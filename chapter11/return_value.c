#include <stdio.h>

void main(void)
{
    char name[40];
    char * pfgets;
    char * pfputs;

    pfgets = fgets(name,40,stdin);
    //pfputs = fputs(name,stdout);

    // fgets 在读取输入行失败 或者 读取到文件末尾时  返回值为 NULL
    printf("%s \n",pfgets);


}

