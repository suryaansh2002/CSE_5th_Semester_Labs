#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
pid_t pid;
int status;
pid = fork();
switch(pid){
case -1: printf("Error occured!...\n");
exit(-1);
case 0: 
printf("Child process of main program: Personal id: %d \n\n", getpid());
printf("Executing Previous Question\n");

execlp("./1","1",NULL);
exit(0);
default: wait(&status);
printf("\nParent Process of main :\n personal id = %d \t Forked id=%d Parent id = %d\n", getpid(),pid,getppid());
}
return 0;
}