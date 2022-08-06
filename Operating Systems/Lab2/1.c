
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>

char* get_perms(__mode_t mode){
	static char local_buff[16] = {0};
	int i = 0;
	//user permissions
	local_buff[i++] = ((mode & S_IRUSR) ? 'r' : '-');
	local_buff[i++] = ((mode & S_IWUSR) ? 'w' : '-');
	local_buff[i++] = ((mode & S_IXUSR) ? 'x' : '-');
	return local_buff;
}

int main(int argc, char *argv[]){
	DIR *mydir;
	struct dirent *myfile;
	struct stat mystat;
	if(argc == 1)
		mydir = opendir(".");
	else
		mydir = opendir(argv[1]);
	
	while((myfile = readdir(mydir)) != NULL){
		stat(myfile->d_name, &mystat);
		printf("%s\t", get_perms(mystat.st_mode));
		// printf("\t%ld\t",mystat.st_size);
		printf("%s\n", myfile->d_name);
	}
	closedir(mydir);
}