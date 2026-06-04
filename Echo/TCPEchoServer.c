#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>


int main() {
    struct sockaddr_in sock_addr, cli_addr;
    bzero(&sock_addr, sizeof(sock_addr));
    unsigned short port = 9900;
    char ip[] = "127.0.0.1";

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    inet_aton(ip, &sock_addr.sin_addr);

    int serv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(serv_socket < 0){
        printf("Socket Error");
        exit(1);
    }
    int bind_sk = bind(serv_socket, (struct sockaddr*)&sock_addr, sizeof(sock_addr));
    if(bind_sk < 0) {
        printf("Bind Failed");
        exit(1);
    }
    int listen_sk = listen(serv_socket, 10);
    if(listen_sk < 0){
        printf("Cannot Listen");
        exit(1);
    }
    socklen_t cli_addr_len = sizeof(cli_addr);
    while (1){
        printf("Listening for clients : \n");
        int connfd = accept(serv_socket, (struct sockaddr*)&cli_addr, &cli_addr_len);
        if(connfd < 0){
            printf("Client Not Connected");
            continue;
        }
        printf("Client Connected : %s\n", inet_ntoa(cli_addr.sin_addr));
        char buff[128];
        bzero(buff, sizeof(buff));
        int r = read(connfd, buff, sizeof(buff)-1);
        if(r < 0){
            printf("Cannot Read !");
            break;
        }
        buff[r] = '\0';
        buff[strcspn(buff, "\r\n")] = '\0';
        printf("Message from client : %s\n", buff);
        int w = write(connfd, buff, strlen(buff));
        if(w < 0) {
            printf("Failed to write\n");
            break;
        }
        printf("Message sent to client : %s\n", inet_ntoa(cli_addr.sin_addr));
        close(connfd);
    }
    close(serv_socket);
    
    
}