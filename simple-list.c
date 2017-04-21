#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <malloc.h>
#include <unistd.h>

size_t file_list(const char *path, char ***ls) {
    size_t count = 0;
    size_t length = 0;
    DIR *dp = NULL;
    struct dirent *ep = NULL;

    dp = opendir(path);
    if(NULL == dp) {
        fprintf(stderr, "no such directory: '%s'", path);
        return 0;
    }

    *ls = NULL;
    ep = readdir(dp);
    while(NULL != ep){
        count++;
        ep = readdir(dp);
    }

    rewinddir(dp);
    *ls = calloc(count, sizeof(char *));

    count = 0;
    ep = readdir(dp);
    while(NULL != ep){
		if ( !strcmp(ep->d_name, ".") || !strcmp(ep->d_name, "..") ) {
			//We skip . and ..
		}else{
			(*ls)[count++] = strdup(ep->d_name);
		}
        ep = readdir(dp);
    }

    closedir(dp);
    return count;
}

int main(int argc, char **argv) {
    char **files;
    char cwd[1024];
	char *scanDirectory;
    size_t count;
    int i;
    
    if(argc > 1){
		//We have a directory to scan
		scanDirectory = argv[1];
		
	}else{
		scanDirectory = getcwd(cwd, sizeof(cwd));
	}
	
    count = file_list(scanDirectory, &files);
    for (i = 0; i < count; i++) {
		//Files is array containing the files, DUH!!
        printf("%s\n", files[i]);
    }
}
