## 变量的存储布局

两种内存分配方式

 - 静态内存分配 由系统自动分配内存，由系统自动释放。静态内存是在栈中分配的.
 - 动态内存分配 进程结束自动释放/或者由程序员手动分配释放

C/C++可执行文件的内存布局

 - `.bss segment` 未初始化的全局数据,静态数据. 该段属于静态内存分配
 - `.data segment` 已初始化的全局变量. 该段属于静态内存分配
 - `.code segment / text segment` 通常用来存放程序代码以及一些只读的常数变量,比如`"234353454"` 
 - `heap`  存储使用`malloc()`分配的变量. 该段属于动态内存分配
 - `stack` 存储局部变量,使用`static`声明的局部变量存储在`data segment`.

### 实例 
    
example. `main.c`
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int global = 0;       // 全局初始化区域
    char * p1;            // 全局未初始化区域
    
    int main(void)
    {
        int a;               // 栈空间
        char s[] = "abcdefg";// 栈空间
        char * p2;           // 栈空间
        
        char *p3 = "1234567890";  // "1234567890" 在常量区 p3在栈上
        static int c = 0;         // 全局静态初始化区
        
        p1 = (char * )malloc(100 * sizeof(char));  // 申请的100字节 属于堆空间
        p2 = (char *)malloc(200 * sizeof(char));   // 申请 200字节属于堆空间
        
        strcpy(p1,"123456789");  
        
        return 0;
    }
    
查看可执行文件
    
    readelf -a a.out | grep -B3 -A100 'Symbol table'

#### 内存泄露与内存溢出

 - 内存泄露 失去对内存的控制导致其无法释放.一般指堆空间内存泄露.
 - 内存溢出 缓冲区填充数据超过缓冲区容量,溢出数据可能覆盖合法数据而造成安全隐患.

### 参考资料

http://akaedu.github.io/book/ch19s03.html

