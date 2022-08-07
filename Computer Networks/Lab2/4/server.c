#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define SERVER_PORT 4000

int createServerSocket(struct sockaddr_in *seraddr, char IP_ADDR[])
{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr->sin_family = AF_INET;
    seraddr->sin_addr.s_addr = inet_addr(IP_ADDR);
    seraddr->sin_port = htons(SERVER_PORT);
    bind(sockfd, (struct sockaddr *)seraddr, sizeof(*seraddr));
    listen(sockfd, 5);
    printf("Sockfd: %d\n", sockfd);

    return sockfd;
}

void PerformServerTask(int sockfd)
{
    int clilen, n;
    struct sockaddr_in cliaddr;
    char buf[256];
    int a, b;
    char ch;
    clilen = sizeof(clilen);
    int newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
    if (fork() == 0)
    {
        n = recv(newsockfd, &a, sizeof(a), 0);
        printf("\nFirst no. received from client is: %d\n", a);
        n = recv(newsockfd, &b, sizeof(b), 0);
        printf("\nSecond no. received from client is: %d\n", b);
        n = recv(newsockfd, &ch, sizeof(ch), 0);
        printf("Operator received from client is: %c", ch);
        int res;
        if (ch == '+')
            res = a + b;
        if (ch == '-')
            res = a - b;
        if (ch == '*')
            res = a * b;
        if (ch == '/')
            res = a / b;

        printf("\nMessage from port no: %d\n", cliaddr.sin_port);
        n = send(newsockfd, &res, sizeof(res), 0);

        // close(newsockfd);
        // exit(0);
    }
    // Otherwise, you must be the parent and your work for this client is finished
    else
        close(newsockfd);
}

int main()
{
    int sockfd, newsockfd, portno, clilen, n = 1;

    char buf[256];
    struct sockaddr_in seraddr, cliaddr;
    int i, value;
    sockfd = createServerSocket(&seraddr, "127.0.0.1");
    while (1)
    {
        printf("server waiting\n");
        PerformServerTask(sockfd);
    }
}