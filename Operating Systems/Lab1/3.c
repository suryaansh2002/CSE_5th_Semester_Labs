#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(){
int a = 18;
float b = 9.69;
char c = 'F';
char str[] = "Suryaansh";
printf("a = %d, b = %f, c = %c, str = %s, Hexadecimal for a = %x\n",a,b,c,str,a);
errno = ENOENT;
printf("Error Access Number : %m\n");
}