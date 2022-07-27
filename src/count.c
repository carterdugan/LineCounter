#include "count.h"

bool isDir(char* path) {
    
    DIR* d;
    bool dir;

    dir = (d = opendir(path)) != NULL;

    closedir(d);

    return dir;

}

bool hasExtension(char* path, char* extension) {

    int path_size;
    int extension_size;
    int i; /* index for extension */
    int j; /* index for path */

    path_size = strlen(path);
    extension_size = strlen(extension);

    if(extension_size > path_size) {
        
        return false;

    }

    j = path_size - 1;

    for(i = extension_size - 1; i >= 0; i--) {

        if(extension[i] != path[j]) {

            return false;

        }

        j--;

    }

    return true;

}

int countDirectory(char* path, struct FlagContainer f, int* extension_subtotals) {

    DIR* d;
    struct dirent* dir;
    char* subdir_name;
    char new_path[MAX_PATH_LENGTH];
    int line_count;
    int path_size;
    int subdir_size;

    line_count = 0;

    strcpy(new_path, path);

    d = opendir(path);

    if(d == NULL) {

        if(f.verbose_dir & f.verbose_errors) {

            printf("Cannot open directory '%s'\n", path);

        }

        return 0;

    }

    if(d) {

        while((dir = readdir(d)) != NULL) {

            subdir_name = dir->d_name;

            if(subdir_name[0] != '.') {

                path_size = strlen(path);
                subdir_size = strlen(subdir_name) + 1;

                if(path_size + subdir_size >= MAX_PATH_LENGTH) {
                    printf("Cannot check '%s' due to path size.\n", subdir_name);
                    return 0;
                }

                /*
                This spits out a warning due to the buffer size,
                ignore it (for now).
                */
                sprintf(new_path, "%s/%s", new_path, subdir_name);

                if(isDir(new_path)) {

                    if(f.branch) {

                        line_count += countDirectory(new_path, f, extension_subtotals);

                    }

                } else {

                        line_count += countFile(new_path, f, extension_subtotals);

                }
                
                new_path[path_size] = '\0';
            }

        }

        closedir(d);

    }

    if(f.verbose_dir) {

        printf("Directory '%s': %d\n", path, line_count);

    }

    return line_count;

}

int countFile(char* path, struct FlagContainer f, int* extension_subtotals) {

    FILE* fp;
    bool valid_extension;
    int line_count;
    char line[MAX_LINE_LENGTH];

    int i;

    line_count = 0;
    valid_extension = false;

    for(i = 0; i < f.extension_count; i++) {

        if(hasExtension(path, f.extensions[i])) {

            valid_extension = true;
            break;

        }

    }

    if(!valid_extension) {

        return 0;

    }

    if((fp = fopen(path, "r")) == NULL) {

        if(f.verbose_files && f.verbose_errors) {

            printf("Cannot open file '%s'\n", path);

        }

        return 0;

    }

    while(fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
    
        if(f.whitespace) {

            if(!strcmp("\n", line)) {

                continue;
            
            }

        }

        line_count++;
    
    }

    if(f.verbose_files) {   
    
        printf("File '%s': %d\n", path, line_count);
    
    }

    fclose(fp);

    if(f.subtotals) {
    
        extension_subtotals[i] += line_count;
    
    }

    return line_count;

}