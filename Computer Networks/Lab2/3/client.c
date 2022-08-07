#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT 6000

int createClientSocket(struct sockaddr_in *address)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = inet_addr("127.0.0.1");
    address->sin_port = htons(SERVER_PORT);
    int len = sizeof(*address);
    // Connect your socket to the server’s socket
    printf("Sock fd: %d", sockfd);
    int result = connect(sockfd, (struct sockaddr *)address, len);
    if (result == -1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    return sockfd;
}

void PerformClientTask(int sockfd)
{
    int n = 1;
    int count;
    while (1)
    {

        printf("\n Enter the number of elements in the array: \t");
        scanf("%d", &count);
        int c = send(sockfd, &count, sizeof(count), 0);
        int arr[count];
        printf("Enter the elements of the array:\n");
        for (int i = 0; i < count; i++)
        {
            scanf("%d", &arr[i]);
        }

        printf("Sending array to server... \n");
        int sending = send(sockfd, arr, sizeof(arr), 0);
        while (n)
        {
            n = recv(sockfd, arr, sizeof(arr), 0);
            printf("SORTED Array from Server is:\n");
            for (int i = 0; i < count; i++)
            {
                printf("%d\t", arr[i]);
            }
            break;
        }
    }
}

int TerminateSocket(int sockfd)
{
    return close(sockfd);
}

int main()
{
    int sockfd;
    struct sockaddr_in address;

    sockfd = createClientSocket(&address);

    PerformClientTask(sockfd);
    TerminateSocket(sockfd);

    if (TerminateSocket(sockfd))
    {
        printf("\nConnection closed\n");
    }
}