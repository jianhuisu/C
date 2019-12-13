#include <stdio.h>

enum specrum {red,black,yello,hello,pink};

void main(void)
{
    enum specrum color;
    int i;

    for(i = color; i < pink;i++)
    {
        printf("%d",i);
    }

    if(0 == red)
    {
        puts("0 is equal enum value red");
    }
    else
    {
        puts("red is not equal enum value red");
    }

    if("red" == red)
    {
        puts("string red is equal enum value red");
    }
    else
    {
        puts("string is not equal enum value red");
    }

}