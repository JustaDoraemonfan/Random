#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

int binToDecimal(char *bin)
{
    int dec = 0;

    while(*bin)
    {
        dec = dec * 2 + (*bin - '0');
        bin++;
    }

    return dec;
}

void decimalToBinary(int n, char *result)
{
    char temp[64];
    int i = 0;

    if(n == 0)
    {
        strcpy(result,"0");
        return;
    }

    while(n)
    {
        temp[i++] = (n % 2) + '0';
        n /= 2;
    }

    int j = 0;

    while(i--)
        result[j++] = temp[i];

    result[j] = '\0';
}

void evaluate(char *expr, char *result)
{
    char cmd[512];

    sprintf(cmd,"echo 'scale=2;%s' | bc",expr);

    FILE *fp = popen(cmd,"r");

    if(fp == NULL)
    {
        strcpy(result,"Error");
        return;
    }

    fgets(result,100,fp);
    result[strcspn(result,"\r\n")] = '\0';

    pclose(fp);
}

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
        char buff[128];

        int r = recvfrom(sk,buff,sizeof(buff)-1,0,
                         (struct sockaddr*)&c,&clen);

        if(r < 0)
        {
            printf("Receive Failed!\n");
            continue;
        }

        buff[r] = '\0';
        buff[strcspn(buff,"\r\n")] = '\0';

        char result[128];

        if(strncmp(buff,"B ",2) == 0)
        {
            sprintf(result,"%d",binToDecimal(buff+2));
        }
        else if(strncmp(buff,"D ",2) == 0)
        {
            decimalToBinary(atoi(buff+2),result);
        }
        else if(strncmp(buff,"E ",2) == 0)
        {
            evaluate(buff+2,result);
        }
        else
        {
            strcpy(result,"Invalid Request");
        }

        sendto(sk,result,strlen(result),0,
               (struct sockaddr*)&c,clen);
    }

    close(sk);
}