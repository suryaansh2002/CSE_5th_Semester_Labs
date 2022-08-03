#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/stat.h>

int main()
{
	FILE *fa, *fb;
	char ch, fileData[500];
	int i = 1;
	char filename[100];
	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);
	fa = fopen(filename, "r");
	fb = fopen("output.txt", "w+");
	if (!fa)
	{
		printf("Cannot open the file\n");
		exit(1);
	}
	fseek(fa, 0, SEEK_END);
	int size = ftell(fa);
	while (i < size + 1)
	{
		fseek(fa, -i, SEEK_END);
		ch = getc(fa);
		fputc(ch, fb);
		i++;
	}
	printf("Reverse of contents of file saved to output.txt \n");

	printf("File size is : %d\n", size);
	fclose(fa);
}
