#include "generateFile.h"

void generateCppFile(char *headerBuffer, char *sourcePath, char *headerFileName) {
    FILE *file = fopen(sourcePath, "w+");
    char *headerName = headerFileName;
    int headerNameLength = getCharptrLength(headerFileName);

    if (file == NULL) {
        perror("file");
    }

    addHeaderInclude(file, headerName, headerNameLength);

    fclose(file);
}

void addHeaderInclude(FILE *file, char *headerName, int headerNameLength) {
    fwrite("#include \"", 1, 10, file);
    fwrite(headerName, 1, 3, file);
    fwrite("\"\n", 1, headerNameLength, file);
}
