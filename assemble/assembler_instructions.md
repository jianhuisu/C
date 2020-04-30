### 常用汇编指令标注

汇编指令有两种语法 

 - Windows也使用intel语法
 - UNIX平台的汇编器一直使用AT&T语法

下文为AT&T语法格式,其常规指令格式为 
    
    指令码 源操作数SRC,目的操作数DST ;注释
    movl $1,%eax # 产生一个立即数1,保存到寄存器eax中


##### mov   

一条数据传送指令

    `movl $1, %eax` 要求CPU内部产生一个数字1并保存到eax寄存器中.`mov`的后缀`l`表示`long`，说明是32位的传送指令.
    
##### int

`int`指令称为软中断指令，可以用这条指令故意产生一个异常.异常的处理和中断类似，CPU从用户模式切换到特权模式，然后跳转到内核代码中执行异常处理程序.

     # .eg 
     .section .data          
     .section .text       
        
         .globl _start
         _start:
                 movl $1,%eax
                 movl $4,%ebx
                 int $0x80
        
     
`int`指令中的立即数`0x80`是一个**参数**，(注释：一般的汇编指令都有两个参数,`int`指令比较特殊).在`kernel`的异常处理程序中要根据这个参数决定处理方式.
例如,在Linux内核中`int $0x80`这种异常称为系统调用`System Call`.
在调用结束之后，`CPU`切换回用户模式，继续执行`int$0x80`的下一条指令.

用户程序只能通过在寄存器中预存参数的方式向内核传递参数.寄存器`eax`和`ebx`的值是用户进程传递给系统调用的两个参数.

 - `eax`的值是系统调用号，Linux的各种系统调用都是由`int $0x80`令引发的，内核需要通过`eax`的值判断用户要调哪个系统调用，_`exit`的系统调用号是`1`.
 - `ebx`的值是传给`_exit`的参数，表示退出状态.大多数系统调用完成之后会返回用户空间继续执行后面的指令，而`_exit`系统调用比较特殊，它会终止掉当前进程，而不是返回用户空间继续执行.

##### cmpl

    start_loop:
     cmpl $0, %eax          # 
     je loop_exit           # jump if equal
     
`cmpl`指令将两个操作数相减，但计算结果并不保存，只是根据计算结果改变`eflags`(个人感觉`eflags`应该是`equal register flags`的缩写)寄存器中的标志位.
如果两个操作数相等，则计算结果为`0`，`eflags`中的`ZF`位置`1`.`je`(`jump if equal`)是一个条件跳转指令，
它检查`eflags`中的`ZF`位，`ZF`位为`1`则发生跳转，`ZF`位为`0`则不跳转，继续执行下一条指令.
可见比较指令和条件跳转指令是配合使用的.   

    cmpl %ebx, %eax
     jle start_loop         # jump if equal or less than
     
       