#include "utils.h"

int copy(FILE *in, char *out, int index) {
    int o = 0;
    while (feof(in) == 0) {
        int c = getc(in);
        if (c == -1) break;
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

