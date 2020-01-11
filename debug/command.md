    
    
    backtrace（或bt）	查看各级函数调用及参数
    finish	            连续运行到当前函数返回为止，然后停下来等待命令 // 相当于 return 到函数调用处
    frame（或f）         根据帧编号	选择栈帧，然后可以查看该帧上的局部变量 , 越新调用的帧 帧号越小
    info（或i） locals	查看当前栈帧局部变量的值
    list（或l）	        列出源代码，接着上次的位置往下列，每次列10行
    list 行号	        列出从第几行开始的源代码
    list 函数名	        列出某个函数的源代码
    next（或n）	        执行下一行语句
    print（或p）	        打印表达式的值，通过表达式可以修改变量的值或者调用函数
    quit（或q）       	退出gdb调试环境
    set var	            修改变量的值
    start	            开始执行程序，停在main函数第一行语句前面等待命令
    step（或s）	        执行下一行语句，如果有函数调用则进入到函数中
    
    
    break（或b） 行号	          在某一行设置断点
    break 函数名	                  在某个函数开头设置断点
    break ... if ...	          设置条件断点  // break 9 if sum != 0 
    continue（或c）	              从当前位置开始连续运行程序
    delete breakpoints  断点号	  删除断点
    display 变量名	              跟踪查看某个变量，每次停下来都显示它的值
    undisplay 跟踪显示号	          取消跟踪显示
    disable breakpoints 断点号	  禁用断点
    enable 断点号	              启用断点
    info（或i） breakpoints	      查看当前设置了哪些断点
    run（或r）	                  从头开始连续运行程序
    
这部分超有用

    watch  观察点                   设置观察点  // (gdb) watch input[5]  ,设置了观察点之后 可以使用 c 运行到下一个观察点
    info（或i） watchpoints	       查看当前设置了哪些观察点
    x	                           从某个位置开始打印存储单元的内容，全部当成字节来看，而不区分哪个字节属于哪个变量
    
    (gdb) x/7b input
    0xbfb8f0a7:	0x31	0x32	0x33	0x34	0x35	0x00	0x00
    
    x命令打印指定存储单元的内容。7b是打印格式，b表示每个字节一组，7表示打印7组
    
    
    
eg.

    gdb -Wall -g break.c -o main
    gdb main
    ...
    list 
    start 
    n
    n
    watch input[5]
    info watchpoints
    c
    ...
    c
    finish
    ...
    q
    
       
    
    
    