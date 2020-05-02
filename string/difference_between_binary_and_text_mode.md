## 文件的二进制和文本模式的区别

1.在windows系统中，文本模式下，文件以"\r\n"代表换行。若以文本模式打开文件，并用fputs等函数写入换行符"\n"时，
   函数会自动在"\n"前面加上"\r"。即实际写入文件的是"\r\n" 。

2.在类Unix/Linux系统中文本模式下，文件以"\n"代表换行。所以Linux系统中在文本模式和二进制模式下并无区别。

### 个人理解

所有数据在硬盘上存储都是以二进制的形式,1010101010100101010 这种格式,系统按照ASCII编码规则,对文件进行读取,保存.
ASCII编码以八位二进制为一组,每组二进制串表示一个字符,我们在键盘上的每按下一个按键,其实都对应着一串二进制串,
或者我们可以这样理解,我们对键盘的每一个操作,都对应着一串二进制代码,只不过有的可以转化为字母数字等可见字符,而有的不能而已

比如一个文件里面存储的内容是 abc

 - 人类：abc[回车]
 - 计算机:0x61 0x62 0x63 0x0d

那些我们通过电脑无法直接感知到的字符,比如换行 空格 缩进 虽然也有自己的二进制编码,但是我们通过编辑器查看时,编辑器显示的只是它们的表象,
而不是他们的二进制编码,同样,我们通过编辑器向文件写入数据时 编辑器先将我们输入的字符转换为 二进制编码,然后存储,写入与读取互为逆操作

 - 在Linux系统上,二进制模式与文本模式都是使用`\r`即`0x0d`表示可见字符后面的"换行操作",也就是说,在Linux系统上,文本模式/二进制模式中位串都是使用`\r`作为`换行动作`separator的
 - 在Win系统上,文本模式中使用`\r\n`表示可见字符后面的"换行操作",二进制模式中使用`\r`作为separator

所以不同操作系统上的文件打开时,会由于对"换行操作"定义不同,而出现一些莫名其妙的问题,所以为了编写可移植的程序,
推荐在所有系统调用fopen(file_name1, "wb")时, 打开模式参数带上"b"

### 通过vim查看内容的16进制表示

    esc 进入命令模式
    以16进制模式查看内容 %!xxd   
    以文本模式查看内容   %!xxd -r
    % 所有行

本质都一样,不同的解析方式,得出不同的外相。(windows可以通过notepad++的插件查看)

### 制作一个二进制文件

    /* writerec.c */
    #include <stdio.h>
    #include <stdlib.h>
    
    struct record {
    	char name[10];
    	int age;
    };
    
    int main(void)
    {
    	struct record array[2] = {{"Ken", 24}, {"Knuth", 28}};
    	FILE *fp = fopen("recfile", "w");
    	if (fp == NULL) {
    		perror("Open file recfile");
    		exit(1);
    	}
    	fwrite(array, sizeof(struct record), 2, fp);
    	fclose(fp);
    	return 0;
    }
    
读取自己制作的二进制文件

    /* readrec.c */
    #include <stdio.h>
    #include <stdlib.h>
    
    struct record {
    	char name[10];
    	int age;
    };
    
    int main(void)
    {
    	struct record array[2];
    	FILE *fp = fopen("recfile", "r");
    	if (fp == NULL) {
    		perror("Open file recfile");
    		exit(1);
    	}
    	fread(array, sizeof(struct record), 2, fp);
    	printf("Name1: %s\tAge1: %d\n", array[0].name, array[0].age);
    	printf("Name2: %s\tAge2: %d\n", array[1].name, array[1].age);
    	fclose(fp);
    	return 0;
    }
    
执行

    $ gcc writerec.c -o writerec
    $ gcc readrec.c -o readrec
    $ ./writerec
    $ od -tx1 -tc -Ax recfile 
    000000 4b 65 6e 00 00 00 00 00 00 00 00 00 18 00 00 00
             K   e   n  \0  \0  \0  \0  \0  \0  \0  \0  \0 030  \0  \0  \0
    000010 4b 6e 75 74 68 00 00 00 00 00 00 00 1c 00 00 00
             K   n   u   t   h  \0  \0  \0  \0  \0  \0  \0 034  \0  \0  \0
    000020
    $ ./readrec 
    Name1: Ken	Age1: 24
    Name2: Knuth	Age2: 28
    
我们把一个`struct record`结构体看作一条记录，由于结构体中有填充字节，每条记录占16字节，把两条记录写到文件中共占`32`字节。
该程序生成的`recfile`文件是二进制文件而非文本文件，**因为其中不仅保存着字符型数据，还保存着整型数据24和28**（在od命令的输出中以八进制显示为030和034）。

注意：直接在文件中读写结构体的程序是不可移植的，如果在一种平台上编译运行writebin.c程序，
把生成的recfile文件拷到另一种平台并在该平台上编译运行readbin.c程序，则不能保证正确读出文件的内容，
因为不同平台的大小端可能不同（因而对整型数据的存储方式不同），
结构体的填充方式也可能不同（因而同一个结构体所占的字节数可能不同，age成员在name成员之后的什么位置也可能不同）。        



