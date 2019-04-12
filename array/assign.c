#include <stdio.h>

void main(void)
{
    int age[10] = {2,3,3,3,3,3};
    int sex[10] = {2,3,3,3,3,2};

//    age = sex;  error

    // sex[4] = {3,6}; error

    age[12] = sex[12];  // 数组边界越界

}