#ifndef COUNT_H
#define COUNT_H

#include <dirent.h>
#include <stdlib.h>

#include "flags.h"

#define MAX_PATH_LENGTH 1024
#define MAX_LINE_LENGTH 256

/*Check if a path is a directory*/
bool isDir(char* path);

/*Check if a file ends with a specified extension*/
bool hasExtension(char* path, char* extension);

/*Count lines of code in a directory*/
int countDirectory(char* path, struct FlagContainer f, int* extension_subtotals);

/*Count lines of code in a file*/
int countFile(char* path, struct FlagContainer f, int* extension_subtotals);

#endif