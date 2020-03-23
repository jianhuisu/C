## Makefile使用

make命令会自动读取当前目录下的Makefile文件，完成相应的编译步骤。Makefile由一组规则（Rule）组成，每条规则的格式是：

    target ... : prerequisites ... 
        command1
        command2
        ...

 - target: / target : (target与:号之间有无空格都可以)
        
执行make命令时，是按照GNUmakefile、makefile、Makefile的顺序找到第一个存在的文件并执行它，不过还是建议使用Makefile做文件名
        
### 用例

#### make clean

e.g.

    main:main.o dep1.o dep2.o
    	gcc main.o dep1.o dep2.o -o main
    main.o: main.c main.h dep1.h dep2.h
    	gcc -c main.c -o main.o
    dep1.o: dep1.c dep1.h
    	gcc -c dep1.c -o dep1.o
    dep2.o : dep2.c dep2.h
    	gcc -c dep2.c -o dep2.o
    
    clean:
    	@echo "cleanning project"
    	-rm main *.o
    	@echo "clean completed"
    
    # 声明 clean 目标是一个伪目标与真正的编译目标区别开 防止因为存在同名文件或者文件夹而影响make rule 的解析 
    .PHONY: clean
    
shell中执行
    
    $ make clean 
    cleanning project
    rm main *.o
    clean completed
    
如果在make的命令行中指定一个目标（例如clean），则更新这个目标，如果不指定目标则更新Makefile中第一条规则的目标（缺省目标）。
只要执行了命令列表就算更新了目标，即使目标并没有生成也算

如果make执行的命令前面加了@字符，则不显示命令本身而只显示它的结果；
如果命令前面加了-号，即使这条命令出错，make也会继续执行后续命令。通常rm命令和mkdir命令前面要加-号，因为rm要删除的文件可能不存在，mkdir要创建的目录可能已存

    // -rm main *.o 
    [guangsujiqiang@su-ct7 tool_makefile]$>make clean
    cleanning project
    rm main *.o
    rm: cannot remove ‘main’: No such file or directory
    rm: cannot remove ‘*.o’: No such file or directory
    make: [clean] Error 1 (ignored) // !!!!!!注意这里 Error 忽略  如果这里错误可以忽略 证明错误无关紧要
    clean completed
    
    // rm main *.o  命令前没有 - 
    [guangsujiqiang@su-ct7 tool_makefile]$>make clean
    cleanning project
    rm main *.o
    rm: cannot remove ‘main’: No such file or directory
    rm: cannot remove ‘*.o’: No such file or directory
    make: *** [clean] Error 1  // !!!!!!注意这里 Error 未忽略 如果这里错误不能忽略 证明错误会影响结果的正确性

clean目标是一个约定俗成的名字，在所有软件项目的Makefile中都表示清除编译生成的文件，类似这样的约定俗成的目标名字有：

 - all，执行主要的编译工作，通常用作缺省目标。
 - install，执行编译后的安装工作，把可执行文件、配置文件、文档等分别拷到不同的安装目录。
 - clean，删除编译生成的二进制文件。
 - distclean，不仅删除编译生成的二进制文件，也删除其它生成的文件，例如配置文件和格式转换后的文档，执行make distclean之后应该清除所有这些文件，只留下源文件。
 - test , 单元测试
 
e.g.

     clean:
        	@echo "cleanning project"
        	-rm main *.o
        	@echo "clean completed"
        
    # 声明 clean 目标是一个伪目标与真正的编译目标区别开 防止因为存在同名文件或者文件夹而影响make rule 的解析 
    .PHONY: clean all install distclean test
    
    
### 要点

##### 函数声明与函数定义不要写在同一个文件 函数声明在头文件中 函数定义在.c文件中
##### 每条命令必须以一个Tab开头

命令列表中的每条命令必须以一个Tab开头，注意不能是空格，对于Makefile中的每个以Tab开头的命令，make会创建一个Shell进程去执行它
否则会出现错误提示 
   
    Makefile:8: *** missing separator.  Stop.  
    第 8 行缺失 separator
 
    [guangsujiqiang@su-ct7 tool_makefile]$>man ascii | grep horizontal
    Oct   Dec   Hex   Char                        Oct   Dec   Hex   Char
    011   9     09    HT  '\t' (horizontal tab)   111   73    49    I
    
    vim 打开 `esc + %!xxd`查看二进制编码   
    
    CLion中Makefile设置Tab Clion->Preferences->Editor->Code Style->Other file Type -> use Tab character
    
##### Makefile中依赖文件要包括头文件 

这是一个严谨的做法 当头文件中包括宏 /依赖关系时  ,头文件的更新将影响编译结果

### 内建的隐含规则（Implicit Rule）

这三条规则可以由make的隐含规则推导出来，所以不必写在Makefile中。
我们知道，写规则的目的是让make建立依赖关系图，不管怎么写，只要把所有的依赖关系都描述清楚了就行。对于多目标的规则，make会拆成几条单目标的规则来处理，例如
makefile 不单单可以围绕目标为中心编写，同样也可以围绕条件


CC是一个Makefile变量，用CC = cc定义和赋值，用$(CC)取它的值，其值应该是cc。
Makefile变量像C的宏定义一样，代表一串字符，在取值的地方展开。cc是一个符号链接，通常指向gcc，在有些UNIX系统上可能指向另外一种C编译器。

    [guangsujiqiang@su-ct7 tool_makefile]$>which cc | xargs ls -l 
    lrwxrwxrwx. 1 root root 3 Oct 17 01:45 /usr/bin/cc -> gcc
