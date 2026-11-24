#include "stdio.h"
#include "string.h"

#include "fileBuffer.h"
#include "generateFile.h"
#include "utils.h"

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
                freeBuffers(fileBuffers, nBuffers);
                freeBuffers(listenFileNames, nBuffers);

                fileBuffers = malloc(32 * sizeof(char*));
                for (int i = 0; i < 32; i++) {
                    fileBuffers[i] = NULL;
                }
                listenFileNames = malloc(32 * sizeof(char*));
                nBuffers = initFileBuffers(fileBuffers, listenFileNames, listenPath);
                printf("\nModification !\n"); 
                printf("The modified file is : %s\n", listenFileNames[i-1]);
                char *cppName = truncateFileNameExtension(listenFileNames[i-1]);
                extendWithCpp(cppName); 
                printf("The corresponding file is : %s\n", cppName);        
                char *fullPath = malloc(256);
                fullPath[0] = '\0';
                strcat(fullPath, modifyPath);
                strcat(fullPath, cppName);

                if (fopen(fullPath, "r") == NULL) {
                    // File does not exist : generate
                    generateCppFile(fileBuffers[i-1], fullPath);
                    printf("Generated new file : %s\n", cppName);
                }
            
                free(fullPath);
                free(cppName);
            }
        }
    } 
    
    return 0;
}
