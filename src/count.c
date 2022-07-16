#include "count.h"

bool isDir(char* path) {
    
    DIR* d;
    bool dir;

    dir = (d = opendir(path)) != NULL;

    closedir(d);

    return dir;

}

bool hasExtension(char* path, char* extension) {

    int last_dot_index = 0;
    int i;
    int j;
    int size;
    char* p;
    char f_ext[EXTENSION_MAX_LENGTH];

    size = strlen(path);

    for(i = 0; i < size; i++) {

        if(path[i] == '.') {

            last_dot_index = i;
        
        }

    }

    if(last_dot_index == 0) {
        
        return false;
    
    }

    i = 0;

    for(j = ++last_dot_index; j < size; j++) {

        f_ext[i] = path[j];
        i++;
        if(i >= EXTENSION_MAX_LENGTH) {return 0;}

    }

    f_ext[i] = '\0';

    return !strcmp(f_ext, extension);

}

int countDirectory(char* path, struct FlagContainer f, int* extension_subtotals) {

    DIR* d;
    struct dirent* dir;
    char* subdir_name;
    char new_path[MAX_PATH_LENGTH];
    int line_count;

    line_count = 0;

    strcpy(new_path, path);

    d = opendir(path);

    if(d == NULL) {

        if(f.verbose_dir) {

            printf("Cannot open directory '%s'\n", path);

        }

        return 0;

    }

    if(d) {

        while((dir = readdir(d)) != NULL) {

            subdir_name = dir->d_name;

            if(strcmp("..", subdir_name) && strcmp(".", subdir_name)) {

                strcat(new_path, "/");
                strcat(new_path, subdir_name);

                if(isDir(new_path)) {

                    if(f.branch) {

                        line_count += countDirectory(new_path, f, extension_subtotals);

                    }

                } else {

                        line_count += countFile(new_path, f, extension_subtotals);

                }
                
                strcpy(new_path, path);

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

        return 0;

    }

    while(fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
    
        if(strcmp("\n", line)) {

            line_count++;

        }
    
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