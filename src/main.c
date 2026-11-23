#include "stdio.h"
#include "string.h"

#include "fileBuffer.h"


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage : (whatever) listenPath modifyPath\n");
        return 1;
    }

    char *listenPath = argv[1];
    char *modifyPath = argv[2];

    // buffers the files
    char **fileBuffers = malloc(32 * sizeof(char*));
    char **listenFileNames = malloc(32 * sizeof(char*));
    int nBuffers = initFileBuffers(fileBuffers, listenFileNames, listenPath); 
    if (nBuffers == -1) {
        printf("Incorrect listenPath");
        return 1;
    }

    while (true) {
        sleep(1);
        int i = checkEqualFileBuffers(fileBuffers, nBuffers, listenPath);
        
        switch (i) {

            case (FB_DIR_ERROR): {
                printf("Incorrect listenPath : %s\n", listenPath);
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
                nBuffers = initFileBuffers(fileBuffers, listenFileNames, listenPath);
                printf("Modification ! %d\n", i); 
                printf("The modified file is : %s\n", listenFileNames[i-1]);
                printf("Trying to find the corresponding file ...\n");
                
            }

        }
    } 
    
    return 0;
}
