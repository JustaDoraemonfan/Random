#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

#define SIZE 4096

int main()
{
    struct sockaddr_in s;
    bzero(&s,sizeof(s));

    s.sin_family = AF_INET;
    s.sin_port = htons(9000);
    inet_aton("127.0.0.1",&s.sin_addr);

    int sk = socket(AF_INET,SOCK_STREAM,0);

    if(sk < 0)
    {
        printf("Socket Error\n");
        exit(1);
    }

    if(connect(sk,(struct sockaddr*)&s,sizeof(s)) < 0)
    {
        printf("Connection Error\n");
        close(sk);
        exit(1);
    }

    while(1)
    {
        char cmd[512];
        char result[SIZE];

        printf("\nEnter Unix Command (or exit): ");
        fgets(cmd,sizeof(cmd),stdin);

        cmd[strcspn(cmd,"\n")] = '\0';

        send(sk,cmd,strlen(cmd),0);

        if(strcmp(cmd,"exit") == 0)
            break;

        int r = recv(sk,result,sizeof(result)-1,0);

        if(r <= 0)
        {
            printf("Server Disconnected\n");
            break;
        }

        result[r] = '\0';

        printf("\n----- OUTPUT -----\n");
        printf("%s",result);
        printf("------------------\n");
    }

    close(sk);
    return 0;
}