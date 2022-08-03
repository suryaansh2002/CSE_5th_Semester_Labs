#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT 7000

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
	int clilen, cliaddr, n;
	char buf[256];

	clilen = sizeof(clilen);
	int newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

	n = recv(newsockfd, buf, strlen(buf), 0);

	printf(" \nMessage from Client %s \n", buf);

	n = send(newsockfd, buf, sizeof(buf), 0);
}

int main()
{
	int sockfd;
	struct sockaddr_in seraddr;
	sockfd = createServerSocket(&seraddr, "127.0.0.1");

	while (1)
	{
		printf("server waiting");
		PerformServerTask(sockfd);
	}
}