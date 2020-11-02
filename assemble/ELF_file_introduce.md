# ELF文件

可执行文件是需要在操作系统中运行的.就像游泳要去游泳馆,滑雪要去滑雪场一样.
可执行文件是要依赖于操作系统的,不同的操作系统下可执行文件的格式不同.

看一下ELF文件的生成步骤：

1. 汇编文件 ： 顺序化的汇编指令

	打开冰箱，
	把大象放进去
	关上冰箱
	...

2. 汇编文件经过汇编器转换生成目标文件.目标文件由多个section组成,就像yaf的配置文件一样.**目标文件并不是可执行文件.**
	
	[section1]
	application.libdir = ""
	[section2]
	appiid = ""
	[section3]
	...
	[section4]

比如说用汇编器`（Assembler）as`把汇编程序中的助记符翻译成`机器指令`(目标文件中就是机器指令,但是并不能被操作系统时别运行)，生成目标文件`hello.o`：

	$ as hello.s -o hello.o

为什么用汇编器翻译成机器指令了还不行，还要有一个链接的步骤呢？链接主要有两个作用:

 - 修改目标文件中的信息，对地址做重定位
 - 把多个目标文件合并成一个可执行文件(为了便于协作开发,程序可能分布在多个文件中).


3. 链接器将`一个或者多个`(为了便于协作开发,程序可能分布在多个文件中)目标文件中的section合并成为Segment.生成`一个`可执行文件.(可执行文件只能有一个).一个`Segment`由一个或多个`Section`组成.

用链接器（Linker，或Link Editor）ld把目标文件hello.o链接成可执行文件hello：

	$ ld hello.o -o hello

4. 加载器(Loader)根据可执行文件中的Segment信息加载运行这个程序.


我们使用readelf工具读取目标文件`hello.o`的`ELF header`与`Section Header Table`.

	[sujianhui@dev529 assemble]$>readelf -a hello.o 
	ELF Header:
	  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
	  Class:                             ELF64
	  Data:                              2's complement, little endian
	  Version:                           1 (current)
	  OS/ABI:                            UNIX - System V
	  ABI Version:                       0
	  Type:                              REL (Relocatable file)
	  Machine:                           Advanced Micro Devices X86-64
	  Version:                           0x1
	  Entry point address:               0x0
	  Start of program headers:          0 (bytes into file)
	  Start of section headers:          256 (bytes into file)
	  Flags:                             0x0
	  Size of this header:               64 (bytes)
	  Size of program headers:           0 (bytes)
	  Number of program headers:         0
	  Size of section headers:           64 (bytes)
	  Number of section headers:         7
	  Section header string table index: 6

	Section Headers:
	  [Nr] Name              Type             Address           Offset
	       Size              EntSize          Flags  Link  Info  Align
	  [ 0]                   NULL             0000000000000000  00000000
	       0000000000000000  0000000000000000           0     0     0
	  [ 1] .text             PROGBITS         0000000000000000  00000040
	       000000000000000c  0000000000000000  AX       0     0     1
	  [ 2] .data             PROGBITS         0000000000000000  0000004c
	       0000000000000000  0000000000000000  WA       0     0     1
	  [ 3] .bss              NOBITS           0000000000000000  0000004c
	       0000000000000000  0000000000000000  WA       0     0     1
	  [ 4] .symtab           SYMTAB           0000000000000000  00000050
	       0000000000000078  0000000000000018           5     4     8
	  [ 5] .strtab           STRTAB           0000000000000000  000000c8
	       0000000000000008  0000000000000000           0     0     1
	  [ 6] .shstrtab         STRTAB           0000000000000000  000000d0
	       000000000000002c  0000000000000000           0     0     1
	Key to Flags:
	  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
	  L (link order), O (extra OS processing required), G (group), T (TLS),
	  C (compressed), x (unknown), o (OS specific), E (exclude),
	  l (large), p (processor specific)

	There are no section groups in this file.

	There are no program headers in this file.

	There are no relocations in this file.

	The decoding of unwind sections for machine type Advanced Micro Devices X86-64 is not currently supported.

	Symbol table '.symtab' contains 5 entries:
	   Num:    Value          Size Type    Bind   Vis      Ndx Name
	     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
	     1: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
	     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    2 
	     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
	     4: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT    1 _start

	No version information found in this file.

ELF格式提供了两种维度的视角,因为两者关心(即需要使用的目标数据不同)

 - 链接器视角:链接器把ELF文件看成是Section的集合. 关心`Section Header Table`而不关心`Program Header Table`.
 - 加载器视角:加载器把ELF文件看成为Segment的集合. 关心`Program Header Table`而不关心`Section Header Table`.

产生这种情况的原因是,链接器需要合并section，而加载器需要将ELF文件装入内存,分配内存以及读写权限.

`Program Header Table`中保存了所有`Segment`的描述信息，`Section Header Table`在加载过程中用不到，所以是可有可无的。
一个Segment由一个或多个Section组成，这些Section加载到内存时具有相同的访问权限。
有些Section只对链接器有意义，在运行时用不到，也不需要加载到内存，那么就不属于任何Segment.(Segment在装载时非常重要,例如我们常见的`Segment fault`).

ELF文件有三种(按照ELF格式进行布局的一类文件)

 - 目标文件
 - 可执行文件
 - 共享库文件

对应上边的布局

 - 目标文件需要链接器做进一步处理，所以一定有Section Header Table；
 - 可执行文件需要加载运行，所以一定有Program Header Table；
 - 共享库既要加载运行，又要在加载时做动态链接，所以既有Section Header Table又有Program Header Table。

文件地址：就是代码在文件中的位置


#### 变量的存储布局

我们知道，C语言的全局变量如果在代码中没有初始化，就会在程序加载时用0初始化。这种数据属于.bss段，在加载时它和.data段一样都是可读可写的数据，但是在ELF文件中.data段需要占用一部分空间保存初始值，而.bss段则不需要。

也就是说，.bss段在文件中只占一个Section Header而没有对应的Section，程序加载时.bss段占多大内存空间在Section Header中描述。在我们这个例子中没有用到.bss段.

#### 参考资料地址

https://docs.huihoo.com/c/linux-c-programming/ch18s05.html




