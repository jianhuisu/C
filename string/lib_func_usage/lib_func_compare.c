#include <stdio.h>
#include <string.h>

int main(void)
{


    char name1[10] = "su";
    char name2[10] = "jianhui";

    printf("%s \n",strcat(name1,name2));
    printf("%s \n",strncat(name1,name2,4));

    char host1[10] = "zhaojianwei";
    char host2[10] = "zhaoshanhe";
    int cmp_result = memcmp(host1,host2,5);
    if( cmp_result  == 0 ){
        printf("equal \n");
    } else if(cmp_result > 0){
        printf("str1 is more than str2 \n");
    } else {
        printf("str1 is less than str2 \n");
    }



    return 0;
}

/*
 *
 * memcmp 从前到后逐个比较缓冲区s1和s2的前n个字节（不管里面有没有'\0'），
 * 如果s1和s2的前n个字节全都一样就返回0，如果遇到不一样的字节，s1的字节比s2小就返回负值(比较第一个不一样字节的二进制值)，
 * s1的字节比s2大就返回正值。
 *
 *
 * strcmp把s1和s2当字符串比较，在其中一个字符串中遇到'\0'时结束(哪个字符串先达到'\0',就有谁决定n)，
 * 按照上面的比较准则，
 *  "ABC"比"abc"小，"ABCD"比"ABC"大(长度不同时,长的比短的大)，"123A9"比"123B2"小。(长度相同时,第一个不同的高位决定大小的结果,可以把字符串当作16进制数来比较)
 *
 * strncmp的比较结束条件是：要么在其中一个字符串中遇到'\0'结束（类似于strcmp），要么比较完n个字符结束（类似于memcmp）。
 * 例如，strncmp("ABCD", "ABC", 3)的返回值是0，
 * strncmp("ABCD", "ABC", 4)的返回值是正值。
 *
 * */