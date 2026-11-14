#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "dirent.h"

int initFileBuffers(char ***fileBuffers, char *path) {
    struct dirent *de;
    DIR *dr = opendir(path);

    if (dr == NULL) {
        return 1;
    } 

    while ((de = readdir(dr)) != NULL) {
        printf("%s\n", de->d_name);
    }

    closedir(dr);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage : (whatever) path_to_listen_to\n");
        return 1;
    }

    // buffers the files
    char ***fileBuffers;
    if (initFileBuffers(fileBuffers, argv[1]) == 1) {
        printf("Incorrect path");
        return 1;
    }

    return 0;
}
