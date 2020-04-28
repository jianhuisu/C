## 程序的编译 链接与装入

内存(内存条) 掉电 数据丢失  
外存（硬盘） 掉电 数据存在

主存储器别名：
	内存
	主存
	可执行存储器

### 计算机系统存储器多层结构


todo 寄存器的字长
todo 同一个名词使用在不同的场景中 具有不同的意义

磁盘中的数据必须先load到主存才可以使用
同样 数据必须先load到主存 才可以输出到辅存


### 2 程序的链接

目前 程序的链接分为三种方式 
    
    静态链接
    装入时动态链接  装入时将所有模块都进行链接
    运行时动态链接  运行时只链接需要的模块        比如 错误处理模块 如果程序运行过程中 没有发生错误 那么这个模块就是无用的

###  3 relocation 

装入时对目标程序中指令和数据地址的修改过程称为重定位


程序运行的顺序是 （编译 链接 装入 ， 链接在装入之后）

装入的方式有三种 

    绝对装入方式  : 编译后产生绝对的物理地址, 只允许将程序装载到内存中的固定位置  适合单道程序
    可重定位装入方式 : 允许将程序程序装载到内存中的固定位置 ，但是 进程经过换入换出后 , 在内存中的物地址不能发生移动, 进程装入后确定物理地址 
    动态运行时的装入方式 ： 允许进程换入换出后改变物理地址 逻辑地址与物理地址的转换发生在 进程从就绪态转化到执行态 ，进程装载所有的地址仍然时 逻辑地址 


各数据地址 ，指令地址 都是根据目标的起始地址经过偏移计算(offset sum)得出
装入后 逻辑地址被转化为物理地址

地址变换通常是在进程装入时一次完成,以后不再改变 ，所以称为 静态重定位

动态运行的装入程序在把装入模块装入内存后,并不立即把装入模块中的`逻辑地址`转化为`物理地址`
(
所以 编译产生的目标文件中的地址都是逻辑地址 其起始地址都是从逻辑地址上的 0x000000000000 开始
其中 每个段的地址都是相对于起始地址计算的
) 如下_

    
    [guangsu@xuwei 10:36:15 ~/CLionProjects/Test]$gcc -c main.c -o main.o
    [guangsu@xuwei 10:36:15 ~/CLionProjects/Test]$objdump -dS main.o
    
    main.o:     file format elf64-x86-64
    
    Disassembly of section .text:
    
    0000000000000000 <swap>:
       0:   55                      push   %rbp
       1:   48 89 e5                mov    %rsp,%rbp
       4:   48 89 7d e8             mov    %rdi,-0x18(%rbp)
       ...
      30:   c3                      retq   
       ...
    
    0000000000000031 <main>:
      31:   55                      push   %rbp
      32:   48 89 e5                mov    %rsp,%rbp
      35:   48 83 ec 40             sub    $0x40,%rsp
      39:   89 7d cc                mov    %edi,-0x34(%rbp)
      ...
      dd:   c9                      leaveq 
      de:   c3                      retq   

对完成`编译链接`的a.out 进行反汇编(汇编指令有删减,只须观察segment的起始地址变化)

    [guangsu@xuwei 10:41:01 ~/CLionProjects/Test]$objdump -dS a.out 
    
    a.out:     file format elf64-x86-64
    
    
    Disassembly of section .init:
    
    00000000004003e0 <_init>:
      4003e0:	48 83 ec 08          	sub    $0x8,%rsp
      4003e4:	48 8b 05 0d 0c 20 00 	mov    0x200c0d(%rip),%rax        # 600ff8 <__gmon_start__>
      4003f9:	c3                   	retq   
    
    Disassembly of section .plt:
    
    0000000000400400 <.plt>:
      400400:	ff 35 02 0c 20 00    	pushq  0x200c02(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
      400406:	ff 25 04 0c 20 00    	jmpq   *0x200c04(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
      40040c:	0f 1f 40 00          	nopl   0x0(%rax)
    
    0000000000400410 <printf@plt>:
      400410:	ff 25 02 0c 20 00    	jmpq   *0x200c02(%rip)        # 601018 <printf@GLIBC_2.2.5>
      400416:	68 00 00 00 00       	pushq  $0x0
      40041b:	e9 e0 ff ff ff       	jmpq   400400 <.plt>
    
    0000000000400420 <__libc_start_main@plt>:
      400420:	ff 25 fa 0b 20 00    	jmpq   *0x200bfa(%rip)        # 601020 <__libc_start_main@GLIBC_2.2.5>
      400426:	68 01 00 00 00       	pushq  $0x1
      40042b:	e9 d0 ff ff ff       	jmpq   400400 <.plt>
    
    0000000000400430 <__gmon_start__@plt>:
      400430:	ff 25 f2 0b 20 00    	jmpq   *0x200bf2(%rip)        # 601028 <__gmon_start__>
      400436:	68 02 00 00 00       	pushq  $0x2
      40043b:	e9 c0 ff ff ff       	jmpq   400400 <.plt>
    
    Disassembly of section .text:
    
    0000000000400440 <_start>:
      400440:	31 ed                	xor    %ebp,%ebp
      400442:	49 89 d1             	mov    %rdx,%r9
      40046a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    
    0000000000400470 <deregister_tm_clones>:
      400470:	b8 3f 10 60 00       	mov    $0x60103f,%eax
      400475:	55                   	push   %rbp
      400497:	ff e0                	jmpq   *%rax
      400499:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    
    00000000004004a0 <register_tm_clones>:
      4004a0:	b8 38 10 60 00       	mov    $0x601038,%eax
      4004a5:	55                   	push   %rbp
      4004d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    
    00000000004004e0 <__do_global_dtors_aux>:
      4004e0:	80 3d 4d 0b 20 00 00 	cmpb   $0x0,0x200b4d(%rip)        # 601034 <_edata>
      4004fc:	0f 1f 40 00          	nopl   0x0(%rax)
    
    0000000000400500 <frame_dummy>:
      400500:	48 83 3d 18 09 20 00 	cmpq   $0x0,0x200918(%rip)        # 600e20 <__JCR_END__>
      400507:	00 
    
    000000000040052d <swap>:
      40052d:	55                   	push   %rbp
      40052e:	48 89 e5             	mov    %rsp,%rbp
      40055c:	5d                   	pop    %rbp
      40055d:	c3                   	retq   
    
    000000000040055e <main>:
      40055e:	55                   	push   %rbp
      400676:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
      40067d:	00 00 00 
    
    0000000000400680 <__libc_csu_fini>:
      400680:	f3 c3                	repz retq 
    
    Disassembly of section .fini:
    
    0000000000400684 <_fini>:
      400684:	48 83 ec 08          	sub    $0x8,%rsp
      400688:	48 83 c4 08          	add    $0x8,%rsp
      40068c:	c3                   	retq   


## 存储管理方式 

操作系统在内存的低址部分 用户程序在内存地址的高址部分  ， 这就相当于 君住长江头 我住长江尾 日日思君不见君 共饮长江水

查看某个进程的逻辑地址空间
然后用cat /proc/29977/maps命令查看它的虚拟地址空间
用pmap 29977命令也可以得到类似的输出结果


操作系统在内存的高地址还是低地址?

从物理内存地址而言，一般都是放在低地址。
从虚拟内存地址而言，一般都是放在高地址。


todo 
