#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "dirent.h"
#include "string.h"

#define BUFFER_SIZE 8192

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

int compareBuffers(char* ba, char* bb) {
    int i = 0;
    while (i < BUFFER_SIZE ) {
        if (ba[i] != bb[i]) {
            return 1;
        }
        i++;
    } 

    return 0;
}

int initFileBuffers(char **fileBuffers, char *path) {
    struct dirent *de;
    DIR *dr = opendir(path);
    FILE *file;

    if (dr == NULL) {
        return 1;
    } 


    int i = 0;
    char* fullPath;
    while ((de = readdir(dr)) != NULL) {
        fullPath = malloc(256);

        strcat(fullPath, path);
        strcat(fullPath, de->d_name);
        printf("%s\n", de->d_name);
        printf("%s\n", fullPath);

        file = fopen(fullPath, "r");
        if (file == NULL) {
            continue;
        }
        
        fileBuffers[i] = malloc(BUFFER_SIZE );
        copy(file, fileBuffers[i], 0);
       
        i++;
    }

    closedir(dr);
    return 0;
}

int checkEqualFileBuffers(char **baseBuffers, char *path) {
    struct dirent *de;
    DIR *dr = opendir(path);
    FILE *file;

    if (dr == NULL) {
        return -1;
    } 

    int i = 0;
    char* fullPath;
    char* checkBuffer;
    while ((de = readdir(dr)) != NULL) {
        fullPath = malloc(256);

        strcat(fullPath, path);
        strcat(fullPath, de->d_name);

        file = fopen(fullPath, "r");
        
        if (file == NULL) {
            continue;
        }

        checkBuffer = malloc(BUFFER_SIZE );
        copy(file, checkBuffer, 0);
        if (compareBuffers(baseBuffers[i], checkBuffer) == 1) {
            
            return i+1;
        }

        i++;
    }

    closedir(dr);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage : (whatever) path_to_listen_to\n");
        return 1;
    }

    char *path = argv[1];

    // buffers the files
    char **fileBuffers = malloc(32 * sizeof(char*));
    
    if (initFileBuffers(fileBuffers, path) == 1) {
        printf("Incorrect path");
        return 1;
    }

    while (true) {
        sleep(1);
        int i = checkEqualFileBuffers(fileBuffers, path);
        if (i <= 0) {
            continue;
        }
        printf("Modification ! %d\n", i);         
    }       

    return 0;
}
