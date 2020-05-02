## od

example.txt文件中内容

    5678
         K

使用工具查看

    [sujianhui@nlp a_test]$ od -tx1 -tc -Ax example.txt 
    000000  35  36  37  38  0a  00  00  00  00  00  4b
             5   6   7   8  \n  \0  \0  \0  \0  \0   K
    00000b
 