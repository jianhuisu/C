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
        
