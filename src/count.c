#include "count.h"

bool isDir(char* path) {
    
    DIR* d;
    bool dir;

    dir = (d = opendir(path)) != NULL;

    closedir(d);

    return dir;

}

bool hasExtension(char* path, char* extension) {

    int last_dot_index;
    int i;
    int index;
    int size;
    char* p;
    char f_ext[EXTENSION_MAX_LENGTH];

    size = strlen(path);

    last_dot_index = 0;

    for(i = 0; i < size; i++) {

        if(path[i] == '.') {

            last_dot_index = i;
        
        }

    }

    if(last_dot_index == 0) {
        
        return false;
    
    }

    index = 0;

    for(i = ++last_dot_index; i < size; i++) {

        f_ext[index] = path[i];
        index++;
        
        if(index >= EXTENSION_MAX_LENGTH) {
        
            return 0;

        }

    }

    f_ext[index] = '\0';

    return !strcmp(f_ext, extension);

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

        if(f.verbose_dir) {

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

        if(f.verbose_files) {

            printf("Cannot open file '%s'\n", path);

        }

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