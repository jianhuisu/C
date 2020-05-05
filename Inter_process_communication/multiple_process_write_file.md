## 多个进程同时向一个文件写入

多个进程向同一个文件进行写操作,该文件属于临界资源,因为没有做进程同步限制,所以写入结果是不可预测的.

    #include <sys/types.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(void)
    {
        pid_t pid;
    
        int childs_num ;
        FILE * fp;
    
        if( (fp = fopen("/home/sujianhui/CLionProjects/C/a_test/example.txt","a+")) == NULL){
            perror("open error");
        }
    
        for(childs_num = 0;childs_num<4;childs_num++){
    
            pid = fork();
            if (pid < 0) {
                perror("fork failed");
                exit(1);
            }
    
            if (pid == 0) {
    
                int i;
                size_t j;
                char a[40];
                for (i = 3; i > 0; i--) {
                     j = snprintf(a, 30, "child pid is %d \n", getpid());
                     fwrite(a,40,1,fp);
                     printf(" %s \n",a);
                     sleep((3*i)+1);
                }
    
                fclose(fp);
                exit(1);
            } else {
                printf("fork child %d \n",pid);
            }
    
        }
    
        int count = 0;
        while(1){
            printf("%d \n",count++);
            sleep(5);
        }
        return 0;
    }
    
