#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main()
{
    struct sockaddr_in serv_addr,cli_addr;

    bzero(&serv_addr,sizeof(serv_addr));

    unsigned short port = 9900;
    char ip[] = "127.0.0.1";

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_aton(ip,&serv_addr.sin_addr);

    int sk = socket(AF_INET,SOCK_DGRAM,0);

    if(sk < 0)
    {
        printf("Socket Error\n");
        exit(1);
    }

    if(bind(sk,(struct sockaddr*)&serv_addr,
            sizeof(serv_addr)) < 0)
    {
        printf("Bind Failed\n");
        exit(1);
    }

    socklen_t len = sizeof(cli_addr);

    while(1)
    {
        char buff[128];

        printf("Waiting for message...\n");

        int r = recvfrom(sk,buff,sizeof(buff)-1,0,
                         (struct sockaddr*)&cli_addr,
                         &len);

        if(r < 0)
        {
            printf("Receive Failed\n");
            continue;
        }

        buff[r] = '\0';

        printf("Message from %s : %s\n",
               inet_ntoa(cli_addr.sin_addr),
               buff);

        int w = sendto(sk,buff,strlen(buff),0,
                       (struct sockaddr*)&cli_addr,
                       len);

        if(w < 0)
        {
            printf("Send Failed\n");
            continue;
        }

        printf("Echo Sent\n");
    }

    close(sk);
}