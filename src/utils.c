#include "utils.h"

int copyFromFile(FILE *in, char *out, int index) {
    int o = 0;
    while (feof(in) == 0) {
        int c = getc(in);
        if (c == -1) break;
        out[index + o] = c;
        o++;
    }
    return o;
}

int copyFromBuffer(char *in, char *out, int index) {
    int o = 0;
    while (in[o] != '\0') {
        char c = in[o];
        out[index + o] = c;
        o++;
    }
    return o;
}

int compareBuffers(char* ba, char* bb) {
    int i = 0;
    while (i < BUFFER_SIZE ) {
        if (ba[i] != bb[i]) {
            return 1;
        }
        i++;
    } 

    return 0;
}

int isRegularFile(char *path) {
    DIR* directory = opendir(path);

    if (directory != NULL)
    {
        closedir(directory);
        return 0;
    }

    if (errno == ENOTDIR)
    {
        return 1;
    }

    return -1;
}

void freeBuffers(char **buffers, int nBuffers) {
    for (int i = 0; i < nBuffers; i++) {
        free(buffers[i]);
    }
    free(buffers);
}
