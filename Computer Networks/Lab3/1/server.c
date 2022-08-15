#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
    int sd;
    struct sockaddr_in sadd, cadd;
    // Create a UDP socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    sadd.sin_family = AF_INET;
    sadd.sin_addr.s_addr = inet_addr("127.0.0.1"); //**
    sadd.sin_port = htons(9704);
    int result = bind(sd, (struct sockaddr *)&sadd, sizeof(sadd));
    int len = sizeof(cadd);
    int rows, cols;
    int m = recvfrom(sd, &rows, sizeof(rows), 0, (struct sockaddr *)&cadd, &len);
    m = recvfrom(sd, &cols, sizeof(cols), 0, (struct sockaddr *)&cadd, &len);

    printf("The rows is %d and cols is %d\n", rows, cols);
    int mat[rows][cols];
    for (int i = 0; i < rows; i++)
    {
        int a = recvfrom(sd, mat[i], sizeof(mat[i]), 0, (struct sockaddr *)&cadd, &len);
    }
    printf("The matrix is:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}