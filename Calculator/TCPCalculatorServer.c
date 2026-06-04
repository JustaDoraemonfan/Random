#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

int main()
{
    struct sockaddr_in s,c;

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

    if(bind(sk,(struct sockaddr*)&s,sizeof(s)) < 0)
    {
        printf("Bind Failed\n");
        exit(1);
    }

    if(listen(sk,5) < 0)
    {
        printf("Listen Failed\n");
        exit(1);
    }

    socklen_t len = sizeof(c);

    while(1)
    {
        int connfd = accept(sk,(struct sockaddr*)&c,&len);

        if(connfd < 0)
            continue;

        char buff[128];

        int r = read(connfd,buff,sizeof(buff)-1);

        if(r > 0)
        {
            buff[r] = '\0';

            int a,b,ans;
            char op;
            char result[128];

            sscanf(buff,"%d %c %d",&a,&op,&b);

            switch(op)
            {
                case '+':
                    ans = a+b;
                    break;

                case '-':
                    ans = a-b;
                    break;

                case '*':
                    ans = a*b;
                    break;

                case '/':
                    if(b==0)
                    {
                        strcpy(result,"Division By Zero");
                        write(connfd,result,strlen(result));
                        close(connfd);
                        continue;
                    }
                    ans = a/b;
                    break;

                default:
                    strcpy(result,"Invalid Operator");
                    write(connfd,result,strlen(result));
                    close(connfd);
                    continue;
            }

            sprintf(result,"%d",ans);

            write(connfd,result,strlen(result));
        }

        close(connfd);
    }

    close(sk);
}