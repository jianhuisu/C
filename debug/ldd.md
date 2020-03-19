## ldd 工具的使用

    ldd - print shared library dependencies
   
    [guangsujiqiang@su-ct7 var]$>ldd a.out 
	linux-vdso.so.1 =>  (0x00007ffe272e0000)
	libc.so.6 => /usr/lib64/libc.so.6 (0x00007f7168a14000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f7168de2000)

ldd模拟运行一遍main，在运行过程中做动态链接，从而得知这个可执行文件依赖于哪些共享库，每个共享库都在什么路径下，加载到进程地址空间的什么地址。
