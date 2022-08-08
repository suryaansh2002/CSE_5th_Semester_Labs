#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define SERVER_PORT 6000

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

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

    int arrLen;
    clilen = sizeof(clilen);
    int newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
    if (fork() == 0)
    {
        n = recv(newsockfd, &arrLen, sizeof(arrLen), 0);
        int buf[arrLen];
        n = recv(newsockfd, buf, sizeof(buf), 0);
        bubbleSort(buf, arrLen);

        printf("\Array received from from port no: %d\n", cliaddr.sin_port);
        printf("\n Sending sorted array back to client\n");
        n = send(newsockfd, buf, sizeof(buf), 0);

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
