#include <stdio.h>

int main()
{
    int numS = 10;
    char sect[1024];
    FILE *diskF = fopen(".", "r");
    fseek(diskF, numS * 512, SEEK_SET);
    fread(sect, 1024, 1, diskF);

    for (int i = 0; i < sizeof(sect); i++)
    {
        printf("%x", sect[i]);

        if ((i + 1) % 16 == 0)
            printf("\n");
    }
    fclose(diskF);
    return 0;
}