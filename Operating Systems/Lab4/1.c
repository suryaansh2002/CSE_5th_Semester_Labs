#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Incorrect number of arguments, Expected 1, Got: %d\n", argc - 1);
        return 0;
    }
    struct stat fstat;
    int rv = stat(argv[1], &fstat);
    if (rv != 0)
    {
        perror("stat");
        return 1;
    }
    printf("File: %s: Inode: %ld\n", argv[1], fstat.st_ino);
    return 0;
}