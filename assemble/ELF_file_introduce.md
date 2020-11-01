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





