#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct sockaddr_in s;

int skfd;
char sbuff[256];
char rbuff[256];

int main()
{
    bzero(&s, sizeof(s));

    s.sin_family = AF_INET;
    s.sin_port = htons(9000);
    inet_aton("127.0.0.1", &s.sin_addr);

    if ((skfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Error\n");
        exit(1);
    }

    if (connect(skfd, (struct sockaddr *)&s, sizeof(s)) < 0)
    {
        printf("Connection Error\n");
        close(skfd);
        exit(1);
    }

    while (1)
    {
        printf("\nEnter Request (BIN/DEC/EXP) or EXIT:\n");

        fgets(sbuff, sizeof(sbuff), stdin);
        sbuff[strcspn(sbuff, "\n")] = '\0';

        if (strcmp(sbuff, "EXIT") == 0)
            break;

        send(skfd, sbuff, strlen(sbuff), 0);

        int r = recv(skfd, rbuff, sizeof(rbuff), 0);

        if (r < 0)
        {
            printf("Receive Error\n");
            continue;
        }

        rbuff[r] = '\0';

        printf("Result = %s\n", rbuff);
    }

    close(skfd);

    return 0;
}