#include "linecounter.h"

PATH_TYPE pathType(char path[PATH_LENGTH])
{

    PATH_TYPE ret_value = OTHER_PATH;

    #if defined(_WIN32) || defined(_WIN64)

        DWORD attribute = GetFileAttributes(path);

        if(attribute != INVALID_FILE_ATTRIBUTES &&
          (attribute & FILE_ATTRIBUTE_DIRECTORY))
        {
            ret_value = DIRECTORY_PATH;
        }
        else if(attribute != INVALID_FILE_ATTRIBUTES &&
               (attribute & FILE_ATTRIBUTE_NORMAL))
        {
            ret_value = FILE_PATH;
        }

    #elif defined(__unix__)

        struct stat sb;

        if(stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
        {
            ret_value = DIRECTORY_PATH;
        }
        else if(stat(path, &sb) == 0 && S_ISREG(sb.st_mode))
        {
            ret_value = FILE_PATH;
        }

    #endif

    return ret_value;
}

int main(int argc, char * argv[])
{

    char path[PATH_LENGTH + 1] = {'\0'};

    if(argc < 2)
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