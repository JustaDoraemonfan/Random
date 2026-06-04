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

    if ((skfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("Socket Error\n");
        exit(1);
    }

    while (1)
    {
        printf("\nEnter Request (B/D/E) or EXIT:\n");

        fgets(sbuff, sizeof(sbuff), stdin);
        sbuff[strcspn(sbuff, "\n")] = '\0';

        if (strcmp(sbuff, "EXIT") == 0)
            break;

        sendto(skfd, sbuff, strlen(sbuff), 0,
               (struct sockaddr *)&s, sizeof(s));

        int r = recvfrom(skfd, rbuff, sizeof(rbuff)-1, 0,
                         NULL, NULL);

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