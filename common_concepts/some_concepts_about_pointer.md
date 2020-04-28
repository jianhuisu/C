## 关于指针的一些重要知识点

### 指针中的一个`1`代表什么

    #include <stdio.h>

    int main(void)
    {
        int a = 1;
        int * p = &a;
        int * p2;
        p2 = p+1;
        //*p++;
        printf("p2 : %p , p : %p",p2,p);
        return 0;
    }

编译运行结果

    /home/sujianhui/CLionProjects/C/cmake-build-debug/test
    p2 : 0x7ffd423a3cd0 , p : 0x7ffd423a3ccc

p2与p的值之间相差(16 - 12)个字节,所以指针中的一个`1`代表1`Byte`,而不是1`bit`