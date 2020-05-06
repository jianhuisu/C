## shell编程

### 变量

有两种类型的Shell变量：

 - 本地变量   只子当前shell进程中有效   `VARNAME=value`
 - 环境变量   一直有效                 `export VARNAME=value`


##### 定义变量

按照惯例，Shell变量由全大写字母加下划线组成.格式:`VAR_NAME=var_value`(等号两边不能有空格)

    #!/bin/bash
    VAR_NAME1=sdfsdfdf
    VAR_NAME2="sdfsdfdf" # 值是否用双引号包裹无关紧要 
    
##### 使用变量

    #!/bin/bash
    
    VAR_NAME1="sujianhui"
    
    echo $VAR_NAME1
    echo ${VAR_NAME1}
    
    echo "my name is "$VAR_NAME1
    echo "my name is $VAR_NAME1"
    echo "my name is ${VAR_NAME1}"
    
输出结果

    [sujianhui@dev529 shell]$sh -f eg.sh 
    sujianhui
    sujianhui
    my name is sujianhui
    my name is sujianhui
    my name is sujianhui
    
**作为一种好的Shell编程习惯，应该总是把变量取值放在双引号之中**

    echo "$VAR_NAME1"    

##### 判断变量是否存在

Shell变量的值都是字符串,没有变量类型区分,而且Shell变量不需要先定义后使用，如果对一个没有定义的变量取值，则值为空字符串。
所以判断变量是否存在,直接判断变量的值长度是否为0即可.
    
    # 判断 $TERMINAL_EMULATOR 是否已经设置， -z 表示zero 如果未设置为真 如果已经设置为假
    if [ -z $TERMINAL_EMULATOR ]
    then
    	 export PS1="\[\e[32;40m\][\u@\h \W]$>\[\e[0m\]"
    else
    	 export PS1="[\u@\h \W]\$"
    fi

##### 释放变量
    
    unset VARNAME # 注意不是 unset $VARNAME

### 表达式

如果两条命令写在同一行则需要用;号隔开，一行只写一条命令就不需要写;号了

##### 真值测试

命令`test`或`[]`可以测试一个条件是否成立

 - 如果测试结果为真，则该命令的`Exit Status`为`0`.
 - 如果测试结果为假，则命令的`Exit Status`为`1`.

eg.

    [sujianhui@dev529 bin]$>test -z $TERMINAL_EMULATOR
    [sujianhui@dev529 bin]$>echo $?
    0
    [sujianhui@dev529 bin]$>[ -z $TERMINAL_EMULATOR ]
    [sujianhui@dev529 bin]$>echo $?
    0

 - `[ -d DIR ]`	如果DIR存在并且是一个目录则为真
 - `[ -f FILE ]`	如果FILE存在且是一个普通文件则为真
 - `[ -z STRING ]`	如果STRING的长度为零则为真
 - `[ -n STRING ]`	如果STRING的长度非零则为真
 - `[ STRING1 = STRING2 ]`	**如果两个字符串相同则为真**(注意 判断是否相等为一个`=`号，并且两边有空格)
 - `[ STRING1 != STRING2 ]`	如果字符串不相同则为真
 - `[ ARG1 OP ARG2 ]`	`ARG1`和`ARG2`应该是整数或者取值为整数的变量，`OP`的取值是`-eq`（等于）`-ne`（不等于）`-lt`（小于）`-le`（小于等于）`-gt`（大于）`-ge`（大于等于）之中的一个

带与、或、非的测试命令

 - `[ ! EXPR ]`	EXPR可以是上表中的任意一种测试条件，!表示逻辑反
 - `[ EXPR1 -a EXPR2 ]`	EXPR1和EXPR2可以是上表中的任意一种测试条件，-a表示逻辑与
 - `[ EXPR1 -o EXPR2 ]`	EXPR1和EXPR2可以是上表中的任意一种测试条件，-o表示逻辑或

上一个demo

    #!/bin/bash
    
    EXAMPLE_PATH="/home/sujianhui/CLionProjects/C/a_test/example.txt"
    VAR_NAME1=3
    VAR_NAME2=2
    
    if [ -f "$EXAMPLE_PATH" -a "$VAR_NAME1" = "$VAR_NAME2" ]
    then
        echo "true"
    else
        echo "not true"
    fi

输出

    [sujianhui@dev529 shell]$sh -f eg.sh 
    not true


#####  if/then/elif/else/fi

    # 判断 $TERMINAL_EMULATOR 是否已经设置， -z 表示zero 如果未设置为真 如果已经设置为假
    if [ -z $TERMINAL_EMULATOR ]
    then
    	 export PS1="\[\e[32;40m\][\u@\h \W]$>\[\e[0m\]"
    else
    	 export PS1="[\u@\h \W]\$"
    fi
##### case

case里面也可以匹配通配符.
$1是一个特殊变量，在执行脚本时自动取值为第一个命令行参数,等价于`read $1`的意思.

    #!/bin/bash
    
    case $1 in
    	start)
    		echo "start success "
    	;;
    	stop)
    		echo "stop success "
    	;;
    	reload | force-reload)
    		echo "reload success "
    	;;
    	restart)
    	  echo "restart success "
    	;;
    	*)
    		echo "Usage: /etc/init.d/apache2 {start|stop|restart|reload|force-reload|start-htcacheclean|stop-htcacheclean}"
    		exit 1
    	;;
    esac

输出

    [sujianhui@dev529 shell]$sh -f eg.sh start
    start success 

##### for/do/done

以空格切割`in`后面的部分,然后遍历切割后的数组.

    #! /bin/sh
    
    for FRUIT in apple banana pear; do
      echo "I like $FRUIT"
    done
    
    for EV_FILE in $(ls ~/PhpstormProjects/pfd); do
      echo "-- php script :  $EV_FILE"
    done

输出

    [sujianhui@dev529 shell]$sh -f eg.sh
    I like apple
    I like banana
    I like pear   
    -- php script :  attack.php
    -- php script :  basic_auth.php

#####  while/do/done

while的用法和C语言类似。比如一个验证密码的脚本：

    #!/bin/bash
    
    read PW
    
    while [ "$PW" != "secret" ]
    do
      echo "please try again"
      read PW
    done
    
    echo "success login "

##### read

`read`读入信息并存储在一个shell变量中.

    #!/bin/bash
    
    read PEOPLE_INPUT
    echo "-- input is : $PEOPLE_INPUT"

输出

    [sujianhui@dev529 shell]$sh -f eg.sh 
    my name is sujianhui
    -- input is : my name is sujianhui

 

### 执行方式

 - chmod a+x && ./eg.sh  fork一个子shell，脚本文件需要具有x属性才可以执行 
 - sh eg.sh              脚本被当作输入参数
 - source eg.sh 使用该方法执行的脚本,可以使得变量的有效期增长，使得其能在该用户下变量有效.