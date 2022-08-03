#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *f1, *f2;

	char filename[100], c;

	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);

	f1 = fopen(filename, "r");
	f2 = fopen("output1.txt", "w+");

	if (f1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}

	c = fgetc(f1);
	while (c != EOF)
	{
		if (c == ' ')
		{
			fputc(' ', f2);
			while (c == ' ')
			{
				c = fgetc(f1);
			}
		}
		else if (c == '\t')
		{
			fputc(' ', f2);
			while (c == '\t')
			{
				c = fgetc(f1);
			}
		}
		else
		{
			fputc(c, f2);
			c = fgetc(f1);
		}
	}
	fclose(f1);
	fclose(f2);
	return 0;
}
