#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "dirent.h"
#include "string.h"

int copy(FILE *in, char *out, int index)
{
    int o = 0;
    while (feof(in) == 0) {
        int c = getc(in);
        if (c == -1) break;
        out[index + o] = c;
        o++;
    }
    return o;
}

int initFileBuffers(char **fileBuffers, char *path) {
    struct dirent *de;
    DIR *dr = opendir(path);
    FILE *file;

    if (dr == NULL) {
        return 1;
    } 

    int i = 0;
    char* fullPath = malloc(256);
    while ((de = readdir(dr)) != NULL) {
        strcat(fullPath, path);
        strcat(fullPath, de->d_name);
        printf("%s\n", de->d_name);

        file = fopen(fullPath, "r");
        if (file == NULL) {
            continue;
        }
        
        fileBuffers[i] = malloc(4096);
        copy(file, fileBuffers[i], 0);
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
    char **fileBuffers;
    if (initFileBuffers(fileBuffers, argv[1]) == 1) {
        printf("Incorrect path");
        return 1;
    }

    while (true) {
        
    }       

    return 0;
}
