//
// Created by 苏建辉 on 2020/1/11.  该例子存在bug  使用gdb 进行调试
//
#include <stdio.h>

int main(void)
{
    int sum = 0, i = 0;
    char input[5];

    while (1) {
        scanf("%s", input);
        for (i = 0; input[i] != '\0'; i++)
            sum = sum*10 + input[i] - '0';
        printf("input=%d\n", sum);
    }

    return 0;
}

