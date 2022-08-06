#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]){
	int sfd,i=0,k=0;
	char ch, chars[100];
	sfd=open(argv[2],O_RDONLY);
	if(sfd==-1){
		printf("No file\n");
		return 0;
	}
	while((read(sfd,&ch,1))>0){
		if(ch!='\n'){
			chars[i++]=ch;
		}
		else{
			k++;
			chars[i]='\0';
			i=0;
			if(strstr(chars,argv[1])!=NULL){
				printf("Line %d -> %s \n ", k,chars);
			}
		}
	}
	return 0;
}