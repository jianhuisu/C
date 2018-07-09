/*
    const 修饰


*/
#include <stdio.h>
#define MAX_WIDTH 20
void main(void)
{
    //pro_arr();
    pro_pointer();
}

pro_arr()
{
    // 保护数组
    const int sex[5] = {1,1,1,1,0};
    sex[4] = 1;

}

#if 0
const_1.c: In function ‘pro_arr’:
const_1.c:17: error: assignment of read-only location ‘sex[4]’
#endif

pro_pointer()
{
    // 保护数组
    int sex[5] = {1,1,1,1,0};
    const int * p = sex;  // 不能使用 p 来更改它所指向的值
    *p = 0;
    p[2] = 0; //  *(p + 2)
    sex[0] = 0;


}

#if 0
const_1.c:32: error: assignment of read-only location ‘*p’
#endif



