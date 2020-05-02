#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char path[] = "/home/sujianhui/CLionProjects/C/a_test/example.txt";

    // 在打开一个文件时如果出错，fopen将返回NULL并设置errno
    FILE * fd = fopen(path,"w");
    if( fd == NULL ){
        printf("errno :%d \n",errno);
        fputs("open error",stderr);
        printf("%s \n",path);
        perror(path,);
        printf("errno :%d \n",errno);
        exit(EXIT_FAILURE);
    }else{
        printf("open success \n");
    }

    // 如果fclose调用出错（比如传给它一个无效的文件指针）则返回EOF并设置errno
    // fopen调用应该和fclose调用配对，打开文件操作完之后一定要记得关闭。如果不调用fclose，在进程退出时系统会自动关闭文件，
    // 但是不能因此就忽略fclose调用，如果写一个长年累月运行的程序（比如网络服务器程序），打开的文件都不关闭，堆积得越来越多，就会占用越来越多的系统资源。
    // 换句话说 可能某天你封装的函数就会在常驻内存程序中引用,显然,如果你成对使用fopen/fclose，你就可以放心的引用了.
    fclose(fd);
    return 0;
}
