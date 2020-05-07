// server.c
// platform : centos7.7
//
#include <stdio.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 8000
#define SERVER_IP_ADDR "127.0.0.1"
// 如果有大量的客户端发起连接而服务器来不及处理，尚未accept的客户端就处于连接等待状态，listen()声明sockfd处于监听状态，并且最多允许有backlog个客户端处于连接等待状态,其它的拒绝连接
#define ACCEPT_BACK_LOG 10
#define READ_CHARACTER_NUM_ONCE 30

int main(void)
{
    int listen_fd,connfd;  // listen_file_des  connect_file_des
    listen_fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr,client_addr;
    char buffer[40];
    int n;
    socklen_t cliaddr_len;

    // bzero 也可以 ，但是建议使用 memset()
    memset(&server_addr,0,sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    // host to network long
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // server_addr.sin_addr.s_addr = inet_pton(SERVER_IP_ADDR);

    // sock API的实现早于ANSI C标准化，那时还没有void *类型，因此这些函数的参数都用struct sockaddr *类型表示，在传递参数之前要强制类型转换一下
    if( bind(listen_fd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr_in)) < 0){
        perror("bind error");
        exit(EXIT_FAILURE);
    }

    // max allow ACCEPT_BACK_LOG in accept queue
    if( listen(listen_fd,ACCEPT_BACK_LOG) < 0){
        perror("listen error");
        exit(EXIT_FAILURE);
    }

    printf("server ready to accept request ... \n");
    while(1){

        cliaddr_len = sizeof(struct sockaddr_in);
        if( ( connfd = accept(listen_fd, (struct sockaddr * )&client_addr, &cliaddr_len) ) < 0 ){
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        n = read(connfd,buffer,READ_CHARACTER_NUM_ONCE);
        // printf("receive [%s : %d ]:  %s \n",client_addr.sin_addr.s_addr,client_addr.sin_port,buffer);
        printf("receive [%s : %d ]:  %s \n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),buffer);
        write(connfd, buffer, n);
        //n = read(connfd,buffer,READ_CHARACTER_NUM_ONCE);
        close(connfd);
    }

    return 0;
}
