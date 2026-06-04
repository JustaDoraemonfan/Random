#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>


int main() {
    struct sockaddr_in s, c;
    bzero(&s, sizeof(s));
    unsigned short port = 9000;
    char ip[] = "127.0.0.1";

    s.sin_family = AF_INET;
    s.sin_port = htons(port);
    inet_aton(ip, &s.sin_addr);

    int sk = socket(AF_INET, SOCK_STREAM, 0);
    if(sk < 0) {
        printf("Socket Failed\n");
        exit(1);
    }
    int b = bind(sk, (struct sockaddr*)&s, sizeof(s));
    if(b < 0) {
        printf("Bind Failed\n");
        exit(1);
    }
    int l = listen(sk, 10);
    if(l < 0) {
        printf("Listen Failed \n");
        exit(1);
    }
    socklen_t clen = sizeof(c);
    while(1) {
        printf("Listening for Clients : ");
        int connfd = accept(sk, (struct sockaddr*)&c, &clen);
        if(connfd < 0) {
            printf("Client connection failed !\n");
            exit(1);
        }
        printf("Client Connected ! \n");
        while(1) {
            char buff[128];
            int r = read(connfd, buff, sizeof(buff)-1);
            if(r <= 0) {
                printf("Client Disconnected\n");
                break;
            }
            buff[r] = '\0';
            buff[strcspn(buff, "\r\n")] = '\0';
            if(strcmp(buff, "exit") == 0){
                close(connfd);
                break;
            }
            printf("Client : %s\n", buff);
            bzero(buff, sizeof(buff));
            printf("Server : ");
            fgets(buff, sizeof(buff)-1, stdin);
            buff[strcspn(buff, "\r\n")] = '\0';
            if (strcmp(buff, "exit") == 0){
                write(connfd, buff, strlen(buff));
                break;
            }

            int w = write(connfd, buff, strlen(buff));
            if(w < 0) {
                printf("Write Failed \n");
                exit(1);
            }
        }
        close(connfd);
    }
    close(sk);
}