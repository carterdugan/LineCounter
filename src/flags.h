#ifndef FLAGS_H
#define FLAGS_H

#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#define EXTENSION_MAX_LENGTH 8
#define MAX_EXTENSIONS 64

struct FlagContainer{

    uint8_t verbose_files   : 1;
    uint8_t verbose_dir     : 1;
    uint8_t verbose_errors  : 1;
    uint8_t branch          : 1;
    uint8_t subtotals       : 1;

    char extensions[MAX_EXTENSIONS][EXTENSION_MAX_LENGTH];

    int extension_count;

};

/*Initialize the FlagContainer and check for command line options*/
void setFlags(int argc, char** argv, struct FlagContainer* f);

#endif