#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "spaces_comments.h"
#include "preprocess.h"
#define MAX_SIZE 100
char keywords[32][10] = {
    "auto",
    "double",
    "int",
    "struct",
    "break",
    "else",
    "long",
    "switch",
    "case",
    "enum",
    "register",
    "typedef",
    "char",
    "extern",
    "return",
    "union",
    "const",
    "float",
    "short",
    "unsigned",
    "continue",
    "for",
    "signed",
    "void",
    "default",
    "goto",
    "sizeof",
    "voltile",
    "do",
    "if",
    "static",
    "while"};
char operators[5] = {
    '+',
    '-',
    '/',
    '%',
    '*'};
char brackets[6] = {
    '(',
    ')',
    '[',
    ']',
    '{',
    '}'};
typedef struct token
{
    char *buf;
    int row, col;
} * Token;
Token table[MAX_SIZE];
int tCount = 0;
void addToken(char *buf, int row, int col)
{
    Token newToken = (Token)malloc(sizeof(struct token));
    newToken->buf = buf;
    newToken->row = row;
    newToken->col = col;
    table[tCount++] = newToken;
}
int compare(char buffer[])
{
    for (int i = 0; i < 32; i++)
    {
        if (strcmp(buffer, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int isOperator(char ch)
{
    for (int i = 0; i < 5; i++)
    {
        if (operators[i] == ch)
            return 1;
    }
    return 0;
}
int isBracket(char ch)
{
    for (int i = 0; i < 6; i++)
    {
        if (brackets[i] == ch)
            return 1;
    }
    return 0;
}

int main()
{
    spaces_comments();
    preprocess();

    FILE *fin = fopen("output.c", "r");
    if (fin == NULL)
    {
        printf("Cannot open file!\n");
        return 0;
    }
    char buffer[100], c = 0;
    int i = 0, row = 1, col_global = 1, col;
    while (c != EOF)
    {
        if (isalpha(c) != 0 || c == '_')
        {
            buffer[i++] = c;
            col = col_global;
            while (isalpha(c) != 0 || c == '_' || isdigit(c) != 0)
            {
                c = fgetc(fin);
                col_global++;
                if (isalpha(c) != 0 || c == '_' || isdigit(c) != 0)
                    buffer[i++] = c;
            }
            buffer[i] = '\0';
            if (compare(buffer) == 1)
            {
                printf("<%s,%d,%d>\n", buffer, row, col - 1);
                addToken(buffer, row, col - 1);
            }
            else
            {
                printf("<id,%d,%d>\n", row, col - 1);
                addToken("id", row, col - 1);
            }
            i = 0;
            if (c == '\n')
                row++, col_global = 1;
            buffer[0] = '\0';
        }
        else if (isdigit(c) != 0)
        {
            buffer[i++] = c;
            col = col_global;
            while (isdigit(c) != 0 || c == '.')
            {
                c = fgetc(fin);
                col_global++;
                if (isdigit(c) != 0 || c == '.')
                    buffer[i++] = c;
            }
            buffer[i] = '\0';
            printf("<num,%d,%d>\n", row, col - 1);
            addToken("num", row, col - 1);

            i = 0;
            if (c == '\n')
                row++, col_global = 1;
            buffer[0] = '\0';
            c = fgetc(fin);
            col_global++;
        }
        else if (c == '\"')
        {
            col = col_global;
            buffer[i++] = c;
            c = 0;
            while (c != '\"')
            {
                c = fgetc(fin);
                col_global++;
                buffer[i++] = c;
            }
            buffer[i] = '\0';
            printf("<%s,%d,%d>\n", buffer, row, col - 1);
            addToken(buffer, row, col - 1);

            buffer[0] = '\0';
            i = 0;
            c = fgetc(fin);
            col_global++;
        }
        else
        {
            col = col_global;
            if (c == '=')
            {
                c = fgetc(fin);
                col_global++;
                if (c == '=')
                {
                    printf("<==,%d,%d>\n", row, col - 1);
                    addToken("==", row, col - 1);
                }
                else
                {
                    printf("<=,%d,%d>\n", row, col - 1);
                    addToken("=", row, col - 1);

                    fseek(fin, -1, SEEK_CUR);
                    col_global--;
                }
            }
            if (c == '>' || c == '<' || c == '!')
            {
                c = fgetc(fin);
                col_global++;
                if (c == '=')
                {
                    char temp_str[3] = {c, '=', '\0'};
                    printf("<%s,%d,%d>\n", temp_str, row, col - 1);
                    addToken(temp_str, row, col - 1);
                }
                else
                {
                    printf("<%c,%d,%d>\n", c, row, col - 1);
                    addToken(&c, row, col - 1);

                    fseek(fin, -1, SEEK_CUR);
                    col_global--;
                }
            }
            if (isOperator(c) == 1 || isBracket(c) == 1)
            {

                printf("<%c,%d,%d>\n", c, row, col - 1);
                addToken(&c, row, col - 1);
            }
            if (c == '\n')
                row++, col_global = 1;
            c = fgetc(fin);
            col_global++;
        }
    }
    return 0;
}