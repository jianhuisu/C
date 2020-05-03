## 文件描述符

PCB中有个指向文件描述符表的指针,该文件描述符表中的每一个表项包含一个指向已经打开的文件的指针.PCB数据结构又内核维护.
用户程序不能直接访问内核中的文件描述符表，而只能使用文件描述符表的索引（即0、1、2、3这些数字），这些索引就称为文件描述符（File Descriptor），用int型变量保存.

当用户程序调用`open`打开一个文件或创建一个新文件时，内核分配一个`文件描述符`并返回给用户程序，该文件描述符表项中的指针指向新打开的文件。
当读写文件时，用户程序把文件描述符传给read或write，内核根据文件描述符找到相应的表项，再通过表项中的指针找到相应的文件。

 - 标准IO返回的是指向FILE结构体的指针.
 - unbuffered IO 返回的是`int`型的文件描述符.

看代码
    
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    
    
    int main(void)
    {
        int fd;
        FILE * fp;
        char path[] = "/home/sujianhui/CLionProjects/C/a_test/example.txt";
    
        if( (fp = fopen(path,"r+")) == NULL){
            perror(path);
            exit(EXIT_FAILURE);
        }
    
        if( (fd = open(path,O_RDONLY)) < 0){
            perror(path);
            exit(EXIT_FAILURE);
        }
    
        printf("file pointer : %p , file descriptor : %d \n ",fp,fd);
    
        fclose(fp);
        close(fd);
    
        return 0;
    } 
     
输出

    /home/sujianhui/CLionProjects/C/cmake-build-debug/test
    file pointer : 0xcbc010 , file descriptor : 4 
  

