#include "fileBuffer.h"

int initFileBuffers(char **fileBuffers, char **listenFileNames, char *path) {
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

        listenFileNames[i] = malloc(256);
        for (int j = 0; j < 256; j++) {
            listenFileNames[i][j] = '\0'; 
        }
        copyFromBuffer(de->d_name, listenFileNames[i], 0);

        file = fopen(fullPath, "r");
        if (file == NULL) {
            free(fullPath);
            continue;
        }

        fileBuffers[i] = malloc(BUFFER_SIZE );
        copyFromFile(file, fileBuffers[i], 0);
       
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
        copyFromFile(file, checkBuffer, 0);
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
    // Is it a regular file and not a directory ?
    if (!isRegularFile(fullPath)) {
        free(fullPath);
        return 1;
    }

    // Is it a .h file ?
    int i = 0;
    while (fullPath[i] != '\0' && fullPath[i] != '.') {
        i++; 
    }
    if (fullPath[i+1] != 'h' || fullPath[i+2] != '\0') {
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

