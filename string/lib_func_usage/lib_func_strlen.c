#include <stdio.h>
#include <string.h>
#define LEN 10

int main(void)
{
    char name[LEN] = "hello";

    // strlen函数返回s所指的字符串的长度。该函数从s所指的第一个字符开始找'\0'字符，
    // 一旦找到就返回，返回的长度不包括'\0'字符在内。
    printf(" string : [%s], length %lu , array size is %d \n",name,strlen(name),LEN);
    return 0;

    // 但要注意，如果定义char buf[5] = "hello";，则调用strlen(buf)是危险的，可能会造成数组访问越界
}

/*
/home/sujianhui/CLionProjects/C/cmake-build-debug/test
 string : [hello a], length 7 , array size is 10

      Oct   Dec   Hex   Char                        Oct   Dec   Hex   Char
       ────────────────────────────────────────────────────────────────────────
       000   0     00    NUL '\0'                    100   64    40    @
       001   1     01    SOH (start of heading)      101   65    41    A
       002   2     02    STX (start of text)         102   66    42    B
       003   3     03    ETX (end of text)           103   67    43    C
       004   4     04    EOT (end of transmission)   104   68    44    D
       005   5     05    ENQ (enquiry)               105   69    45    E
       006   6     06    ACK (acknowledge)           106   70    46    F

字符串以NUL结尾

*/