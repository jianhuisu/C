#include <stdio.h>
#define MTYPE(X) _Generic((X),\
int:"int",\
float:"float",\
default:"default"\
)

void main(void)
{
    int age = 3;
    printf("%s \n",MTYPE(age));

}
// 这个脚本有错误 不过目前没有定位到错误原因