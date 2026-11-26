#ifndef UTILS_H
#define UTILS

#include "dirent.h"
#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#define BUFFER_SIZE 4096

/** Copy char * buffer from file.
 *  Does a deep copy of the file and stores it in the buffer starting at the specified index.
 *  @param in source file
 *  @param out char * buffer output
 *  @param index the index of out to start in the copy
 *  @return number of copied bytes
 *  @see copyFromBuffer
 */
int copyFromFile(FILE *in, char *out, int index);

/** Copy char * buffer from another char * buffer.
 *  Does a deep copy of the in buffer and stores it in the buffer starting at the specified index.
 *  @param in source buffer
 *  @param out char * buffer output
 *  @param index the index of out to start in the copy
 *  @return number of copied bytes
 *  @see copyFromFile
 */
int copyFromBuffer(char *in, char *out, int index);

/** Compares the passed buffers.
 *  Goes through each value of the first buffer and checks its value is the same as the other buffer.
 *  @param ba buffer A
 *  @param bb buffer B
 *  @return 0 if they are the same, 1 otherwise.
 */
int compareBuffers(char *ba, char *bb);

/** Checks if a file is an actual file.
 *  Tries to open the file as a directory. If it fails, that means it is a regular file. Otherwise, it is not.
 *  @param path path to open the file to check
 *  @return 0 if it is a regular file, 1 if there was an error with opendir(), -1 otherwise.
 */
int isRegularFile(char *path);

/** Frees a char ** type.
 *  Goes through each element of the buffer and frees it. Then, frees the char ** element.
 *  @param buffers char ** to clear
 *  @param nBuffers nomber of pointers the variable buffers stores
 */
void freeBuffers(char **buffers, int nBuffers);

/** Truncate the extension of a filename.
 *  Mallocs a new char * and copies the name parameter into it. Then, truncates the extension and returns it.
 *
 *  Example : "file.h" --> "file"
 *
 *  @param name name to truncate
 *  @return the newly allocated truncated buffer
 */
char *truncateFileNameExtension(char* name);

/** Extends a filename with .cpp.
 *  Takes the name parameter "as-is", then extends it with ".cpp".
 *
 *  Example : "file --> "file.cpp"
 *
 *  @param name name to extend
 *  @see truncateFileName
 */
void extendWithCpp(char *name);

/** Get the size of the char pointer (string).
 *  Goes through each element of the pointer, and stops whenever '\0' is found.
 *  @param ptr char pointer to get the length from
 *  @return length of the pointer
 */
int getCharptrLength(char *ptr);

#endif
