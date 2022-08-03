#include <time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>

#define SERVER_PORT 7000

int createServerSocket(struct sockaddr_in* seraddr, char IP_ADDR[]){

	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	seraddr->sin_family = AF_INET;
	seraddr->sin_addr.s_addr=inet_addr(IP_ADDR);
	seraddr->sin_port = htons(SERVER_PORT);
	bind(sockfd,(struct sockaddr *)seraddr,sizeof(*seraddr));
	listen(sockfd,5);
	printf("Sockfd: %d\n",sockfd);

	return sockfd;
}

void PerformServerTask(int sockfd){
int clilen,cliaddr,n;

clilen = sizeof(clilen);
int newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);

time_t rawtime;
struct tm * timeinfo;

time ( &rawtime );
timeinfo = localtime ( &rawtime );
printf(" \nClient Asking for time \n");
printf("Time is %s",asctime (timeinfo));
n = send(newsockfd,asctime (timeinfo),strlen(asctime (timeinfo)),0);


}

int main()
{
int sockfd;
struct sockaddr_in seraddr;

sockfd = createServerSocket(&seraddr,"127.0.0.1");

while (1) {
printf("server waiting");
PerformServerTask(sockfd);
}

}