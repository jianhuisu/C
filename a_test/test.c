#include <stdio.h>

int main(int argc, char** argv)
{
    typedef struct {
        char a;
        int b;
        short c;
        char d;
    }st;

    st s;
    s.a = 1;
    s.b = 2;
    s.c = 3;
    s.d = 4;

    printf("%u \n ",sizeof(st));
    printf("%u %u  %u  %u \n ",s.a,s.b,s.c,s.d);

}