## gdb multiple process

### 多进程调试

    gdb fork_test.o
    ...
    
    (gdb) 
    13      
    14          if(pid < 0){
    15              perror("fork error");
    16          }
    17      
    18          if(pid == 0){
    19              // this is child
    20              message = "child";
    21              n = 6;
    22          } else {
    (gdb) b 21
    Breakpoint 1 at 0x400642: file test_fork.c, line 21.
    (gdb) set follow-fork-mode child
    (gdb) r
    Starting program: /home/guangsujiqiang/CLionProjects/C/multiple_process/a.out 
    [New process 32507]
    [Switching to process 32507]
    
`set follow-fork-mode child`命令设置gdb在fork之后跟踪子进程（`set follow-fork-mode parent`则是跟踪父进程），
然后用run命令，看到的现象是父进程一直在运行，在(gdb)提示符下打印消息，而子进程被先前设的断点打断了。