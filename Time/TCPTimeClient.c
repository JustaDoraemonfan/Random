#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main() {
    struct sockaddr_in s;
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
    int c = connect(sk, (struct sockaddr*)&s, sizeof(s));
    if(c < 0){
        printf("Server Connection Failed \n");
        exit(1);
    }
    printf("Server Connected \n");
    while(1) {
        char buff[128];
        printf("Client : ");
        fgets(buff, sizeof(buff)-1, stdin);
        buff[strcspn(buff, "\r\n")] = '\0';
        int w = write(sk, buff, strlen(buff));
        if(w < 0) {
            printf("Write Failed !\n");
            exit(1);
        }
        if(strcmp(buff, "exit") == 0) {
                printf("Client Disconnected");
                write(sk, buff, strlen(buff));
                close(sk);
                break;
            }
        bzero(buff, sizeof(buff));
        int r = read(sk, buff, sizeof(buff)-1);
        if(r <= 0) {
            printf("Client Disconnected \n");
            exit(1);
        }
        buff[r] = '\0';
        buff[strcspn(buff, "\r\n")] = '\0';
        printf("Server : %s\n", buff);
    }
    close(sk);
}