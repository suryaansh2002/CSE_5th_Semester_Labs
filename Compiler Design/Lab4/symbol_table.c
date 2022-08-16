#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include "spaces_comments.h"

#include "preprocess.h"

#define MAX_SIZE 20

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
    "while"}; // list of keywords
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
char data_types[][10] = {
    "double",
    "int",
    "char",
    "float"};
char special_symbols[12] = {
    '*',
    ';',
    ':',
    '.',
    ',',
    '^',
    '&',
    '!',
    '>',
    '<',
    '~',
    '`'};

// element structure for symbol table created:
typedef struct symbol
{
    char *name;
    char *data_type;
    struct symbol *next;
    char *rtype;
    int size;

} * Symbol;
Symbol st[MAX_SIZE]; // symbol table created

// to check for comparision
int isKeyword(char buffer[])
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

int isDatatype(char buffer[])
{
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(buffer, data_types[i]) == 0)
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

int isSpecialSymbol(char c)
{
    for (int i = 0; i < 12; i++)
    {
        if (special_symbols[i] == c)
            return 1;
    }
    return 0;
}

// creating a hashing function
int hash(int size)
{
    return (size % MAX_SIZE);
}

void displaySymbolTable()
{
    printf("\nSymbol table\nSize \t\t Lexene Name\t\t DType\t\t Return Type\n\n");
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (st[i] == NULL)
            continue;
        else
        {
            Symbol cur = st[i];
            while (cur)
            {
                printf(" %d\t\t %s\t\t %s\t\t %s \n", cur->size, cur->name, cur->data_type, cur->rtype);
                cur = cur->next;
            }
        }
    }
}

// searching in the symbol table
int searchSymbolTable(char identifier[])
{
    int index = hash(strlen(identifier));
    if (st[index] == NULL)
        return -1;
    Symbol cur = st[index];
    int i = 0;
    while (cur != NULL)
    {
        if (strcmp(identifier, cur->name) == 0)
            return i;
        cur = cur->next;
        i++;
    }
    return -1;
}

// inserting in the symbol table
void insertSymbolTable(char identifier[], char data_type[], char rtype[])
{
    if (searchSymbolTable(identifier) == -1)
    {
        Symbol n = (Symbol)malloc(sizeof(struct symbol));
        char *str = (char *)calloc(strlen(identifier) + 1, sizeof(char));
        strcpy(str, identifier);
        n->name = str;
        n->next = NULL;
        char *type = (char *)calloc(strlen(data_type) + 1, sizeof(char));
        strcpy(type, data_type);
        n->data_type = type;
        if (!rtype || strlen(rtype) < 1)
        {
            n->rtype = "NULL";
        }
        else
        {
            char *temp = (char *)calloc(strlen(rtype) + 1, sizeof(char));
            strcpy(temp, rtype);
            n->rtype = temp;
        }
        if (strcmp(data_type, "int") == 0)
            n->size = 4;
        else if (strcmp(data_type, "double") == 0)
            n->size = 8;
        else if (strcmp(data_type, "char") == 0)
            n->size = 1;
        else if (strcmp(data_type, "function") == 0)
            n->size = 0;
        else
            n->size = 4;
        int index = hash(strlen(identifier));
        if (st[index] == NULL)
        {
            st[index] = n;
            return;
        }
        Symbol cur = st[index];
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = n;
    }
}

int main()
{
    spaces_comments();
    preprocess();
    int rowNum = 1;

    FILE *fin = fopen("output.c", "r");
    if (fin == NULL)
    {
        printf("Cannot open file!\n");
        return 0;
    }
    char buffer[100], c = 0, data_type_buffer[100];
    int i = 0, col_global = 1, col, temp_row = rowNum;
    while (temp_row > 0)
    {
        c = fgetc(fin);
        if (c == '\n')
            temp_row--;
    }
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
            if (isDatatype(buffer) == 1)
            {
                printf("<%s,%d,%d,Keyword>\n", buffer, rowNum, col - 1);
                strcpy(data_type_buffer, buffer);
            }
            else if (isKeyword(buffer) == 1)
            {
                printf("<%s,%d,%d,Keyword>\n", buffer, rowNum, col - 1);
            }
            else
            {
                printf("<%s,%d,%d,Identifier>\n", buffer, rowNum, col - 1);

                if (c == '(')
                    // Do not include predefined functions
                    if (strstr(buffer, "printf") || strstr(buffer, "scanf"))
                    {
                    }
                    else
                    {
                        insertSymbolTable(buffer, "function", data_type_buffer);
                    }
                else
                    insertSymbolTable(buffer, data_type_buffer, NULL);
                data_type_buffer[0] = '\0';
            }
            i = 0;
            if (c == '\n')
                rowNum++, col_global = 1;
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
            printf("<%s,%d,%d,Number>\n", buffer, rowNum, col - 1);

            i = 0;
            if (c == '\n')
                rowNum++, col_global = 1;
            buffer[0] = '\0';
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
            printf("<%s,%d,%d,String>\n", buffer, rowNum, col - 1);

            buffer[0] = '\0';
            i = 0;
            c = fgetc(fin);
            col_global++;
        }
        else if (c == '\'')
        {
            col = col_global;
            buffer[i++] = c;
            c = 0;
            c = fgetc(fin);
            col_global++;
            buffer[i++] = c;
            if (c == '\\')
            {
                c = fgetc(fin);
                col_global++;
                buffer[i++] = c;
            }
            c = fgetc(fin);
            col_global++;
            buffer[i++] = c;
            buffer[i] = '\0';

            // character constants
            buffer[0] = '\0';
            i = 0;
            c = fgetc(fin);
            col_global++;
        }
        else
        {
            col = col_global;
            if (c == '=')
            { // relational and logical operators
                c = fgetc(fin);
                col_global++;
                if (c == '=')
                {
                    printf("<==,%d,%d,RELATIONAL_OPERATOR>\n", rowNum, col - 1);
                }
                else
                {

                    printf("<=,%d,%d,CHARACTER_CONSTANT>\n", rowNum, col - 1);

                    fseek(fin, -1, SEEK_CUR);
                    col_global--;
                }
            }
            else if (c == '>' || c == '<' || c == '!')
            {
                char temp = c;
                c = fgetc(fin);
                col_global++;
                if (c == '=')
                {
                    char temp_str[3] = {
                        temp,
                        '=',
                        '\0'};

                    printf("<%s,%d,%d,RELATIONAL_OPERATOR>\n", temp_str, rowNum, col - 1);
                }
                else
                {
                    char temp_str[2] = {
                        temp,
                        '\0'};

                    printf("<%s,%d,%d,RELATIONAL_OPERATOR>\n", temp_str, rowNum, col - 1);

                    fseek(fin, -1, SEEK_CUR);
                    col_global--;
                }
            }
            else if (isBracket(c) == 1)
            {
                char temp_string[2] = {
                    c,
                    '\0'};
                printf("<%s,%d,%d,BRACKET>\n", temp_string, rowNum, col - 1);
            }
            else if (isSpecialSymbol(c) == 1)
            {
                char temp_string[2] = {
                    c,
                    '\0'};
                printf("<%s,%d,%d,SPECIAL_SYMBOL>\n", temp_string, rowNum, col - 1);
            }
            else if (isOperator(c) == 1)
            {
                char temp = c;
                c = fgetc(fin);
                col_global++;
                if (c == '=' || (temp == '+' && c == '+') || (temp == '-' && c == '-'))
                {
                    char temp_string[3] = {
                        temp,
                        c,
                        '\0'};
                    printf("<%s,%d,%d,OPERATOR>\n", temp_string, rowNum, col - 1);
                }
                else
                {
                    char temp_String[2] = {
                        temp,
                        '\0'};
                    printf("<%s,%d,%d,OPERATOR>\n", temp_String, rowNum, col - 1);

                    fseek(fin, -1, SEEK_CUR);
                    col_global--;
                }
            }
            else if (c == '\n')
                rowNum++, col_global = 1;
            c = fgetc(fin);
            col_global++;
        }
    }
    displaySymbolTable();
    return 0;
}