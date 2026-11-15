#include "stdio.h"
#include "string.h"

#include "fileBuffer.h"


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage : (whatever) path_to_listen_to\n");
        return 1;
    }

    char *path = argv[1];

    // buffers the files
    char **fileBuffers = malloc(32 * sizeof(char*));
    int nBuffers = initFileBuffers(fileBuffers, path); 
    if (nBuffers == -1) {
        printf("Incorrect path");
        return 1;
    }

    while (true) {
        sleep(1);
        int i = checkEqualFileBuffers(fileBuffers, path);
        if (i <= 0) {
            continue;
        }

        // Super slow
        initFileBuffers(fileBuffers, path);
        printf("Modification ! %d\n", i);         
        printf(fileBuffers[i-1]);
        printf("\n");
    }       

    return 0;
}
