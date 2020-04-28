## pointer 


### 野指针

    // error:
	int main(void)
	{	
		int *p;
		...
		*p = 0;
		...
	}

堆栈上的初始值是不确定的,`*ip`对应内存单元可能存储任何值(声明指针并不像声明int一样,会自动初始化所在的内存单元),
如果我们紧接着对未初始化的指针进行引用赋值操作`*p=0`,谁知道这会修改哪一块的内存数据,所以,为了避免出现野指针,在定义指针变量时就应该给它明确的初始值,或者时NULL

	// right:
	#include <stddef.h>

	int main()
	{
		int a = 1;
		int *p = &a;
		
		// 或者
		int *pc = NULL
		*pc = 1;
	}

### 指针的计算问题

	

	#include <stdio.h>

	int main(int argc ,char **argv)
	{
	    int a[10] ={1,2,3,4,5,6,7,8,9};
	    int i = 0;
	
	    for(i=0;i<10;i++){
	        printf("%4d , address : %p \n ",a[i],&a[i]);
	    }
	
	    int *p = a;
	
	    printf("%p , address : %p \n ",a,&a[0]);
	    printf("%p , address : %p \n ",p++,&a[0]);
	    printf("%p , address : %p \n ",p,&a[0]);
	
	    printf("%d \n",sizeof(int));
	
	    return 0;
	}


print

	/home/guangsu/CLionProjects/Test/cmake-build-debug/Test
	    1 , address : 0x7fff67e1d720 
	    2 , address : 0x7fff67e1d724 
	    3 , address : 0x7fff67e1d728 
	    4 , address : 0x7fff67e1d72c 
	    5 , address : 0x7fff67e1d730 
	    6 , address : 0x7fff67e1d734 
	    7 , address : 0x7fff67e1d738 
	    8 , address : 0x7fff67e1d73c 
	    9 , address : 0x7fff67e1d740 
	    0 , address : 0x7fff67e1d744 
	 0x7fff67e1d720 , address : 0x7fff67e1d720 
	 0x7fff67e1d720 , address : 0x7fff67e1d720 
	 0x7fff67e1d724 , address : 0x7fff67e1d720 
	 4 


eg.2 

    #include <stdio.h>
    
    int main(void)
    {
        printf("int: %d , char : %d \n",sizeof(int),sizeof(char));
    
        int a = 1;
        int * pi = &a;
    
        char  b = 'A';
        char * pc = &b;
        
        // 指针+1 操作 实质为 当前指针地址 + 1 * （指针类型所占字节数）
        printf("int origin value is %p , char origin value is %p \n",pi,pc);
        printf("int after+ value is %p , char after+ value is %p \n",++pi,++pc);
    }

print 

    /home/sujianhui/CLionProjects/C/cmake-build-debug/test
    int: 4 , char : 1 
    int origin value is 0x7ffe6d29de5c , char origin value is 0x7ffe6d29de5b 
    int after+ value is 0x7ffe6d29de60 , char after+ value is 0x7ffe6d29de5c 
    
    Process finished with exit code 0

使用 *p 去访问时，编译后的汇编指令寻址时 应该会从指针指向地址开始 ，偏移（指针类型 占用字节大小）N个字节后结束，这一区间内的内存单元 就是变量值所在区域.

C 如何查看int占用几个字节

	sizeof(int)
	sizeof(char)

1 个字节（Byte）等于 8 个位（bit）似乎已经是程序员间的常识了，很少有人质疑这一点。
但是作为C语言程序员，我们常常要在不同的硬件平台上做底层开发，应该明白：1个字节等于8个位只是惯例而已，C标准并没有定义这一点。有些编译器并不遵守这个惯例.
**字节通常简写为“B”，而位通常简写为小写“b”**

### 指针的初始化

注意pi和pc虽然是不同类型的指针变量，但它们的内存单元都占4个字节，因为要保存32位的虚拟地址，同理，在64位平台上指针变量都占8个字节。

    int i;
    int *pi = &i;
    char c;
    char *pc = &c;

用一个指针给另一个指针赋值时要注意，两个指针必须是同一类型的。在我们的例子中，pi是int *型的，pc是char *型的，pi = pc;这样赋值就是错误的。但是可以先强制类型转换然后赋值：

    pi = (int *)pc;

现在pi指向的地址和pc一样，但是通过`*pc`只能访问到一个字节，而通过`*pi`可以访问到4个字节，后3个字节已经不属于变量c了,此时进行指针类型转化，
其实相当于把`*pc`能访问到的一个字节与紧跟其后的3个字节划分为 `*pi`可以访问的区间，这种方式很危险，不推荐甚至应该禁止这种赋值方式.

### 通用指针 void * 

ANSI在将C语言标准化时引入了`void *`类型，`void *`指针与其它类型的指针之间可以隐式转换，而不必用类型转换运算符。注意，只能定义`void *`指针，
而不能定义void型的变量，因为`void *`指针和别的指针一样都占4个字节，而如果定义void型变量（也就是类型暂时不确定的变量），
编译器不知道该分配几个字节给变量。同样道理，`void *`指针不能直接Dereference，而必须先转换成别的类型的指针再做Dereference(根据指针找到变量称为Dereference)。
 

#### const 

    #include <stdio.h>
    
    int main(int argc ,char **argv)
    {
    
        int a = 1;
        int b = 2;
        
        // pointer variable p is read-only , so p =&b is error  , *p=3 is right
        int * const p = &a; 
        
        // pointer reference address is read-only , so pointer variable can modify( right: p1 = &b ) ,
        // but the value pointer reference can not modify( error: *p1=3 )
        int const *p1 = &a;
        
        // p2 variable can not modify , *p2 also can not modify
        int const * const p2 = &a;   
        
        return 0;
    }


即使不用const限定符也能写出功能正确的程序，但良好的编程习惯应该尽可能多地使用const，因为：

 - const 提升代码的可读性
 - 尽可能多地使用const限定符，把不该变的都声明成只读，这样可以依靠编译器检查程序中的Bug，防止意外改写数据。
 - const对编译器优化是一个有用的提示，编译器也许会把const变量优化成常量。












todo 

我们知道，调用函数的传参过程相当于用实参定义并初始化形参，swap(&i, &j)这个调用相当于

char name='A'
&name => 0x7ffce3e36e1f

pointer var's value is 48bits address(12 position hex number equal 48 bits)  / why ?
so 6(48/8) bytes this char pointer var occupied 


内存地址是12位16进制数，那么对应的指针需要多少字节？
例如（对变量取址得到的）：0x7fff5ced2e5c;
那么就是12个4位的2进制数，就是48位的2进制数，48/8 = 6，那就是6个字节可以表示48位的2进制数。但是我储存一个指针（利用sizeof求得）需要8字节，另外两个字节我推测是用来存储这个指针所指变量的长度。
例如 int 的指针 p，使用 p+1， 则对应的地址偏移4个字节。
>>>
我的问题是，我上面一堆话说得对吗？
此外，我是非专业的业余爱好者，所以请不要鄙视我不懂某些基础知识。

指针是8字节没问题，但另两个字节也是地址的组成部分，并无它用。可以这样想，在windows系统上，如果你对函数临时变量取值，
很可能得到0x13ff58这样一个6位16进制数地址(3 bytes)，那么剩下5个字节都做其它用了吗？
地址数值只有48位是表像，实际上它是64位的地址，这是当前的x86_64处理器硬件限制所致。
因为目前面世的x86_64处理器的地址线只有48条，硬件要求传入的地址的48到63位必须与47位相同。
因此有两段合法的地址空间，
最直观的是0 - 0x00007fff ffffffff，另
一段是0xffff8000 00000000 - 0xffffffff ffffffff。
两段加在一起一共2^48 = 256TB，

这就是当前处理器的寻址能力。
但一般我们是见不到第二段地址的，因为操作系统一般使用低段地址，
高段这部分需要你的机器至少有128TB以上的内存。()

、分页地作业地址空间是维一地，即单一地线性空间，程序员只须利用一个记忆符，即可表示一地址. 
分段地作业地址空间是二维地，程序员在标识一个地址时，既需给出段名，又需给出段内地址.

memory manager 

1 段式存储管理
2 页式存储管理 
3 段页式存储管理  

虚拟地址空间和物理地址空间是独立的，32位处理器的虚拟地址空间是4GB，而物理地址空间既可以大于也可以小于4GB。
http://akaedu.github.io/book/ch17s04.html
32位处理器的页尺寸通常是4KB

通常操作系统把虚拟地址空间划分为用户空间和内核空间，
例如x86平台的Linux系统虚拟地址空间是 

    0x00000000~0xffffffff，
    前3GB（0x00000000~0xbfffffff）是用户空间，
    后1GB（0xc0000000~0xffffffff）是内核空间。
    
用户程序加载到用户空间，在用户模式下执行，不能访问内核中的数据，也不能跳转到内核代码中执行。
这样可以保护内核，如果一个进程访问了非法地址，顶多这一个进程崩溃，而不会影响到内核和整个系统的稳定性。
CPU在产生中断或异常时不仅会跳转到中断或异常服务程序，还会自动切换模式，从用户模式切换到特权模式，
因此从中断或异常服务程序可以跳转到内核代码中执行。事实上，整个内核就是由各种中断和异常处理程序组成的。

总结一下：在正常情况下处理器在用户模式执行用户程序，在中断或异常情况下处理器切换到特权模式执行内核程序，
处理完中断或异常之后再返回用户模式继续执行用户程序。


但是通过*pc只能访问到一个字节，而通过*pi可以访问到4个字节

you can full fix a box with water or air ,bu hard to fixed box full of gravels

box is a memory unit , gravel  is every bits value belong this unit 

