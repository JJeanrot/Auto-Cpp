#include "generateFile.h"

void generateCppFile(char *headerBuffer, char *sourcePath) {
    FILE *file = fopen(sourcePath, "w+");
    if (file == NULL) {perror("file");}
    fwrite("test", 1, 4, file);

    fclose(file);
}
