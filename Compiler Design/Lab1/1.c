#include <stdio.h>
#include <stdlib.h> // For exit()

int main()
{
	FILE *fptr1;
	int countL = 0, countC = 0;
	char filename[100], c;
	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r"); // Open one file for reading
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}

	c = fgetc(fptr1); // Read contents from file
	while (c != EOF)
	{
		if (c == '\n')
		{
			countL++;
		}
		countC++;
		c = fgetc(fptr1);
	}
	printf("No. of lines is %d and no. of characters is %d\n", countL, countC);
	fclose(fptr1);
	return 0;
}
