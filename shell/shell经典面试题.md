## shell经典面试题

找出`~/documents`内大于50k，小于100k的文件，并删除它们。

    #!/bin/bash
    file_list=$(find ~/Documents -size +50k -size -1000k)
    for i in $file_list 
    do
        echo $i
    done
    
查看`/web.log`第`25`行`第三列`的内容

    awk '{if(RN==25) print $3}' /web.log
    
定时执行一个任务

    将定时任务配置追加到 /etc/crontab

找到`nginx master`进程ID
    
    [sujianhui@dev0529 Documents]$>ps aux | grep nginx | grep master | awk '{print $2}'
    17036

1到10数字相加，写出shell脚本


shell中两个整数相加

    A=5    
    B=6
    
 - `let $A+$B`    
 - `echo $(($A+$B))` 
 - `echo $[$A+$B]` 
 - `expr $A + $B` 
 - `echo $A+$B | bc` 
 -  `awk 'BEGIN{print '"$A"'+'"$B"'}'` 

命令"export"有什么用 ?

    将变量声明为环境变量,使变量在子shell中可用.
    
如何只用`echo`命令获取字符串变量的一部分 ?

    echo ${variable:x:y}
    x - 起始位置  从0开始计数    
    y - 长度
    
    #!/bin/bash
    name=lujianhui
    echo ${name:2:4}
    # 只会显示 jian
    
如何使用 awk 列出 UID 小于 100 的用户 ?

    awk -F ':' '{if($3<100) print $1}' /etc/passwd

如何获取变量长度 ?

    ${#variable}
    
输出`variable`的最后 10 个字符
    
    ${variable: -10}
    
如何打印传递给脚本的所有参数 ?
    
    echo $*  / echo $@
    
`[ a ==b ]` 和 `[ a -eq b ]` 有什么区别

 - `[ a == b ]`  用于字符串比较
 - `[ a -eq b ]`  用于数字比较
    
`=` 和 `==` 有什么区别

 - `=`  用于为变量赋值
 - `==`  用于字符串比较
 
`[[ string == abc* ]]` 和 `[[string == "abc" ]]` 有什么区别

 - `[[ $string == abc* ]]`   检查字符串是否以字母 `abc` 开头
 - `[[ $string == "abc" ]]`  检查字符串是否完全等于 `abc`
