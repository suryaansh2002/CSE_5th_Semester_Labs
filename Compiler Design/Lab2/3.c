#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

char keywords[5][10] = {
    "int",
    "float",
    "char",
    "double",
    "main"};
int compare(char buffer[])
{
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(buffer, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}
int main()
{
    char filename[100], c;

    printf("Enter the filename to open for reading: \n");
    scanf("%s", filename);

    FILE *f1 = fopen(filename, "r");
    if (f1 == NULL)
    {
        printf("Cannot find file!\n");
        exit(0);
    }
    char buffer[100];
    int i = 0;
    while (c != EOF)
    {
        if (isalpha(c) == 0)
        {
            printf("%c", c);
        }
        if (isalpha(c) != 0)
        {
            while (isalpha(c) != 0)
            {
                c = fgetc(f1);
                if (isalpha(c) != 0)
                    buffer[i++] = c;
            }
            buffer[i] = '\0';
            if (isalpha(c) == 0)
            {
                printf("%c", c);
            }

            if (compare(buffer) == 1)
            {
                for (int j = 0; j < i; j++)
                {
                    printf("%c", toupper(buffer[j]));
                }
            }
            else
            {
                for (int j = 0; j < i; j++)
                {
                    printf("%c", buffer[j]);
                }
            }
            i = 0;
            buffer[0] = '\0';
        }
        else
        {
            c = fgetc(f1);
            if (isalpha(c) != 0)
                buffer[i++] = c;
        }
    }
    fclose(f1);
    return 0;
}