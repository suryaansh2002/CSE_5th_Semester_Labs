#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Incorrect number of arguments, Expected 1, Got: %d", argc - 1);
        return 0;
    }
    char *oldpath = argv[1];
    char *newpath = "newfilepath.txt";
    struct stat fstat;
    printf("Before linking new link:\n");
    system("ls");
    int rv = stat(oldpath, &fstat);
    if (rv != 0)
    {
        perror("stat");
        return 1;
    }
    printf("Number of links before linking: %ld\n", fstat.st_nlink);
    link(oldpath, newpath);
    printf("After linking new link:\n");
    system("ls");
    int rv_2 = stat(newpath, &fstat);
    if (rv_2 != 0)
    {
        perror("stat");
        return 1;
    }
    printf("Number of hard links after linking: %ld\nThe new path is: %s\n",
           fstat.st_nlink, newpath);
    unlink(oldpath);
    printf("After unlinking old link:\n");
    system("ls");
    int rv_3 = stat(newpath, &fstat);
    if (rv_3 != 0)
    {
        perror("stat");
        return 1;
    }
    printf("Number of links after unlinking: %ld\n", fstat.st_nlink);
    return 0;
}