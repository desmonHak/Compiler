#ifndef __DEBUG_C__
#define __DEBUG_C__
#include "debug_c.h"

void __attribute__((constructor)) __constructor_debug_c__(){
    //debug_set_log_file("debug_log.txt");
    //open_file(&Log_debug_file, NAME_DEFAULT_LOG_DEBUG, READ_WRITE );
    DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:white}[#{FG:red}DEBUG INIT#{FG:white}]");

    /*if (Log_debug_file.archivo == OPEN_ERROR) {
        printf("Error al abrir el archivo " NAME_DEFAULT_LOG_DEBUG "\n");
        return 1;
    }*/

}
void __attribute__((destructor)) __destructor_debug_c__(){
    /*if (logFile != NULL)
    {
        fclose(logFile);
        logFile = NULL;
    }*/
    /*close_file(&Log_debug_file);*/
}

const char* get_level_debug(DebugLevel level) {
    switch(level){

    case DEBUG_LEVEL_INFO:
        return ErrorLevelStrings[0];
        break;
    case DEBUG_LEVEL_WARNING:
        return ErrorLevelStrings[1];
        break;
    case DEBUG_LEVEL_ERROR:
        return ErrorLevelStrings[2];
        break;
    default:
        return "UNKNOW";
        break;
    };
}  

/*void debug_set_log_file(const char *filename)
{
    if (logFile != NULL)
    {
        fclose(logFile);
        logFile = NULL;
    }

    logFile = fopen(filename, "w");
}*/

void debug_set_level(DebugLevel level)
{
    currentLevel = level;
}

void debug_print(DebugLevel level, const char *fmt, ...)
{
    if (fmt == (const char *)NULL) return;
    if (level < currentLevel)
    {
        return;
    }

    va_list args;
    va_start(args, fmt);

    va_list args_copy;
    va_copy(args_copy, args);
    size_t size = (vsnprintf(NULL, 0, fmt, args_copy) + 1) * sizeof(char);
    va_end(args_copy);
    va_copy(args_copy, args);

    vprintf_color( fmt, args_copy);
    va_end(args_copy);
    putchar( '\n');

    /*if (logFile != NULL)
    {
        vfprintf(logFile, fmt, args);
        fprintf(logFile, "\n");
    }*/

    /*unsigned char *formatted_buffer = (unsigned char *)malloc(size);
    vsprintf(formatted_buffer, fmt, args);

    write_file(&Log_debug_file, formatted_buffer);
    if(Log_debug_file.size == WRITE_ERROR){
        printf("Error al escribir el archivo\n");
    }*/

    va_end(args);

    if (level == DEBUG_LEVEL_ERROR)
    {
        va_start(args, fmt);
        char *message = malloc(size * sizeof(char));
        vsnprintf(message, size, fmt, args);
        va_end(args);
        
        ERROR_C(ERROR_LEVEL_ERROR, message);
    }
}
#endif