## shell中一些常用的特殊用法

### 命令替换

执行一个命令,将命令的输出赋值到一个变量.

    #!/bin/bash
    
    DATE_1=`date`
    DATE_2=$(date)
    
    echo $DATE_1
    echo $DATE_2
    
输出

    [sujianhui@dev529 shell]$sh -f eg.sh 
    Wed May 6 10:43:57 CST 2020
    Wed May 6 10:43:57 CST 2020

推荐用`$()`这种方式.
       
### shell 通配符

 - `*`	匹配0个或多个任意字符
 - `?`	匹配一个任意字符
 - `[若干字符]`	匹配方括号中任意一个字符的一次出现

eg.

    $ ls /dev/ttyS*
    $ ls ch0?.doc
    $ ls ch0[0-2].doc
    $ ls ch[012][0-9].doc
    
**`Globbing`所匹配的文件名是由Shell展开的**，也就是说在参数还没传给程序之前已经展开了，
比如上述`ls ch0[012].doc`命令，如果当前目录下有ch00.doc和ch02.doc，则传给ls命令的参数实际上是这两个文件名，而不是一个匹配字符串。

### 算术代换：$(())

用于算术计算，`$(())`中的Shell变量取值将转换成整数，例如：

    #!/bin/bash
    
    VAR_NAME1=3
    VAR_NAME2=4
    
    echo $VAR_NAME1 + $VAR_NAME2
    echo $(($VAR_NAME1 + $VAR_NAME2))
    
输出

    [sujianhui@dev529 shell]$sh -f eg.sh 
    3 + 4
    7
    
`$(())`中只能用`+-*/`和`()`运算符，并且只能做`整数`运算。

### login shell

当前用户使用哪个shell,由`/etc/passwd`决定.

shell load 顺序 `/etc/profile` `~/.bash_profile`、`~/.bash_login`和`~/.profile`

### 空命令

`:`是一个特殊的命令，称为空命令，该命令不做任何事，但`Exit Status`总是真

    if :; then echo "always true"; fi