#ifndef GENERATE_FILE
#define GENERATE_FILE

#include "utils.h"

void generateCppFile(char *headerFile, char *sourcePath, char *headerFileName);

void addHeaderInclude(FILE *file, char *headerName, int headerNameLength);

#endif
