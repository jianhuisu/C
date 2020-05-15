## 常见命令    
    
#### run 
    
    run（或r）	        从头开始连续运行程序   gdb > r 1.php  ==> php 1.php
    start	            开始执行程序，停在main函数第一行语句前面等待命令
    step（或s）	        执行下一行语句，如果有函数调用则进入到函数中
    until               运行至当前语句块结束
    continue（或c）	    从当前位置开始连续运行程序
    next（或n）	        执行下一行语句\
    finish	            连续运行到当前函数返回为止，然后停下来等待命令 // 相当于 return 到函数调用处
    detach              leave current process
    quit（或q）       	退出gdb调试环境

#### view code 
    
    list（或l）	        列出源代码，接着上次的位置往下列，每次列10行
    list 行号	        列出从第几行开始的源代码
    list 函数名	        列出某个函数的源代码
    print（或p）	        打印表达式的值，通过表达式可以修改变量的值或者调用函数
    display 变量名	    跟踪查看某个变量，每次停下来都显示它的值
    undisplay 跟踪显示号	取消跟踪显示
    
#### frames     

    backtrace（或bt）	查看各级函数调用及参数
    frame（或f）         根据帧编号	选择栈帧，然后可以查看该帧上的局部变量 , 越新调用的帧 帧号越小
    info（或i） locals	查看当前栈帧局部变量的值

##### breakpoints 
    
    break（或b） 行号	              在某一行设置断点
    break 函数名	                  在某个函数开头设置断点
    break ... if ...	          设置条件断点  // break 9 if sum != 0 
    delete breakpoints  断点号	  删除断点
    disable breakpoints 断点号	  禁用断点
    enable 断点号	              启用断点
    info（或i） breakpoints	      查看当前设置了哪些断点
    
##### temp variables 

    set var	            修改变量的值    
    