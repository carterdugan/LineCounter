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

    uint8_t verbose_files   : 1; /* print the files visited */
    uint8_t verbose_dir     : 1; /* print the directories visited */
    uint8_t verbose_errors  : 1; /* print any encountered errors */
    uint8_t branch          : 1; /* branch into subdirectories */
    uint8_t subtotals       : 1; /* print subtotals for each extension */
    uint8_t whitespace      : 1; /* exclude white space from the count */

    /* extensions specified at the command line */
    char extensions[MAX_EXTENSIONS][EXTENSION_MAX_LENGTH];

    /* Total number of extensions */
    int extension_count;

};

/*Initialize the FlagContainer and check for command line options*/
void setFlags(int argc, char** argv, struct FlagContainer* f);

#endif