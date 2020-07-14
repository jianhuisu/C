## 位数组

#### 位数组的概念

所谓的位数组，主要是为了有效地利用内存空间而设计的一种存储数据的方式。在这种结构中一个整数在内存中用一位`1 bit`表示。
**这里所谓的表示就是如果整数存在，相应的二进制位就为`1`，否则为`0`**.

主要思想：

我们知道一个`char`类型的数据在内存中占用`1Byte`即`8 bit`，如果我们**用二进制位在内存中的顺序**来代表整数则可以存储更多的信息.
这样的话，一个`char`类型可以存储`8`个整数。假设`a`是一个`char`数组的话，整数8就可以用`a[1]`的第一个二进制位表示了.

例如:使用`512`字节表示`4096`个整数.

    512Bytes =>  512 * 8 => 4096 bits  如果整数存在，相应的二进制位就为`1`，否则为`0` 
    
    第一位代表整数 0
    第二位代表整数 1
    第三位代表整数 2
    ...
    第4096位代表整数 4095

这样我们就可以用`512`字节存储`4096`个数了，大大的节省了内存空间。

#### 利用`char`数组构造一个二进制数组

###### 将一个整数添加到二进制数组中

    /* num代表要插进数组中的数 */
    void add_to_bitarray(char *bitarr, int num){   
        /* MASK 为 0x7 */
        bitarr[num >> SHIFT] |= (1 << (num & MASK));  
    }
    
该方法的主要作用是将二进制数组中表示该整数的位置为`1`。首先我们得找到该整数位于`char`数组的第几个`组`中，这里利用该整数除以`8`即可（代码中除以8用右移三位实现）.
例如整数`25`位于`25/8 = 3 余 1`，表明该整数是用`char`数组的`第四个元素`的`第二位`表示.
那么在该元素的第几位可以利用该整数的后三位表示（`0~7`刚好可以表示`8`个位置），即 `25 & 0x7 = 1`，则代表`25`在该元素的第二位。
将相应位置`1`，可以先将整数1左移相应位数，然后与二进制数组进行或操作即可。

###### 判断一个整数是否在二进制数组中

    int is_in_bitarray(char *bitarr, int num){
        return bitarr[num >> SHIFT] & (1 << (num & MASK));
    }

先找到该整数在二进制数组中的位置，然后判断该位是否为1，若是则表示该整数位于二进制数组中，反之不在数组中。

###### 删除二进制数组中的一个整数

    void clear_bitarray(char *bitarr, int num){
        bitarr[num >> SHIFT] &= ~(1 << (num & MASK));
    }

思路相同，先找到该整数在二进制数组中的位置，然后将该位置为0即可。

###### 完整demo

    #include <stdio.h>  
    #include <stdlib.h>  
    #include <string.h>  
    #define SHIFT 3  
    #define MASK 0x7  
    
    char *init_bitarray(int);
    void add_to_bitarray(char *, int);
    int is_in_bitarray(char *, int);
    void clear_bitarray(char *, int);
    void test(char *);
    
    int main(){
    	char *arr;
    
    	arr = init_bitarray(100);
    	add_to_bitarray(arr, 25);
    	test(arr);
    	clear_bitarray(arr, 25);
    	test(arr);
    	getchar();
    	return 0;
    }
    
    char *init_bitarray(int size){
    	char *tmp;
    
    	tmp = (char*)malloc(size / 8 + 1);
    	memset(tmp, 0, (size / 8 + 1)); //initial to 0  
    
    	return tmp;
    }
    
    void add_to_bitarray(char *bitarr, int num){   /* num代表要插进数组中的数 */
    	bitarr[num >> SHIFT] |= (1 << (num & MASK));
    }
    
    int is_in_bitarray(char *bitarr, int num){
    	return bitarr[num >> SHIFT] & (1 << (num & MASK));
    }
    
    void clear_bitarray(char *bitarr, int num){
    	bitarr[num >> SHIFT] &= ~(1 << (num & MASK));
    }
    
    void test(char *bitarr){
    
    	if (is_in_bitarray(bitarr, 25) != 0)
    		printf("25 in\n");
    	else
    		printf("25 not in\n");
    	if (is_in_bitarray(bitarr, 30) != 0)
    		printf("30 in\n");
    	else
    		printf("30 not in\n");
    }
    

#### 总结

当判断`1-n`个数中是否存在重复数字时,就可以构建一个容纳`(n-1)/8`个`char`的位数组.来解决大数据的查重，判断问题.    
    
#### 参考资料

原文链接：https://blog.csdn.net/qq_37375427/article/details/79797359