#ifndef __ERROR_C__
#define __ERROR_C__

#include "error_c.h"

void error_print(const Error *err)
{
    if (err == NULL) return;
    const char *level_str;
    switch (err->level_c)
    {
    case ERROR_LEVEL_INFO:
        level_str = "Info";
        break;
    case ERROR_LEVEL_WARNING:
        level_str = "Warning";
        break;
    case ERROR_LEVEL_ERROR:
        level_str = "Error";
        break;
    default:
        level_str = "Unknown";
        break;
    }
    fprintf(stderr, "[%s] %s (%s:%d)\n", level_str, err->message, err->file, err->line);
}

void error_log(const Error *err)
{
    if (err == NULL) return;
    FILE *file = fopen(ERROR_LOG_FILE, "a");
    if (file != NULL)
    {
        const char *level_str;
        switch (err->level_c)
        {
        case ERROR_LEVEL_INFO:
            level_str = "Info";
            break;
        case ERROR_LEVEL_WARNING:
            level_str = "Warning";
            break;
        case ERROR_LEVEL_ERROR:
            level_str = "Error";
            break;
        default:
            level_str = "Unknown";
            break;
        }
        fprintf(file, "[%s] %s (%s:%d)\n", level_str, err->message, err->file, err->line);
        fclose(file);
    }
}


#endif