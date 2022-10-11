
%{
#include<stdio.h>
#include<stdlib.h>
int s=0,p=0;
%}

%%

"scanf" {fprintf(yyout,"READ"); s++;}
"printf" {fprintf(yyout,"WRITE"); p++;}

%% 
  
  
int main()                                              
{
   
yyin=fopen("input.c","r");
yyout=fopen("output.c","w+");
yylex();  
printf("No. of scanf: %d, printf: %d",s,p);
return 0; 
}
int yywrap()
{
        return 1;
}
