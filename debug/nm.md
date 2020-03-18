## nm工具介绍

man一下

    nm - list symbols from object files 列表展示目标文件中的符号

### 使用方式

    gcc -c main.c -o main.o
    nm main.o 
    // 或者
    gcc main.c -o a.out 
    nm a.out 

搞个有数据的
 
    [guangsujiqiang@su-ct7 Link]$>nm a.out
    // The symbol value | The symbol type | The symbol name 
    0000000000601044 B a
    0000000000601034 D b
    000000000060103c B __bss_start
    0000000000601040 b completed.6355
    0000000000601030 D __data_start
    0000000000601030 W data_start
    0000000000400470 t deregister_tm_clones
    00000000004004e0 t __do_global_dtors_aux
    0000000000600e18 t __do_global_dtors_aux_fini_array_entry
    0000000000400678 R __dso_handle
    0000000000600e28 d _DYNAMIC
    000000000060103c D _edata
    0000000000601260 B _end
    0000000000400664 T _fini
    0000000000400500 t frame_dummy
    0000000000600e10 t __frame_dummy_init_array_entry
    0000000000400820 r __FRAME_END__
    0000000000601000 d _GLOBAL_OFFSET_TABLE_
                     w __gmon_start__
    0000000000400680 r __GNU_EH_FRAME_HDR
    00000000004003e0 T _init
    0000000000600e18 t __init_array_end
    0000000000600e10 t __init_array_start
    0000000000400670 R _IO_stdin_used
    00000000004005da T is_empty
    0000000000600e20 d __JCR_END__
    0000000000600e20 d __JCR_LIST__
    0000000000400660 T __libc_csu_fini
    00000000004005f0 T __libc_csu_init
                     U __libc_start_main@@GLIBC_2.2.5
    000000000040052d T main
    00000000004005bc T pop
    0000000000400590 T push
                     U putchar@@GLIBC_2.2.5 // --------------------------- 看标注
    00000000004004a0 t register_tm_clones
    0000000000601060 B stack
    0000000000400440 T _start
    0000000000601040 D __TMC_END__
    0000000000601038 D top

标注：U putchar@@GLIBC_2.2.5 这个符号未定义 链接生成可执行文件main时可以做符号解析，
而putchar是libc的库函数，在可执行文件main中仍然是未定义的，要在程序运行时做动态链接。

### symbols value 项解析

hexadecimal by default 默认为16进制
    
### symbols type项解析

todo 待我融汇贯通 再来完善

The symbol type.  At least the following types are used; others are, as well, depending on the object file format. 
符号类型 常规情况下有以下选项 ,另外也会有一些其它类型存在于某些特殊格式的目标文件中
  
 - If lowercase, the symbol is usually local; // local符号不参与链接过程 哈哈
 - if uppercase, the symbol is global (external).

There are however a few lowercase symbols that are shown for special global symbols ("u", "v" and "w").
特例,上面两条规则的特殊情况 
    
 "A" The symbol's value is absolute, and will not be changed by further linking.

    "B"
    "b" .bss 段中的未初始化符号 
    
    "C" The symbol is common.  Common symbols are uninitialized data.  When linking, multiple common symbols may appear with the same name.  
        If the symbol is defined anywhere, the common symbols are treated as undefined references.
    
    "D"
    "d" .bss中已经初始化的符号 The symbol is in the initialized data section.
    
    "G"
    "g" The symbol is in an initialized data section for small objects.  
        Some object file formats permit more efficient access to small data objects, such as a global int variable as opposed to a
        large global array.
    
    "i" For PE format files this indicates that the symbol is in a section specific to the implementation of DLLs.  For ELF format files this indicates that the symbol is an indirect function.  This
       is a GNU extension to the standard set of ELF symbol types.  It indicates a symbol which if referenced by a relocation does not evaluate to its address, but instead must be invoked at
       runtime.  The runtime execution will then return the value to be used in the relocation.
    
    "I" The symbol is an indirect reference to another symbol.
    
    "N" The symbol is a debugging symbol.
    
    "p" The symbols is in a stack unwind section.
    
    "R"
    "r" The symbol is in a read only data section.
    
    "S"
    "s" The symbol is in an uninitialized data section for small objects.
    
    "T"
    "t" The symbol is in the text (code) section.
    
    "U" 符号未定义
    
    "u" The symbol is a unique global symbol.  This is a GNU extension to the standard set of ELF symbol bindings. 
        For such a symbol the dynamic linker will make sure that in the entire process
        there is just one symbol with this name and type in use.
    
    "V"
    "v" The symbol is a weak object.(弱对象)  When a weak defined symbol is linked with a normal defined symbol, 
        the normal defined symbol is used with no error.  When a weak undefined symbol is linked and
        the symbol is not defined, the value of the weak symbol becomes zero with no error.  
        On some systems, uppercase indicates(表示) that a default value has been specified.
    
    "W"
    "w" The symbol is a weak symbol that has not been specifically tagged as a weak object symbol.  When a weak defined symbol is linked with a normal defined symbol, the normal defined symbol is
       used with no error.  When a weak undefined symbol is linked and the symbol is not defined, the value of the symbol is determined in a system-specific manner without error.  On some systems,
       uppercase indicates that a default value has been specified.
    
    "-" The symbol is a stabs symbol in an a.out object file.  In this case, the next values printed are the stabs other field, the stabs desc field, and the stab type.  Stabs symbols are used to
       hold debugging information.
