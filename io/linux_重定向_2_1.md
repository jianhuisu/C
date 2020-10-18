# linux shell中"2>&1"含义

在计划任务中经常可以看到。例如我们公司的计划任务举例：

    */2 * * * * root cd /opt/xxxx/test_S1/html/xxxx/admin; php index.php task testOne >/dev/null 2>&1
    */2 * * * * root cd /opt/xxxx/test_S1/html/xxxx/admin; php index.php task testTwo >/dev/null 2>&1
    
 - fd 0 standard in
 - fd 1 standard out
 - fd 2 standard error out
 
对于`&1`更准确的说应该是文件描述符`1`,而1标识标准输出`stdout`对于 `2` ，表示标准错误`stderr`.

`2>&1` 的意思就是将标准错误重定向到标准输出。这里标准输出已经重定向到了 `/dev/null`。那么标准错误也会输出到`/dev/null`
可以把`/dev/null`可以看作"黑洞". 它等价于一个只写文件. 所有写入它的内容都会永远丢失. 而尝试从它那儿读取内容则什么也读不到.

为何`2>&1`要写在后面？

    index.php task testOne > /dev/null 2>&1

我们可以理解为，左边是标准输出，好，现在标准输出直接输入到 /dev/null 中，而2>&1是将标准错误重定向到标准输出，
所以当程序产生错误的时候，相当于错误流向左边，而左边依旧是输入到/dev/null中。

