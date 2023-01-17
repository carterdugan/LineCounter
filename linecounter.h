#ifndef LINECOUNTER_H
#define LINECOUNTER_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#if defined(_WIN32) || defined(_WIN64)
#include <fileapi.h>
#ifndef PATH_SEPARATOR
#define PATH_SEPARATOR "\\"
#endif
#elif defined(__unix__)
#include <sys/types.h>
#include <sys/stat.h>
#ifndef PATH_SEPARATOR
#define PATH_SEPARATOR "/"
#endif
#endif

#ifndef PATH_LENGTH
#define PATH_LENGTH 1024
#endif

#ifndef VERBOSE_FILES
#define VERBOSE_FILES   1 << 0
#endif

#ifndef VERBOSE_DIR
#define VERBOSE_DIR     1 << 1
#endif

#ifndef VERBOSE_ERRORS
#define VERBOSE_ERRORS  1 << 2
#endif

#ifndef BRANCH
#define BRANCH          1 << 3
#endif

#ifndef SUBTOTALS
#define SUBTOTALS       1 << 4
#endif

#ifndef WHITESPACE
#define WHITESPACE      1 << 5
#endif

#ifndef SET_FLAG
#define SET_FLAG(n, flag) n |= flag
#endif

#ifndef CLEAR_FLAG
#define CLEAR_FLAG(n, flag) n &= ~flag
#endif

#ifndef RESET_FLAGS
#define RESET_FLAGS(n) n = 0x0
#endif

#ifndef CHECK_FLAG
#define CHECK_FLAG(n, flag) n & flag
#endif

typedef enum
{

    DIRECTORY_PATH,
    FILE_PATH,

    OTHER_PATH

} PATH_TYPE;

PATH_TYPE pathType(char path[PATH_LENGTH + 1]);

#endif /* !LINECOUNTER_H */