#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
    int sd;
    struct sockaddr_in address;
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); //**
    address.sin_port = htons(9704);
    printf("Enter no. of rows in matrix:");
    int rows;
    scanf("%d", &rows);
    printf("Enter no. of columns in matrix:");
    int cols;
    scanf("%d", &cols);

    int len = sizeof(address);

    int m = sendto(sd, &rows, sizeof(rows), 0, (struct sockaddr *)&address, len);
    int c = sendto(sd, &cols, sizeof(rows), 0, (struct sockaddr *)&address, len);
    for (int i = 0; i < rows; i++)
    {
        int arr[cols];
        printf("Enter the elements of row %d:\n", i + 1);
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", &arr[j]);
        }
        int n = sendto(sd, arr, sizeof(arr), 0, (struct sockaddr *)&address, len);
    }
    return 0;
}