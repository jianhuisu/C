#include <stdio.h>
#include <stdlib.h>
typedef char BYTE;  // 具有 #define BYTE unsigned char 作用
typedef struct{int x;int y} rect;
typedef struct complex
    {
        int x;
        int y;
    }COMPLEX;

void main(void)
{
    BYTE name[10] = "sujianhui";

    puts(name);



    rect name1 = {1,2};
    rect name2 = {3,4};

    printf("%d \n",name1.x);
    printf("%d \n",name1.y);



    COMPLEX jianhui = {1,2};

    printf("%d \n",jianhui.x);
    printf("%d \n",jianhui.y);
}

