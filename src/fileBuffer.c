#include "fileBuffer.h"

int initFileBuffers(char **fileBuffers, char *path) {
    struct dirent *de;
    DIR *dr = opendir(path);
    FILE *file;

    if (dr == NULL) {
        return -1;
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
    return i;
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

int checkFileBuffersSize(int baseNBuffers, DIR *dr) {
    struct dirent *de;

    int i = 0;
    while ((de = readdir(dr)) != NULL) {
        i++;
    }  

    free(de);
    return i >= baseNBuffers;
}

void freeFileBuffers(char **fileBuffers, int nBuffers) {
    for (int i = 0; i < nBuffers; i++) {
        free(fileBuffers[i]);
    }
    free(fileBuffers);

}

