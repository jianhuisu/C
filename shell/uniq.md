## uniq 

uniq命令：过滤文件中的重复内容,将去重后的内容显示在终端，并不会改变源文件内容

    uniq repeat.txt

如果想要保存去重后的内容 `uniq repeat.txt unrepeat.txt`

`-d`参数：只显示重复行的值
`-c` 显示重复次数

例如：

    [sujianhui@dev529 pfd]$ uniq -c ip.txt 
    1 123 3344
    3 124 3344
    1 123 3344
    2 121 3344
    1 121 5344

**当重复的行并不相邻时，`uniq -c`命令是不起作用的**，即若文件内容为以下格式时，`uniq`命令不起作用：

    $ cat testfile1      # 原有内容 
    test 30  
    Hello 95  
    Linux 85 
    test 30  
    Hello 95  
    Linux 85 
    test 30  
    Hello 95  
    Linux 85 
    
所以 有一个文件`ip.txt`，每行一条ip记录，共若干行，下面哪个命令可以实现`统计出现次数最多的前3个ip及其次数?`

 - 正确答案 `sort -nr ip.txt | uniq -c | sort -nr | head -n 3`
 - 错误答案 `uniq -c ip.txt | sort -nr | head -n 3`  
 
 