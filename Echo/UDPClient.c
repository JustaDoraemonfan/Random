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
    struct sockaddr_in serv_addr;
    bzero(&serv_addr,sizeof(serv_addr));

    unsigned short port = 9900;
    char ip[] = "127.0.0.1";

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_aton(ip,&serv_addr.sin_addr);

    int sk = socket(AF_INET,SOCK_DGRAM,0);

    if(sk < 0)
    {
        printf("Socket Failed\n");
        exit(1);
    }

    char buff[128];

    printf("Enter Message : ");
    fgets(buff,sizeof(buff),stdin);

    buff[strcspn(buff,"\r\n")] = '\0';

    int w = sendto(sk,buff,strlen(buff),0,
                   (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr));

    if(w < 0)
    {
        printf("Send Failed\n");
        exit(1);
    }

    printf("Message Sent Successfully!\n");

    bzero(buff,sizeof(buff));

    int r = recvfrom(sk,buff,sizeof(buff)-1,0,
                     NULL,NULL);

    if(r < 0)
    {
        printf("Receive Failed\n");
        exit(1);
    }

    buff[r] = '\0';

    printf("Server Echoed Back : %s\n",buff);

    close(sk);
}