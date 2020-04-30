# PURPOSE: This program finds the maximum number of a
#	  set of data items.
#
#VARIABLES: The registers have the following uses:
#
# %edi - Holds the index of the data item being examined
# %ebx - Largest data item found
# %eax - Current data item
#
# The following memory locations are used:
#
# data_items - contains the item data. A 0 is used
# to terminate the data
#
# VARIABLES :
#       %edi  存储遍历数组时，数组当前元素的索引
#       %eax  存储遍历数组时, 数组当前元素的值
#       %ebx  存储 遍历过的元素中的最大值

.section .data
data_items:
.long 3,67,34,222,45,75,54,34,44,33,22,11,66,0

.section .text
.globl _start
_start:
        movl $0,%edi                     # 存储数组下标索引值
        movl data_items(,%edi,4),%eax    # 将数组中第 edi 个元素的值 传送到 寄存器%eax中
        movl %eax,%ebx                   # 将寄存器%eax的值 发送到寄存器 %ebx

start_loop:
        cmpl $0,%eax                     # 遇到0元素时 终止循环
        je loop_exit
        incl %edi
        movl data_items(,%edi,4),%eax    # data_items 表示数组首元素的地址 是一个常数，
                                         # 指令的意思是 从data_items开始计算，
                                         # 偏移 %edi * 4 个字节处的数据 发送到寄存器 %eax 上

        cmpl %ebx,%eax                   # if(（%ebx - %eax）> 0 ){ jle start_loop} else {movl %eax,%ebx}
        jle start_loop

        movl %eax,%ebx
        jmp start_loop

loop_exit:
        movl $1,%eax
        int $0x80
