%{
#include<stdio.h>
	#include<stdlib.h>
#include "3.tab.h"

%}
%%
[0-9]+ {printf("%s\n",yytext);return NUMBER;}
\n {return NL;}
[ ] {printf("\n");return BLANK;}
"+" {printf("+\n");return PLUS;}
"-" {printf("-\n");return MINUS;}
"*" {printf("*\n");return MUL;}
"/" {printf("/\n");return DIV;}
"^" {printf("^\n");return EXPO;}
%%
int yywrap()
{ return 1;
}