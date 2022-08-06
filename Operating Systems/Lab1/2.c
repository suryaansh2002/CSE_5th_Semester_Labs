#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
	int sfd,i=0,k=0;
	char ch, chars[100];
	sfd=open(argv[1],O_RDONLY);
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

			printf("%d: %s\n ",k,chars);
			if(k==20){
				fgetc(stdin);
			k=0;
			}
		}
	}
	return 0;
}