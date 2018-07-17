#include <stdio.h>

int main(int argc ,char *argv[])
//int main(int argc ,char **argv)   argv 是一个指针数组
{
    int count = 0;

    printf("the command line has %d arguments\n",argc - 1);

    for(count = 0; count < argc; count++)
    {
        printf("the %d arguments value is %s \n",count,argv[count]);
    }
    return 0;
}