#ifndef UTILS_H
#define UTILS

#include "dirent.h"
#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#define BUFFER_SIZE 4096

int copyFromFile(FILE *in, char *out, int index);
int copyFromBuffer(char *in, char *out, int index);
int compareBuffers(char *ba, char *bb);
int isRegularFile(char *path);

void freeBuffers(char **buffers, int nBuffers);
char *truncateFileNameExtension(char* path);

#endif
