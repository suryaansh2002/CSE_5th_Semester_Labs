#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
char *get_perms(__mode_t mode)
{
    static char local_buff[16] = {0};
    int i = 0;
    // user permissions
    local_buff[i++] = ((mode & S_IRUSR) ? 'r' : '-');
    local_buff[i++] = ((mode & S_IWUSR) ? 'w' : '-');
    local_buff[i++] = ((mode & S_IXUSR) ? 'x' : '-');
    return local_buff;
}

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
    printf("File Name: %s\n"
           "Inode: %ld\n"
           "Container Device ID: %ld\n"
           "Permissions: %s\n"
           "Hard Links: %ld\n"
           "User ID: %d\n"
           "Group ID: %d\n"
           "Device ID: %ld\n"
           "Total Size: %ld\n"
           "Block Size: %ld\n"
           "Number of blocks: %ld\n"
           "Last Access Time: %s"
           "Last Modified: %s"
           "Last Status: %s",
           argv[1],
           fstat.st_ino,
           fstat.st_dev,
           get_perms(fstat.st_mode),
           fstat.st_nlink,
           fstat.st_uid,
           fstat.st_gid,
           fstat.st_rdev,
           fstat.st_size,
           fstat.st_blksize,
           fstat.st_blocks,
           ctime(&fstat.st_atime),
           ctime(&fstat.st_mtime),
           ctime(&fstat.st_ctime));
    return 0;
}