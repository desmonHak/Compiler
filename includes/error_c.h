#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>
#include <stdlib.h>

#define ERROR_LOG_FILE "error_log.txt"

typedef enum {
    ERROR_LEVEL_INFO,
    ERROR_LEVEL_WARNING,
    ERROR_LEVEL_ERROR
} ErrorLevel;

typedef struct {
    char *message;
    const char *file;
    unsigned int line;
    ErrorLevel level_c;
} Error;

void error_print(const Error *err);
void error_log(const Error *err);

#define ERROR_C(level, msg)                                                                 \
    do                                                                                    \
    {                                                                                     \
        Error err = {.message = msg, .file = __FILE__, .line = __LINE__, .level_c = level}; \
        error_print(&err);                                                                \
        error_log(&err);                                                                  \
        if (level == ERROR_LEVEL_ERROR)                                                   \
        {                                                                                 \
            exit(EXIT_FAILURE);                                                           \
        }                                                                                 \
    } while (0)


#include "error_c.c"
#endif 