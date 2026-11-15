#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "dirent.h"
#include "string.h"

#include "utils.h"

int initFileBuffers(char **fileBuffers, char *path);
int checkEqualFileBuffers(char **baseBuffers, char *path);

#endif
