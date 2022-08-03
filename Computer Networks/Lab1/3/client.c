#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>

#define SERVER_PORT 7000

int createClientSocket(	struct sockaddr_in* address){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address->sin_family=AF_INET;
	address->sin_addr.s_addr=inet_addr("127.0.0.1");
	address->sin_port=htons(SERVER_PORT);
	int len = sizeof(*address);
	//Connect your socket to the server’s socket
	printf("Sock fd: %d",sockfd);
	int result=connect(sockfd,(struct sockaddr *)address,len);
	if(result==-1)
	{
	perror("\nCLIENT ERROR");
	exit(1);
	}
	return sockfd;
}

void PerformClientTask(int sockfd){
char ch[256];
int n=1;
while(1){
printf("\nEnter Setance to send:\n");
gets(ch);
ch[strlen(ch)]='\0';
if(ch=='quit'){
	break;
}
int c=send(sockfd,ch,strlen(ch),0);
}


}

int TerminateSocket(int sockfd){
return close(sockfd);
}

int main()
{
int sockfd;
struct sockaddr_in address;

sockfd = createClientSocket(&address);

PerformClientTask(sockfd);
TerminateSocket(sockfd);

if(TerminateSocket(sockfd)){
	printf("\nConnection closed\n");
}
}