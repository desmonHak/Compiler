#ifndef _BASE_H_
#define _BASE_H_

// macros globales del compilador:
#ifdef _WIN32
#define NAME_COMPILER "compile.exe"
#else
#define NAME_COMPILER "compile.elf"
#endif
#define VERSION_COMPILER 0
#define SUB_VERSION_COMPILER 0
// ---

#if defined(__x86_64__) /* 64 bit detected */
static unsigned compiler_word_arch = 64;
#elif defined(__i386__) /* 32 bit x86 detected */
static unsigned compiler_word_arch = 32;
#endif

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <getopt.h>
#include <wchar.h>
#include <locale.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/stat.h>
#endif

#include "colors-C-C-plus-plus/colors.h"
#include "compiler.h"
#include "strings.h"
#include "lang.h"

#ifdef _WIN32 // separador de ruta para sistemas no windows
    #define PATH_SEPARATOR_CHAR '\\'
    #define PATH_SEPARATOR_STRING "\\"
#else // separador de ruta para linux o sistemas no windows
    #define PATH_SEPARATOR_CHAR '/'
    #define PATH_SEPARATOR_STRING "/"
#endif

#ifdef _WIN32
/* Unicode */
#define setlocaleU() setlocale(LC_ALL, "spanish")
#define fprintf(stream, format, ...) fwprintf(stream, L""format, ##__VA_ARGS__)
/* Unicode formats */
#define STRING_FORMAT "%S"
#define CHAR_FORMAT "%lc"

#else

#define setlocaleU()
#define STRING_FORMAT "%s"
#define CHAR_FORMAT "%lc"
#endif

/* Unicode codes */

#define A_ACENT "\u00E1"
#endif
