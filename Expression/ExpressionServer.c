#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
int binToDecimal(char *bin) {
    int dec = 0;
    while(*bin) {
        dec = dec * 2 + (*bin - '0');
        bin++;
    }
    return dec;
}
void decimalToBinary(int n, char *result){
    char temp[64];
    int i=0;
    if(n == 0) {
        strcpy(result, "0");
        return;
    }
    while(n) {
        temp[i++] = (n % 2) + '0';
        n /= 2;
    }
    int j = 0;
    while(i--) {
        result[j++] = temp[i]; 
    }
    result[j] = '\0';
}
void evaluate(char *expr, char *result) {
    char cmd[512];
    sprintf(cmd, "echo 'scale=2;%s' | bc", expr);
    FILE *fp = popen(cmd, "r");
    if(fp == NULL){
        strcpy(result, "Error");
        return;
    }
    fgets(result, 100, fp);
    result[strcspn(result, "\r\n")] = '\0';
    pclose(fp);
}

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
        while(1) {
            char buff[128];
            int r = read(connfd, buff, sizeof(buff)-1);
            buff[r] = '\0';
            buff[strcspn(buff, "\r\n")] = '\0';
            char result[128];
            if(strncmp(buff, "B ", 2) == 0) {
                sprintf(result, "%d", binToDecimal(buff+2));
            }else if(strncmp(buff, "D ", 2) == 0) {
                decimalToBinary(atoi(buff+2), result);
            }else if(strncmp(buff, "E ", 2) == 0) {
                evaluate(buff+2, result);
            }
            int w = write(connfd, result, strlen(result));
        }
        close(connfd);
    }
    close(sk);
}