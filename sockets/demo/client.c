#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 8000
#define SERVER_IP "127.0.0.1"

int main(void)
{
    printf("this is client \n");

    struct sockaddr_in server_addr;
    int sock_fd;

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // ip 的点分十进制表示法 转换为 网络字节序
    // server_addr.sin_addr.s_addr = inet_pton(SERVER_IP); // 这个函数有问题
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    // todo 这个sock_fd 是自己的fd 还是 对端的fd ?
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if( connect(sock_fd,(struct sockaddr * )&server_addr,sizeof(server_addr)) < 0){
        perror("connect fail \n");
        exit(EXIT_FAILURE);
    }

    write(sock_fd,"hello world",20);

    char buffer[40];

    read(sock_fd,buffer,40);
    close(sock_fd);
    printf("connection break off \n");
    return 0;
}