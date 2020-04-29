### ELF文件各Section标注

系统预定义了一些节名（以.开头），这些节有其特定的类型和含义。

    .bss：包含程序运行时未初始化的数据（全局变量和静态变量）。当程序运行时，这些数据初始化为0.
    .comment 包含版本控制信息（是否包含程序的注释信息？不包含，注释在预处理时已经被删除了）.
    .data和.data1，包含初始化的全局变量和静态变量。
    .debug，包含了符号调试用的信息，我们要想用gdb等工具调试程序，需要该类型信息.
    .line，SHT_PROGBITS，包含符号调试的行号信息，描述了源程序和机器代码的对应关系。gdb等调试器需要此信息。
    .dynamic，包含了动态链接的信息。
    .dynstr, 包含了动态链接用的字符串，通常是和符号表中的符号关联的字符串。
    .dynsym，包含动态链接符号表.
    .fini，程序正常结束时，要执行该section中的指令。现在ELF还包含.fini_array section。
    .got，类型SHT_PROGBITS，全局偏移表(global offset table)，以后会重点讲。
    .hash，类型SHT_HASH，包含符号hash表，以后细讲。标志SHF_ALLOC。
    .init，程序运行时，先执行该节中的代码。现在ELF还包含.init_array section。
    .interp 该节内容是一个字符串，指定了程序解释器的路径名。如果文件中有一个可加载的segment包含该节，属性就包含SHF_ALLOC，否则不包含。
    .note Note Section, 类型SHT_NOTE，以后单独讲。
    .plt 过程链接表（Procedure Linkage Table）
    .rel
    .text
    .relNAME，类型SHT_REL, 包含重定位信息。如果文件有一个可加载的segment包含该section
    .relaname 类型SHT_RELA，和.rel相同。SHT_RELA和SHT_REL的区别，会在讲重定位的时候说明。
    .rodata和.rodata1。 包含只读数据，组成不可写的段。
    .shstrtab，类型SHT_STRTAB，包含section的名字。
    .strtab SHT_STRTAB，包含字符串，通常是符号表中符号对应的变量名字。
    .symtab，类型SHT_SYMTAB，Symbol Table，符号表。包含了定位、重定位符号定义和引用时需要的信息。
    
    
### 参考地址

https://www.cnblogs.com/jiqingwu/p/elf_explore_3.html