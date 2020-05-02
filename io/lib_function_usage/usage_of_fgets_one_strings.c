#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    char path[] = "/home/sujianhui/CLionProjects/C/a_test/example.txt";
    FILE * fp;

    if( (fp = fopen(path,"r+"))  == NULL){
        perror(path);
        exit(EXIT_FAILURE);
    }

    char buf[5];
    while( fgets(buf,5,fp) !=  NULL ){
        // 自动在每一次输出的结尾添加'\n'
        // puts(buf);

        // 不在每一次输出后自动添加'\n' 对于fgets 来讲 只有 '\0' 是特殊字符
        fputs(buf,stdout);
    }
    printf("heihei");
    fclose(fp);
    return 0;
}

/*
    example.txt 内容 5678asdfasf

    // 使用 puts的输出结果
    /home/sujianhui/CLionProjects/C/cmake-build-debug/test
    5678
    asdf
    asf

    heihei


    // 使用 fputs的输出结果
    /home/sujianhui/CLionProjects/C/cmake-build-debug/test
    5678asdfasf
    heihei

    所以函数配套使用是非常重要的!!!
 */