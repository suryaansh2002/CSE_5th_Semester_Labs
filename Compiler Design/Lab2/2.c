#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *f1, *f2;

	char filename[100], c;

	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);

	f1 = fopen(filename, "r");
	f2 = fopen("output2.txt", "w+");
	char *includeStr = "include", *defineStr = "define";
	if (f1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	int flag = 0, i = 0;
	char buffer[100];
	c = fgetc(f1);
	while (c != EOF)
	{

		if (c == '#' && flag == 0)
		{
			while (c != ' ')
			{
				c = fgetc(f1);
				buffer[i++] = c;
			}

			buffer[i] = '\0';
			if (strstr(buffer, includeStr) != NULL || strstr(buffer, defineStr) != NULL)
			{
				while (c != '\n')
				{
					c = fgetc(f1);
				}
			}

			else
			{
				fputc('#', f2);
				for (int j = 0; j < i; j++)
				{
					fputc(buffer[j], f2);
				}

				while (c != '\n')
				{
					c = fgetc(f1);
					fputc(c, f2);
				}
			}

			i = 0;
			buffer[i] = '\0';
		}

		else
		{
			if (flag == 0)
			{
				buffer[i++] = c;
				buffer[i] = '\0';
				if (strstr(buffer, "main") != NULL)
				{
					flag = 1;
				}
			}
			if (c == ' ' || c == '\n')
			{
				buffer[0] = '\0';
				i = 0;
			}
			fputc(c, f2);
		}
		c = fgetc(f1);
	}
	fclose(f1);
	fclose(f2);
	return 0;
}
