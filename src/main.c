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
        int i = checkEqualFileBuffers(fileBuffers, nBuffers, path);
        
        switch (i) {

            case (FB_DIR_ERROR): {
                printf("Incorrect path : %s\n", path);
                break;
            }

            case (FB_DELETE): {
                printf("Deleted file !\n");
                break;
            }

            case (FB_NO_CHANGES): {
                break;
            }

            default: {
                freeFileBuffers(fileBuffers, nBuffers);
                fileBuffers = malloc(32 * sizeof(char*));
                for (int i = 0; i < 32; i++) {
                    fileBuffers[i] = NULL;
                }
                nBuffers = initFileBuffers(fileBuffers, path);
                printf("nBuffers, %d\n", nBuffers);
                printf("Modification ! %d\n", i); 
                printf("%s", fileBuffers[i-1]);
            }

        }
    } 
    
    return 0;
}
