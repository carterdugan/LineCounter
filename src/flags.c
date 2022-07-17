#include "flags.h"

void setFlags(int argc, char** argv, struct FlagContainer* f) {

    // unistd globals
    extern char* optarg;
    extern int optind, optopt;

    char c;

    f->verbose_files = false;
    f->verbose_dir = false;
    f->verbose_errors = false;
    f->branch = false;
    f->subtotals = false;

    f->extension_count = 0;

    while ((c = getopt(argc, argv, ":fdebs")) != -1) {

        switch(c) {

            char* arg;

            case 'f':
                f->verbose_files = true;
                break;

            case 'd':
                f->verbose_dir = true;
                break;

            case 'e':
                f->verbose_errors = true;

            case 'b':
                f->branch = true;
                break;

            case 's':
                f->subtotals = true;
                break;


            case '?':
                printf("Invalid option: %c\n", optopt);
                break;
            default:
                break;
        }
    }

}