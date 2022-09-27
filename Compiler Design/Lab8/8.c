#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include "nextToken.h"

#include "spaces_comments.h"

#include "preprocess.h"


void program();
void declarations();
void datatype();
void idlist();
void idlistprime();
void statementlist();
void statement();
void assignstat();
void expn();
void eprime();
void simpleexp();
void seprime();
void term();
void tprime();
void factor();
void relop();
void mulop();
void addop();


struct token tkn;
FILE * f1;
void invalid() {
   printf("error");
   exit(0);
}
void program() {

   if (strcmp(tkn.lexeme, "main") == 0) {
      tkn = getNextToken(f1);

      if (strcmp(tkn.lexeme, "(") == 0) {
         tkn = getNextToken(f1);

         if (strcmp(tkn.lexeme, ")") == 0) {
            tkn = getNextToken(f1);

            if (strcmp(tkn.lexeme, "{") == 0) {
               tkn = getNextToken(f1);
               declarations();
               statementlist();

               if (strcmp(tkn.lexeme, "}") == 0) {
                  printf("Compiled successfully");
                  return;
               } else {
                  printf("} missing at row=%d col=%d", tkn.row, tkn.col);
                  exit(1);
               }
            } else {
               printf("{ missing at row=%d col=%d", tkn.row, tkn.col);
               exit(1);
            }
         } else {
            printf(") missing at row=%d col=%d", tkn.row, tkn.col);
            exit(1);
         }
      } else {
         printf("( missing at row=%d col=%d", tkn.row, tkn.col);
         exit(1);
      }
   }
}

void declarations() {
   if (isdatatype(tkn.lexeme) == 0) {
      return;
   }

   datatype();
   idlist();
   if (strcmp(tkn.lexeme, ";") == 0) {
      tkn = getNextToken(f1);
      declarations();
   } else {
      printf("; missing at row=%d col=%d", tkn.row, tkn.col);
      exit(1);
   }
}

void datatype() {
   if (strcmp(tkn.lexeme, "int") == 0) {
      tkn = getNextToken(f1);
      printf("Type: %s\n", tkn.type);
      return;
   } else if (strcmp(tkn.lexeme, "char") == 0) {
      tkn = getNextToken(f1);
      return;
   } else {
      printf("%s Missing datatype at row=%d col=%d", tkn.lexeme, tkn.row, tkn.col);
      exit(1);
   }
}

void idlist() {
   if (strcmp(tkn.type, "identifier") == 0) {
      tkn = getNextToken(f1);
      idlistprime();
   } else {
      printf("Missing IDENTIFIER at row=%d col=%d", tkn.row, tkn.col);
   }
}

void idlistprime() {
   if (strcmp(tkn.lexeme, ",") == 0) {
      tkn = getNextToken(f1);
      idlist();
   }

   if (strcmp(tkn.lexeme, "[") == 0) {
      tkn = getNextToken(f1);
      if (strcmp(tkn.type, "number") == 0) {
         tkn = getNextToken(f1);
         if (strcmp(tkn.lexeme, "]") == 0) {
            tkn = getNextToken(f1);
            if (strcmp(tkn.lexeme, ",") == 0) {
               tkn = getNextToken(f1);
               idlist();
            } else {
               return;
            }
         }
      }
   } else {
      return;
   }
}

void statementlist() {
   if (strcmp(tkn.type, "identifier") != 0) {
      return;
   }

   statement();
   statementlist();
}

void statement() {
   assignstat();

   if (strcmp(tkn.lexeme, ";") == 0) {
      tkn = getNextToken(f1);
      return;
   }
}
void assignstat() {
   if (strcmp(tkn.type, "identifier") == 0) {
      tkn = getNextToken(f1);

      if (strcmp(tkn.lexeme, "=") == 0) {
         tkn = getNextToken(f1);
         expn();
      } else {
         printf("= missing at row=%d col=%d", tkn.row, tkn.col);
         exit(1);
      }
   } else {
      printf("Missing identifier at row=%d col=%d", tkn.row, tkn.col);
      exit(1);
   }
}

void expn() {
   simpleexp();
   eprime();
}

void eprime() {
   if (isrel(tkn.lexeme) == 0) {
      return;
   }

   relop();
   simpleexp();
}

void simpleexp() {
   term();
   seprime();
}

void seprime() {
   if (isadd(tkn.lexeme) == 0) {
      return;
   }

   addop();
   term();
   seprime();
}

void term() {
   factor();
   tprime();
}

void tprime() {
   if (ismul(tkn.lexeme) == 0) {
      return;
   }

   mulop();
   factor();
   tprime();
}

void factor() {
   if (strcmp(tkn.type, "identifier") == 0) {
      tkn = getNextToken(f1);
      return;
   } else if (strcmp(tkn.type, "number") == 0) {
      tkn = getNextToken(f1);
      return;
   }
}

void relop() {
   if (strcmp(tkn.lexeme, "==") == 0) {
      tkn = getNextToken(f1);
      return;

   }
   if (strcmp(tkn.lexeme, "!=") == 0) {
      tkn = getNextToken(f1);
      return;
   }

   if (strcmp(tkn.lexeme, "<=") == 0) {
      tkn = getNextToken(f1);
      return;
   }

   if (strcmp(tkn.lexeme, ">=") == 0) {
      tkn = getNextToken(f1);
      return;
   }

   if (strcmp(tkn.lexeme, "<") == 0) {
      tkn = getNextToken(f1);
      return;
   }

   if (strcmp(tkn.lexeme, ">") == 0) {
      tkn = getNextToken(f1);
      return;
   }
}

void addop() {
   if (strcmp(tkn.lexeme, "+") == 0) {
      tkn = getNextToken(f1);
      return;
   }

   if (strcmp(tkn.lexeme, "-") == 0) {
      tkn = getNextToken(f1);
      return;
   }
}

void mulop() {
   if (strcmp(tkn.lexeme, "*") == 0) {
      tkn = getNextToken(f1);
      return;
   }

   if (strcmp(tkn.lexeme, "/") == 0) {
      tkn = getNextToken(f1);
      return;
   }

   if (strcmp(tkn.lexeme, "%") == 0) {
      tkn = getNextToken(f1);
      return;
   }
}

int main() {
   spaces_comments();
   preprocess();
   f1 = fopen("output.c", "r");
   if (f1 == NULL) {
      printf("Error! File cannot be opened!\n");
      return 0;
   }
   tkn = getNextToken(f1);
   program();
   char c = fgetc(f1);
   if (c == EOF) {
      printf("\n Syntaxt Correct. Reached EOF\n\n");
   }
   fclose(f1);
}