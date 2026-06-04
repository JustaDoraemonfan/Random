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

    int sk = socket(AF_INET,SOCK_DGRAM,0);

    if(sk < 0)
    {
        printf("Socket Failed!\n");
        exit(1);
    }

    if(bind(sk,(struct sockaddr*)&s,sizeof(s)) < 0)
    {
        printf("Bind Failed!\n");
        exit(1);
    }

    socklen_t clen = sizeof(c);

    while(1)
    {
        char cmd[512];
        char result[1028] = "";

        int r = recvfrom(sk,cmd,sizeof(cmd)-1,0,
                         (struct sockaddr*)&c,&clen);

        if(r < 0)
        {
            printf("Receive Error\n");
            continue;
        }

        cmd[r] = '\0';
        cmd[strcspn(cmd,"\r\n")] = '\0';

        FILE *fp = popen(cmd,"r");

        if(fp == NULL)
        {
            strcpy(result,"Command Error\n");
        }
        else
        {
            char line[256];

            while(fgets(line,sizeof(line),fp))
                strcat(result,line);

            pclose(fp);

            if(strlen(result)==0)
                strcpy(result,"No Output\n");
        }

        FILE *f = fopen("output.txt","a");

        if(f != NULL)
        {
            fprintf(f,"\nCommand : %s\n",cmd);
            fprintf(f,"Output :\n%s\n",result);
            fclose(f);
        }

        sendto(sk,result,strlen(result),0,
               (struct sockaddr*)&c,clen);
    }

    close(sk);
    return 0;
}