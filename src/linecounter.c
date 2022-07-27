#include "linecounter.h"

/* flags.h */
extern void setFlags(int argc, char** argv, struct FlagContainer* f);

/* count.h */
extern bool isDir(char* path);
extern int countDirectory(char* path, struct FlagContainer f, int* extension_subtotals);
extern int countFile(char* path, struct FlagContainer f, int* extension_subtotals);

int main(int argc, char** argv) {

    struct FlagContainer fcontainer;
    int arg_counter;
    char path[MAX_PATH_LENGTH];
    int extension_subtotals[MAX_EXTENSIONS];
    int line_count;

    int i;

    if(argc < 2) {
    
        printf("Usage: ./linecounter [extensions] <options> [path]\n");
        printf("Use --help for more details\n");
        return -1;
    
    }

    if(!strcmp("--help", argv[1])) {

        printf("Usage: ./linecounter [extensions] <options> [path]\n");
        printf("    -f    %s", "Verbose output that prints the path of each file visited\n");
        printf("    -d    %s", "Verbose output that prints the path of each directory visited\n");
        printf("    -e    %s", "Verbose output that prints any errors encountered\n");
        printf("    -w    %s", "Exlude whitespace from the counted lines of code\n");
        printf("    -b    %s", "Branch out into subdirectories\n");
        printf("    -s    %s", "Print out the subtotals of the each extension\n");

        return 0;

    }

    setFlags(argc, argv, &fcontainer);

    for(i = 1; i < argc; i++) {
        
        if(argv[i][0] == '-') {

            continue;
    
        }

        if(fcontainer.extension_count < MAX_EXTENSIONS) {

            strcpy(fcontainer.extensions[fcontainer.extension_count], argv[i]);
            fcontainer.extension_count++;
            
        }
    
    }

    fcontainer.extension_count--;

    strcpy(path, argv[argc - 1]);

    if(fcontainer.subtotals) {

        for(i = 0; i < fcontainer.extension_count; i++) {
        
            extension_subtotals[i] = 0;
        
        }

    }

    if(fcontainer.extension_count == 0) {
    
        printf("Must have 1 or more extensions\n");
        return -1;
    
    }

    line_count = 0;

    if(isDir(path)) {
    
        line_count += countDirectory(path, fcontainer, extension_subtotals);
    
    } else {        
    
        line_count += countFile(path, fcontainer, extension_subtotals);
    
    }

    
    if(fcontainer.subtotals) {
        for(i = 0; i < fcontainer.extension_count; i++) {
    
            int st = extension_subtotals[i];

            printf("Extension .%s: %d (%.2f%%)\n",
                fcontainer.extensions[i],
                st,
                line_count == 0 ? 0 : (float)st / line_count * 100);
    
        }
    
    }

    printf("Total lines of code in '%s': %d\n", path, line_count);

    return 0;
}