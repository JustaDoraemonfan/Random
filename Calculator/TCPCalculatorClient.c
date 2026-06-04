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

    int sk = socket(AF_INET,SOCK_STREAM,0);

    if(sk < 0)
    {
        printf("Socket Failed\n");
        exit(1);
    }

    if(connect(sk,(struct sockaddr*)&s,sizeof(s)) < 0)
    {
        printf("Connection Failed\n");
        exit(1);
    }

    char buff[128];

    printf("Enter Expression (Ex: 10 + 5): ");
    fgets(buff,sizeof(buff),stdin);

    buff[strcspn(buff,"\r\n")] = '\0';

    write(sk,buff,strlen(buff));

    int r = read(sk,buff,sizeof(buff)-1);

    if(r > 0)
    {
        buff[r] = '\0';
        printf("Result = %s\n",buff);
    }

    close(sk);
}