%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
	
%}


%token NL NUMBER PLUS MINUS MUL DIV EXPO BLANK 

%%

stmt:	input NL
	;
input:	input line
	|
	;
line:	exp
	;
exp:	NUMBER 
	| exp exp PLUS 
	| exp exp MINUS 
	| exp exp MUL 
	| exp exp DIV 
	| exp exp EXPO 
	| exp BLANK
	| exp
	;

%%

int yyerror(char *msg)
{
	printf("Invalid Expression\n");
	return 1;
 	
}

void main ()
{
	printf("Enter the expression\n");
	
	yyin=fopen("in.txt","r");
	//yyin=stdin;
do
{
if(yyparse())
{
printf("\n Failure");
exit(0);}
}while(!feof(yyin));
printf("success");
}