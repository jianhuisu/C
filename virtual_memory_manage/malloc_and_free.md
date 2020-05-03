## malloc相关知识点

`C99`引入`VLA`特性，可以定义`char buf[n+1] = {};`，这样可确保`buf`是以`'\0'`结尾的。
但即使用`VLA`仍然不够灵活，`VLA`是在`栈上`动态分配的，函数返回时就要释放，如果我们希望动态分配一块全局的内存空间，在各函数中都可以访问呢？
由于全局数组无法定义成`VLA`，所以仍然不能满足要求。

进程有一个堆空间，C标准库函数`malloc`可以在堆空间动态分配内存，它的底层通过`brk`系统调用向操作系统申请内存。
动态分配的内存用完之后可以用`free`释放，更准确地说是归还给`malloc`，这样下次调用`malloc`时这块内存可以再次被分配。

`malloc`触发了一次系统调用，从系统中申请了`4k`内存，而`free`只是在应用层进行了释放，
没有触发系统调用，而没有向系统归还这`4k`.下次如果再次`malloc 4k`以内的内存，这块内存会被应用层重用，也不会触发系统调用了.

#### 什么是内存泄漏(Memory Leak)?
 
一个简单的顺序控制流程，分配内存，赋值，打印，释放内存，退出程序。
这种情况下即使不用`free`释放内存也可以，**因为程序退出时整个进程地址空间都会释放，包括`堆空间`，该进程占用的所有内存都会归还给操作系统**。
但如果一个程序长年累月运行（例如网络服务器程序`常驻内存应用`），并且在循环或递归中调用`malloc`分配内存，则必须有`free`与之配对，分配一次就要释放一次，
否则每次循环都分配内存，分配完了又不释放，就会慢慢耗尽系统内存，这种错误称为内存泄漏（`Memory Leak`）.
另外,`malloc`返回的指针一定要保存好，只有把它传给`free`才能释放这块内存，如果这个指针丢失了，就没有办法`free`这块内存了，也会造成内存泄漏.
内存泄漏的`Bug`很难找到，因为它不会像访问越界一样导致程序运行错误，少量内存泄漏并不影响程序的正确运行，
大量的内存泄漏会使系统内存紧缺，导致频繁换页，不仅影响当前进程，而且把整个系统都拖得很慢.
**读者只要理解了基本工作原理，就很容易分析在使用malloc和free时遇到的各种Bug了。**
下面是一个会产生内存泄露的`demo`.

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    int main(void)
    {
        typedef struct{
            int length;
            char *name;
        }u_t;
    
        int c = 1;
    
        //while(c<100){
        while(c){
    
            u_t * ptr = malloc(sizeof(u_t));
    
            if(ptr != NULL ){
                ptr->length = c;
                ptr->name = malloc(1000);
                strcpy(ptr->name,"hello");
                printf("malloc 1000 bytes ; number : %d , name : %s \n",ptr->length,ptr->name);
    
    // 如果把释放内存操作注释 那么会造成内存泄露            
    //            free(ptr->name);
    //            free(ptr);
    //            ptr = NULL;
                c++;
            } else {
                printf("out of memory,total use %u bytes \n",1000 * c );
                exit(1);
            }
    
        }
    
        return 0;
    }


`ps aux | grep server_name | xargs top -p`可以监测到内存使用量持续攀升,直到进程崩溃. 

### 其它的内存分配函数

分配内存的函数
除了`malloc`之外，C标准库还提供了另外两个在`堆空间分配内存`的函数，它们分配的内存同样由`free`释放。

    #include <stdlib.h>
    
    void *calloc(size_t nmemb, size_t size);
    void *realloc(void *ptr, size_t size);
    返回值：成功返回所分配内存空间的首地址，出错返回NULL
    
`calloc`的参数很像`fread/fwrite`的参数，分配`nmemb`个元素的内存空间，每个元素占`size`字节，并且`calloc`负责把这块内存空间用字节0填充，
    而`malloc`并不负责把分配的内存空间清零.

有时候用`malloc`或`calloc`分配的内存空间使用了一段时间之后需要改变它的大小，一种办法是调用`malloc`分配一块新的内存空间，把原内存空间中的数据拷到新的内存空间，
然后调用`free`释放原内存空间。使用`realloc`函数简化了这些步骤，把原内存空间的指针`ptr`传给`realloc`，通过参数`size`指定新的大小（字节数），
`realloc`返回新内存空间的首地址，并释放原内存空间。新内存空间中的数据尽量和原来保持一致，如果`size`比原来小，则前`size`个字节不变，
后面的数据被截断，如果`size`比原来大，则原来的数据全部保留，后面长出来的一块内存空间未初始化（`realloc`不负责清零）。

注意：参数`ptr`要么是`NULL`，要么必须是先前调用`malloc`、`calloc`或`realloc`返回的指针，不能把任意指针传给`realloc`要求重新分配内存空间.

#include <alloca.h>

void *alloca(size_t size);
返回值：返回所分配内存空间的首地址，如果size太大导致栈空间耗尽，结果是未定义的
参数size是请求分配的字节数，alloca函数不是在堆上分配空间，而是在调用者函数的栈帧上分配空间，类似于C99的变长数组，当调用者函数返回时自动释放栈帧，所以不需要free。这个函数不属于C标准库，而是在POSIX标准中定义的。

### 参考资料

http://akaedu.github.io/book/ch24s01.html#interface.prereq