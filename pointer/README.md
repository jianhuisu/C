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

#### C指针的大小，是否是固定的

任何类型的指针变量所占用的内存空间都是4字节即32位,因此指针变量所占用的存储空间大小是一样的，指针变量存放的值都是一个32位的地址值。
但是不同类型的指针，在参与指针运算的时候是不同的。举例说明：

    int *p;
    char *ch;
    
 - `p+1`，假如p的值是`1000`，那么`p+1`的值是1004了，因为`int`类型是4字节的.这里的1代表 指向下一个int的地址,所以要+4字节.
 - `ch+1`，假如p的值是`1000`，那么`p+1`的值是1001了，因为`char`类型是1字节的。

> ye jiu shi shuo , zhi zhen shi zi dai lei xing de . bu tong lei xing zhi jian de zhi zhen bu ke yi  zhi jie yun suan. 

注意：指针可以进行 `==` `!=` 运算,但是不可以进行比较运算.



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