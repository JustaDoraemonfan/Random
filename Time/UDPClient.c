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
    struct sockaddr_in s;
    bzero(&s,sizeof(s));

    unsigned short port = 9000;
    char ip[] = "127.0.0.1";

    s.sin_family = AF_INET;
    s.sin_port = htons(port);
    inet_aton(ip,&s.sin_addr);

    int sk = socket(AF_INET,SOCK_DGRAM,0);

    if(sk < 0)
    {
        printf("Socket Failed\n");
        exit(1);
    }

    while(1)
    {
        char buff[128];

        printf("Client : ");
        fgets(buff,sizeof(buff)-1,stdin);

        buff[strcspn(buff,"\r\n")] = '\0';

        if(sendto(sk,buff,strlen(buff),0,
                  (struct sockaddr*)&s,
                  sizeof(s)) < 0)
        {
            printf("Send Failed\n");
            break;
        }

        if(strcmp(buff,"exit") == 0)
        {
            printf("Client Disconnected\n");
            break;
        }

        int r = recvfrom(sk,buff,sizeof(buff)-1,0,
                         NULL,NULL);

        if(r < 0)
        {
            printf("Receive Failed\n");
            break;
        }

        buff[r] = '\0';

        printf("Server : %s\n",buff);
    }

    close(sk);
}