#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
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

    clilen = sizeof(clilen);
    int newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

    if (fork() == 0)
    {
        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        printf(" \nClient Asking for time \n");
        printf("Time is %s", asctime(timeinfo));
        n = send(newsockfd, asctime(timeinfo), strlen(asctime(timeinfo)), 0);

        close(newsockfd);
        exit(0);
    }
    // Otherwise, you must be the parent and your work for this client is finished
    else
        close(newsockfd);
}

int main()
{
    int sockfd;
    struct sockaddr_in seraddr;
    sockfd = createServerSocket(&seraddr, "127.0.0.1");
    while (1)
    {
        printf("server waiting\n");
        PerformServerTask(sockfd);
    }
}