#ifndef GENERATE_FILE
#define GENERATE_FILE

#include "utils.h"

/** Main function of the file, the only one used in main.c.
 *  Creates a new file and put information in it
 *  @param headerFile Buffer containing the content of the header file
 *  @param sourcePath Path to create the new file
 *  @param headerFileName Name of the header file
 *  @see addHeaderInclude
 */
void generateCppFile(char *headerFile, char *sourcePath, char *headerFileName);
 
/** Adds the main include to the cpp file.
 *  Adds a line like so "#include '<header name>.h'"
 *  @param file Created file
 *  @param headerName Name of the header file
 *  @param headerNameLength length of the header file name
 *  @see generateCppFile
 */
void addHeaderInclude(FILE *file, char *headerName, int headerNameLength);

#endif
