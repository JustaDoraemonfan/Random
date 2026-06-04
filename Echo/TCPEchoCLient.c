#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main() {
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    unsigned short port = 9900;
    char ip[] = "127.0.0.1";

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_aton(ip, &serv_addr.sin_addr);

    int serv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(serv_socket < 0){
        printf("Socket Failed \n");
        exit(1);
    }
    int connfd = connect(serv_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(connfd < 0) {
        printf("Cannot connect with server !");
        exit(1);
    }
    printf("Client Connected !\n");
    char buff[128];
    printf("Enter Message : ");
    fgets(buff, sizeof(buff)-1, stdin);
    buff[strcspn(buff, "\r\n")] = '\0';
    int w = write(serv_socket, buff, strlen(buff));
    if(w < 0){
        printf("Write Failed !");
        exit(1);
    }
    printf("\nMessage Sent Successfully ! \n");
    bzero(buff, sizeof(buff));

    int r = read(serv_socket, buff, sizeof(buff) - 1);
    if(r < 0) {
        printf("Cannot Read \n");
        exit(1);
    }
    buff[r] = '\0';
    printf("Server Echoed Back : %s\n", buff);
    close(serv_socket);
}