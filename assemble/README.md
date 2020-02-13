汇编文件 hello.s

.section .data
.section .text
.global _start
    // instruction
start:

汇编，链接

    as hello.s -o hello.o
    ld hello.o -o hello

寻址方式

ADDRESS_OR_OFFSET(%BASE_OR_OFFSET,%INDEX,MULTIPLIER)
它所表示的地址可以这样计算出来：
FINAL ADDRESS = ADDRESS_OR_OFFSET + BASE_OR_OFFSET + MULTIPLIER * INDEX

ADDRESS_OR_OFFSET和MULTIPLIER必须是常数，
BASE_OR_OFFSET和INDEX必须是寄存器。
在有些寻址方式中会省略这4项中的某些项，相当于这些项是0。其中ADDRESS_OR_OFFSET和MULTIPLIER必须是常数，BASE_OR_OFFSET和INDEX必须是寄存器。在有些寻址方式中会省略这4项中的某些项，相当于这些项是0。

    直接寻址（Direct Addressing Mode）。只使用ADDRESS_OR_OFFSET寻址，例如movl ADDRESS, %eax把ADDRESS地址处的32位数传送到eax寄存器。

    变址寻址（Indexed Addressing Mode） 。上一节的movl data_items(,%edi,4), %eax就属于这种寻址方式，用于访问数组元素比较方便。

    间接寻址（Indirect Addressing Mode）。只使用BASE_OR_OFFSET寻址，例如movl (%eax), %ebx，把eax寄存器的值看作地址，把内存中这个地址处的32位数传送到ebx寄存器。注意和movl %eax, %ebx区分开。

    基址寻址（Base Pointer Addressing Mode）。只使用ADDRESS_OR_OFFSET和BASE_OR_OFFSET寻址，例如movl 4(%eax), %ebx，用于访问结构体成员比较方便，例如一个结构体的基地址保存在eax寄存器中，其中一个成员在结构体内的偏移量是4字节，要把这个成员读上来就可以用这条指令。

    立即数寻址（Immediate Mode）。就是指令中有一个操作数是立即数，例如movl $12, %eax中的$12，这其实跟寻址没什么关系，但也算作一种寻址方式。

    寄存器寻址（Register Addressing Mode）。就是指令中有一个操作数是寄存器，例如movl $12, %eax中的%eax，这跟内存寻址没什么关系，但也算作一种寻址方式。在汇编程序中寄存器用助记符来表示，在机器指令中则要用几个Bit表示寄存器的编号，这几个Bit也可以看作寄存器的地址，但是和内存地址不在一个地址空间。

ELF文件有三种类型
    可执行文件
    可重定为目标文件
    共享库文件

常用工具：
    readelf 查看目标文件 或者 可执行文件的分段信息
        readelf -a main.o
    objdump 反汇编工具   查看目标文件与可执行文件的汇编代码
        objdump -d main.o


