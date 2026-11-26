#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

#define FB_DIR_ERROR -2
#define FB_DELETE -1
#define FB_NO_CHANGES 0

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "dirent.h"
#include "string.h"

#include "utils.h"

/** Inits the file buffers with the files found in the listened path.
 *  Goes through each of the files in the listened path. If the file is an actual file, and if it is a ".h" file, then it is counted. Its content is stored in fileBuffer, and its name is stored in listenFileNames. 
 *  Recursivity is not supported. 
 *  The allocations of the file buffers and the file names are done in the function, but the parameters must have memory already allocated before running the function.
 *  @param fileBuffers file buffers to fill
 *  @param listenFileNames file names to fill
 *  @param path listen path to get the files to fill with
 *  @return number of allocated files (also the number of names, it's the same)
 */
int initFileBuffers(char **fileBuffers, char **listenFileNames, char *path);

/** Checks if a modification happened in the files.
 *  First checks if the actual number of files in the directory is the smaller than the file buffers. If it is, its means there was a file deletion, and it gets returned.
 *  After, goes through each of the files in the listened path. If the file is an actual file, and if it is a ".h" file, then it is counted. Then, compares that file with the corresponding buffer in the fileBuffers parameter. If there is a difference it gets returned.
 *  @param baseBuffers the buffers calculated in @see initFileBuffers
 *  @param nBuffers the nomber of buffers that were computed
 *  @param path path to listen to
 *  @return 
 *  FB_NO_CHANGES if no changes were spotted, 
 *  FB_DELETE if a file deletion was detected, 
 *  FB_DIR_ERROR if an error occured with opendir()
 *  else, the index + 1 of the modified (or added) file
 */
int checkEqualFileBuffers(char **baseBuffers, int nBuffers, char *path);

/** Checks if the file is suitable for listen.
 *  Checks if it is not a directory
 *  Checks if it is strictly a .h file (no .hpp)
 *  @param fullPath the path of the file to check
 *  @return 0 if the file is suitable, 1 otherwise
 */
int isFileSuitable(char *fullPath);

/** Checks if the actual number of files in the directory is the smaller that was computed before.
 *  It doesn't matter if the actual number of files is greater, as the way to detect if a file was modified or if a file was added is the exact same.
 *  @param baseNBuffers the number of buffers that was computed
 *  @param dr the listen directory
 *  @return 0 if the actual number of files is equal or greatr than the one computed, 1 otherwise
 *  @see checkEqualFileBuffers
 */
int checkFileBuffersSize(int baseNBuffers, DIR *dr);


#endif
