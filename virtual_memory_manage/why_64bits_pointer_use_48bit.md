## 为什么64位的机器上,打印指针只有48位宽


#### 背景

64位机器上 C语言指针变量的值为 宽度为12位 `0x7ffd3cb1d9b4` , 
而使用`objdump`反汇编得出的可执行程序分段地址都是 `0x00000000004003e0` 这样，这是为什么？？？

这个让我抓狂的问题在知乎得到了解决(之前我一直搜索为什么指针只用12位，结果寥寥无几,后来换了关键词,为什么指针只用48位，结果立刻闪现),
下面是回答正文.

#### 回答

假定题主问的只是AMD64。Intel版叫做Intel® 64，是从AMD交叉授权来的AMD64；
Intel® 64曾用名EM64T。当前版本的AMD64架构就规定了只用48位地址；
**一个表示虚拟内存地址的64位指针只有低48位有效并带符号扩展到64位**
换句话说，其高16位必须是全1或全0(就是地址从左向右开始数的前16位),而且必须与低48位的最高位（第47位）一致，(注释: 左高右低) 
    
    4bits     10bits      10bits       10bits      10bits     10bits     10bits
    1111     1111111111 11[1]0000000 0000000000 0000000000 0000000000 0000000000   
                          第47位
                          右边是低48位
                          
否则通过该地址访问内存会产生#GP异常（general-protection exception）。

只用48位的原因很简单：

    因为现在还用不到完整的64位寻址空间，所以硬件也没必要支持那么多位的地址。
    
设计为带符号扩展的原因也很简单：

    很多环境中，寻址空间的高一半（higher-half）有特殊用途，而低一半（lower-half）给用户做一般用途。
    
这“高/低”可以通过最高位是1还是0来判断；
如果把地址看成带符号整数，那么“负数”部分就是高一半，“正数”部分就是低一半。
所以AMD64在设计成只用64位中的48位时，要求canonical form要满足带符号扩展的要求。
以后就算允许更多位地址，满足当前限制的地址也仍然会是合法地址，保证了向前兼容性。
这些限制都只是临时的。以后真的需要的时候可以放宽到56位，最终状态就会扩展到真正的完整64位吧。

其它64位CPU架构未必有一样的限制。SPARC的64位版就允许完整的64位寻址空间。AArch64允许用高8位来做tag，
那么还有56位寻址空间。既然题主问的是48位那多半是AMD64吧

原文链接: https://www.zhihu.com/question/28638698/answer/41603886

#### extend question 
    
    void main():
    struct node * new_node = (struct node *)malloc(sizeof( struct node));
    int a = 1;
    printf("stack ptr value  %p \n",&a);
    printf("heap ptr value:  %p \n",new_node);

o ? why pointer length is not equal ?
    
    [sujianhui@dev529 linked_list]$>gcc reverse.c && ./a.out 
    success 0xc3f010 
    stack ptr value  0x7ffc3c941d4c          => 12 * 4 = 48 bit 
    heap ptr value:  0xc3f030                =>  6 * 4 = 24 bit
    
    

### 小结

内存芯片上通过电容矩阵来存储数据
硬盘上通过磁性物质来存储数据