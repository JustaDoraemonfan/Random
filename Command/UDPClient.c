#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

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
        printf("Socket Failed!\n");
        exit(1);
    }

    while(1)
    {
        char cmd[512];
        char result[1028];

        printf("Enter Command : ");

        fgets(cmd,sizeof(cmd),stdin);

        cmd[strcspn(cmd,"\n")] = '\0';

        if(strcmp(cmd,"exit")==0)
            break;

        sendto(sk,cmd,strlen(cmd),0,
               (struct sockaddr*)&s,sizeof(s));

        int r = recvfrom(sk,result,sizeof(result)-1,0,
                         NULL,NULL);

        if(r < 0)
        {
            printf("Receive Error\n");
            continue;
        }

        result[r] = '\0';

        printf("\nOutput:\n%s\n",result);
    }

    close(sk);
    return 0;
}