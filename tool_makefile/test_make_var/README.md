执行规则all:的命令列表时才需要展开$(foo)

makefile:

    foo=$(bar)
    bar=hub
    all:
        @echo $(foo)
        
make all

    [guangsujiqiang@su-ct7 test_make_var]$>make
    hub



### 参考资料

https://akaedu.github.io/book/ch22s03.html