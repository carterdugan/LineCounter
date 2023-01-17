#include "linecounter.h"

PATH_TYPE pathType(char path[PATH_LENGTH + 1])
{

    /* Use of 'Kernel32.dll' and I believe 'fileapi.h' */
    #if defined(_WIN32) || defined(_WIN64)

        DWORD attribute = GetFileAttributes(path);

        if(attribute == INVALID_FILE_ATTRIBUTES)
        {
            return ERROR_PATH;
        }

        if(attribute & FILE_ATTRIBUTE_DIRECTORY)
        {
            return DIRECTORY_PATH;
        }

        return FILE_PATH;

    #elif defined(__unix__)

        struct stat sb;

        if(stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
        {
            return DIRECTORY_PATH;
        }
        
        if(stat(path, &sb) == 0 && S_ISREG(sb.st_mode))
        {
            return FILE_PATH;
        }

        return OTHER_PATH;

    #endif

}

int main(int argc, char * argv[])
{

    char path[PATH_LENGTH + 1] = {'\0'};

    if(argc < 3)
    {
        printf("Usage: ./linecounter <OPTIONS> [EXTENSIONS] [PATH]\n");
        return 1;
    }

    if(strlen(argv[argc - 1]) > PATH_LENGTH)
    {
        printf("Path cannot exceed 1024 characters.\n");
        return 1;
    }

    memcpy(path, argv[argc - 1], strlen(argv[argc - 1]));

    return 0;

}