#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

#define FB_DIR_ERROR -2
#define FB_DELETE -1
#define FB_NO_CHANGES 0

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "dirent.h"
#include "string.h"

#include "utils.h"

int initFileBuffers(char **fileBuffers, char **listenFileNames, char *path);
int checkEqualFileBuffers(char **baseBuffers, int nBuffers, char *path);
int isFileSuitable(char *fullPath);
int checkFileBuffersSize(int baseNBuffers, DIR *dr);
void freeFileBuffers(char **fileBuffers, int nBuffers);


#endif
