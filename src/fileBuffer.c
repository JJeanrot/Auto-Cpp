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
        for (int j = 0; j < 256; j++) {
            fullPath[j] = '\0';
        }   


        strcat(fullPath, path);
        strcat(fullPath, de->d_name);

        if (isFileSuitable(fullPath)) {
            continue;
        }

        printf("%s\n", de->d_name);

        file = fopen(fullPath, "r");
        if (file == NULL) {
            free(fullPath);
            continue;
        }

        
        fileBuffers[i] = malloc(BUFFER_SIZE );
        copy(file, fileBuffers[i], 0);
       
        i++;
        free(fullPath);
    }

    fclose(file);
    closedir(dr);
    return i;
}

int checkEqualFileBuffers(char **baseBuffers, int nBuffers, char *path) {
    struct dirent *de;
    DIR *dr = opendir(path);
    FILE *file;

    if (dr == NULL) {
        return -1;
    } 

    int equalSize = checkFileBuffersSize(nBuffers, dr);
    if (!equalSize) {
        return FB_DELETE;
    }   
    rewinddir(dr);


    int i = 0;
    char* fullPath;
    char* checkBuffer;
    while ((de = readdir(dr)) != NULL) {
        fullPath = malloc(256);
        for (int i = 0; i < 256; i++) {
            fullPath[i] = '\0';
        }   

        strcat(fullPath, path);
        strcat(fullPath, de->d_name);

        if (isFileSuitable(fullPath)) {
            continue;
        }

        file = fopen(fullPath, "r");
        
        if (file == NULL) {
            free(fullPath);
            continue;
        }

        checkBuffer = malloc(BUFFER_SIZE );
        for (int i = 0; i < BUFFER_SIZE; i++) {
            checkBuffer[i] = '\0'; 
        }
        copy(file, checkBuffer, 0);
        if (compareBuffers(baseBuffers[i], checkBuffer) == 1) {
            fclose(file); 
            return i+1;
        }

        i++;
        free(fullPath);
    }

    fclose(file);
    closedir(dr);
    return 0;
}

int isFileSuitable(char *fullPath) {
    if (!isRegularFile(fullPath)) {
        free(fullPath);
        return 1;
    }

    return 0;
}

int checkFileBuffersSize(int baseNBuffers, DIR *dr) {
    struct dirent *de;

    int i = 0;
    while ((de = readdir(dr)) != NULL) {
        if (!isRegularFile(de->d_name)) {
            continue;
        }
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

