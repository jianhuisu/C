执行规则all:的命令列表时才需要展开$(foo)

makefile:

    foo=$(bar)
    bar=hub
    all:
        @echo $(foo)
        
make all

    [guangsujiqiang@su-ct7 test_make_var]$>make
    hub

 - `=` 声明方式到命令列表执行时才展开
 - `:=`声明方式立刻展开

### 参考资料

https://akaedu.github.io/book/ch22s03.html