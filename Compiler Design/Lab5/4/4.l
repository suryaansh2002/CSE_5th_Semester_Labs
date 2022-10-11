
%{
#include<stdio.h>
#include<stdlib.h>
%}

%%

"scanf" {fprintf(yyout,"READ");}
"printf" {fprintf(yyout,"WRITE");}

%% 
  
  
int main()                                              
{
   
yyin=fopen("input.c","r");
yyout=fopen("output.c","w+");
yylex();  
return 0; 
}
int yywrap()
{
        return 1;
}
