#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
    struct sockaddr_in s;

    bzero(&s,sizeof(s));

    s.sin_family = AF_INET;
    s.sin_port = htons(9000);
    inet_aton("127.0.0.1",&s.sin_addr);

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

        sendto(sk,buff,strlen(buff),0,
               (struct sockaddr*)&s,
               sizeof(s));

        if(strcmp(buff,"exit") == 0)
        {
            close(sk);
            break;
        }

        int r = recvfrom(sk,buff,sizeof(buff)-1,0,
                         NULL,NULL);

        if(r < 0)
        {
            printf("Read Failed\n");
            exit(1);
        }

        buff[r] = '\0';

        printf("Server : %s\n",buff);

        if(strcmp(buff,"exit") == 0)
            break;
    }

    close(sk);
}