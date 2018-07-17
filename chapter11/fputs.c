#include <stdio.h>
#define LEN 40
void main(void)
{

    char words1[LEN];
    char words2[LEN];
    char words3[LEN];

    scanf("%s",words1); // 只能读取一个单词
    printf("%s\n",words1);
    gets(words2); // 可以读取一行数据 直到遇到换行符 丢弃换行符 存储其余字符 并在字符串末尾添加空字符
    puts(words2); // 输出时  自动在字符串末尾添加 换行符 遇到空字符停止输出 否则一直运行
    printf("%s",words2);

    fgets(words3,LEN,stdin);
    fputs(words3,stdout);


}
#if 0
/tmp/ccqZLrC2.o: In function `main':
fputs.c:(.text+0x38): warning: the `gets' function is dangerous and should not be used.  // gets 函数无法检查 数组是否可以容纳 输入字符串 溢出后容易擦除数据
hello world
hello
 world
 worldwodehaishi wod
wodehaishi wod

#endif
