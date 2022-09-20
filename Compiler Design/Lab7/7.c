#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nextToken.h"
#include "spaces_comments.h"

#include "preprocess.h"


void program();
void declarations();
void data_type();
void identifier_list();
void assign_stat();


struct token curr;
FILE *f1;
void invalid(){
  printf("error");
  exit(0);
}
void program()
{
  
  if(strcmp(curr.lexeme,"main")==0)
  {
    curr=getnexttoken(f1);
    if(strcmp(curr.lexeme,"(")==0)
    {
      curr=getnexttoken(f1);
      if(strcmp(curr.lexeme,")")==0)
      {
        curr=getnexttoken(f1);
        if(strcmp(curr.lexeme,"{")==0)
        {
          curr=getnexttoken(f1);
          declarations();
          assign_stat();
          if(strcmp(curr.lexeme,"}")==0)
          {
            return;
          }
          else 
        {
          printf("\nMissing } at row:%d and col:%d.\n\n",curr.row,curr.col);
          exit(0);
        }
        }
        else 
        {
          printf("\nMissing { at row:%d and col:%d.\n\n",curr.row,curr.col);
          exit(0);
        }
      }
      else 
        {
          printf("\nMissing ) at row:%d and col:%d.\n\n",curr.row,curr.col);
          exit(0);
        }
    }
    else 
        {
          printf("\nMissing ( at row:%d and col:%d.\n\n",curr.row,curr.col);
          exit(0);
        }
  }
  else 
        {
          printf("\nMissing main function\n\n");
          exit(0);
        }
}


void declarations()
{
  if(isdatatype(curr.lexeme)==0)
  {
    return;
  }
  data_type();
  identifier_list();
  if(strcmp(curr.lexeme,";")==0)
  {
    curr=getnexttoken(f1);
    declarations();
  }
  else {printf("\nMissing ; at row:%d and col:%d.\n\n",curr.row,curr.col); exit(0);}



}


void data_type()
{
  if(strcmp(curr.lexeme,"int")==0)
  {
    curr=getnexttoken(f1);
    return;
  }
  else if(strcmp(curr.lexeme,"char")==0)
  {
    curr=getnexttoken(f1);
    return;
  }
  else 
        {
          printf("\nMissing data type at row:%d and col:%d.\n\n",curr.row,curr.col);
          exit(0);
        }

}


void identifier_list()
{
  if(strcmp(curr.type,"identifier")==0)
  {
    curr=getnexttoken(f1);
    if(strcmp(curr.lexeme,",")==0)
    {
      curr=getnexttoken(f1);
      identifier_list();
    }
    else return;
  }


  else 
    {
      printf("\nMissing identifier at row:%d and col:%d.\n\n",curr.row,curr.col);
      exit(0);
    }
}


void assign_stat()
{
  if(strcmp(curr.type,"identifier")==0)
  {
    curr=getnexttoken(f1);
    if(strcmp(curr.lexeme,"=")==0)
    {
      curr=getnexttoken(f1);
      if(strcmp(curr.type,"identifier")==0)
      {
        curr=getnexttoken(f1);
        if(strcmp(curr.lexeme,";")==0)
        {
          curr=getnexttoken(f1);
          return;
        }
      }


    else if(strcmp(curr.type,"number")==0)
    {
      curr=getnexttoken(f1);
        if(strcmp(curr.lexeme,";")==0)
        {
          curr=getnexttoken(f1);
          return;
        }
        else 
        {
          printf("\nMissing ; at row:%d and col:%d.\n\n",curr.row,curr.col);
          exit(0);
        }


    }
    else 
        {
          printf("\nMissing identifier at row:%d and col:%d.\n\n",curr.row,curr.col);
          exit(0);
        }
    }
    else 
        {
          printf("\nMissing = at row:%d and col:%d.\n\n",curr.row,curr.col);
          exit(0);
        }
  }
  else 
        {
          printf("\nMissing identifier at row:%d and col:%d.\n\n",curr.row,curr.col);
          exit(0);
        }
}


int main()
{
  spaces_comments();
  preprocess();
  f1=fopen("output.c","r");
  if(f1==NULL)
   {
     printf("Error! File cannot be opened!\n");
     return 0;
   }
  struct token tkn;
  curr=getnexttoken(f1);
  program();
  char c=fgetc(f1);
  if(c==EOF){
  printf("\n Syntaxt Correct. Reached EOF\n\n");    
  }
fclose(f1);
}