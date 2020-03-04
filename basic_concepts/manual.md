## Linux手册

Linux的man很强大，该手册分成很多section，使用man时可以指定不同的section来浏览，各个section意义如下：
 
 - 1 commands
 - 2 system calls
 - 3 library calls
 - 4 special files
 - 5 file formats and convertions
 - 6 games for linux
 - 7 macro packages and conventions
 - 8 system management commands
 - 9 其他
    
解释一下 

 - 1 是普通的命令
 - 2 是系统调用,如open,write之类的(通过这个，至少可以很方便的查到调用这个函数，需要加什么头文件)
 - 3 是库函数,如printf,fread
 - 4 是特殊文件,也就是/dev下的各种设备文件
 - 5 是指文件的格式,比如passwd, 就会说明这个文件中各个字段的含义
 - 6 是给游戏留的,由各个游戏自己定义
 - 7 是附件还有一些变量,比如向environ这种全局变量在这里就有说明
 - 8 是系统管理用的命令,这些命令只能由root使用,如ifconfig

想要指定section就直接在man的后面加上数字,比如 :

    man 1 ls
    man 3 printf
    
### 如何查看一个宏定义的位置

    [guangsujiqiang@su-ct7 bp]$>find /usr/include/ -name *.h | xargs grep 'WIFEXITED'
    /usr/include/bits/waitstatus.h:/* If WIFEXITED(STATUS), the low-order 8 bits of the status.  */
    /usr/include/bits/waitstatus.h:#define	__WIFEXITED(status)	(__WTERMSIG(status) == 0)
    /usr/include/stdlib.h:# define WIFEXITED(status)	__WIFEXITED (__WAIT_INT (status))
    /usr/include/sys/wait.h:# define WIFEXITED(status)	__WIFEXITED (__WAIT_INT (status))
    
然后`cat`查看内容    

    cat -n /usr/include/sys/wait.h | grep WIFEXITED
    
xargs命令解释

    find /etc/ -name passwd | xargs cat -n

xargs reads items from the standard input, delimited by blanks (which can be protected with double or single quotes or a backslash) or newlines
等价于下面的shell脚本
   
    for item in $(find /etc/ -name passwd )
    do 
        cat -n $item
    done 