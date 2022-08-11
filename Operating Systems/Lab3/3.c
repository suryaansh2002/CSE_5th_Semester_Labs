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
case 0: printf("Child: personal id = %d \t Forked id=%d Parent id = %d\n", getpid(),pid,getppid());
exit(0);
default: wait(&status);
printf("Parent: personal id = %d \t Forked id=%d Parent id = %d\n", getpid(),pid,getppid());
}
return 0;
}