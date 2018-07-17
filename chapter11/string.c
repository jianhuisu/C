#include <stdio.h>
#define MAX_LEN 40
#define MSG "I'm pre define string"
main(void)
{
    char words[MAX_LEN] = "My name is sujianhui";
    const char *ptr = "My name is sujianhui";

    // puts('this is common string value')  单引号会将字符串转化为 int 类型 , 但是puts 接受 char 类型
    puts("this is common string value");
    puts(words);
    puts(ptr);
    puts(MSG);
    words[8] = 'A';
    puts(words);
}