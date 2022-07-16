#ifndef FLAGS_H
#define FLAGS_H

#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define EXTENSION_MAX_LENGTH 8
#define MAX_EXTENSIONS 64

struct FlagContainer{

    char verbose_files   : 1;
    char verbose_dir     : 1;
    char branch          : 1;
    char subtotals       : 1;

    char extensions[MAX_EXTENSIONS][EXTENSION_MAX_LENGTH];

    int extension_count;

};

/*Initialize the FlagContainer and check for command line options*/
void setFlags(int argc, char** argv, struct FlagContainer* f);

#endif