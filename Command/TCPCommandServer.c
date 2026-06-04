#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

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
        printf("Socket Failed !\n");
        exit(1);
    }
    int b = bind(sk, (struct sockaddr*)&s, sizeof(s));
    if(b < 0) {
        printf("Bind Failed !\n");
        exit(1);
    }
    int l = listen(sk, 10);
    if(l < 0) {
        printf("Listen Failed !\n");
        exit(1);
    }
    socklen_t clen = sizeof(c);
    while(1) {
        printf("Listening for clients : \n");
        int connfd = accept(sk, (struct sockaddr*)&c, &clen);
        if(connfd < 0) {
            printf("Connection Failed !\n");
            exit(1);
        }
        printf("Connecter to client : %s\n", inet_ntoa(c.sin_addr));
        while(1){
            char cmd[512];
            char result[1028]  = "";
            int r = read(connfd, cmd, sizeof(cmd) - 1);
            if(r <= 0) {
                printf("Client Disconnected \n");
                break;
            }
            cmd[r] = '\0';
            cmd[strcspn(cmd, "\r\n")] = '\0';
            FILE *fp = popen(cmd, "r");
            if(fp == NULL) {
                strcpy(result, "Error");
            }else {
                char line[256];
                while(fgets(line, sizeof(line), fp))
                    strcat(result, line);
                pclose(fp);
            }
            FILE *f = fopen("output.txt" , "a");
            if(f != NULL) {
                fprintf(f, "Command : %s\n", cmd);
                fprintf(f, "Output : %s\n", result);
                fclose(f);
            }
            write(connfd, result, strlen(result));

        }
        close(connfd);
    }
    close(sk);
}