## 自动处理头文件的依赖关系

人工数里依赖关系很容易出现错误,gcc套件提供了工具动态解析依赖关系

 - gcc -M main.c  输出以main.c源文件的依赖,`包括` 系统头文件的依赖关系 例如 stdio.h的依赖关系
 - gcc -MM main.c 输出以main.c源文件的依赖,`不包括`对操作系统的依赖项
 

### GNU官方建议Makefile写法

    all: main
    main: main.o stack.o maze.o
        gcc $^ -o $@
    clean:
        -rm main *.o
    .PHONY: clean
    sources = main.c stack.c maze.c
    include $(sources:.c=.d)
    %.d: %.c
        set -e; rm -f $@; \
        $(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
        rm -f $@.$$$$
        
注意，虽然在Makefile中这个命令写了四行，但其实是一条命令，make只创建一个Shell进程执行这条命令，这条命令分为5个子命令，用;号隔开，并且为了美观，用续行符\拆成四行来写。执行步骤为：

 - set -e命令设置当前Shell进程为这样的状态：如果它执行的任何一条命令的退出状态非零则立刻终止，不再执行后续命令。
 - 把原来的maze.d删掉。
 - 重新生成maze.c的依赖关系，保存成文件maze.d.1234（假设当前Shell进程的id是1234）。注意，在Makefile中$有特殊含义，如果要表示它的字面意思则需要写两个$，所以Makefile中的四个$传给Shell变成两个$，两个$在Shell中表示当前进程的id，一般用它给临时文件起名，以保证文件名唯一。
 - 经过sed处理之后存为maze.d，其内容是maze.o maze.d: maze.c maze.h main.h。
 - 最后把临时文件maze.d.1234删掉。
 
特殊变量(下面的规则指紧紧相临的规则)
 
 - $@，表示规则中的目标
 - $<，表示规则中的第一个条件
 - $?，表示规则中所有比目标新的条件，组成一个列表，以空格分隔
 - $^，表示规则中的所有条件，组成一个列表，以空格分隔
 
 
    main: main.o stack.o maze.o
        gcc main.o stack.o maze.o -o main
        
    =>
    
    main: main.o stack.o maze.o
    	gcc $^ -o $@
    	
### 子模块的Makefile

进入到子目录`testmake`,编译下面的Makefile

    make -C testmake

-C选项可以切换到另一个目录执行那个目录下的Makefile，比如先退到上一级目录再执行我们的Makefile（假设我们的源代码都放在testmake目录下）：
一些规模较大的项目会把不同的模块或子系统的源代码放在不同的子目录中，然后在每个子目录下都写一个该目录的Makefile，
然后在一个总的Makefile中用make -C命令执行每个子目录下的Makefile。
例如Linux内核源代码根目录下有Makefile，子目录fs、net等也有各自的Makefile，二级子目录fs/ramfs、net/ipv4等也有各自的Makefile。

思考：为什么需要模块这一个概念呢? heihei

### debug

在make命令行也可以用`=`或`:=`定义变量，如果这次编译我想加调试选项`-g`，但我不想每次编译都加-g选项，
可以在命令行定义CFLAGS变量，而不必修改Makefile编译完了再改回来：(这个超实用且很常见)

    $ make CFLAGS=-g
    cc -g   -c -o main.o main.c
    cc -g   -c -o stack.o stack.c
    cc -g   -c -o maze.o maze.c
    gcc main.o stack.o maze.o -o main
    
如果在Makefile中也定义了CFLAGS变量，则命令行的值覆盖Makefile中的值。

-n选项只打印要执行的命令，而不会真的执行命令，这个选项有助于我们检查Makefile写得是否正确，由于Makefile不是顺序执行的，
用这个选项可以先看看命令的执行顺序，确认无误了再真正执行命令。
