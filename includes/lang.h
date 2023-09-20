#ifndef _LANG_H_
#define _LANG_H_

#include "base.h"

#ifdef ES_COMPILER
#define _LANG_COMPILER_ "ES"
#define USAGE_STRING_ARGV "uso: #{FG:lwhite}" NAME_COMPILER " #{FG:reset}"
#define HELP_STRING_ARGV  " [#{FG:lgreen}-h#{FG:reset}] [#{FG:lgreen}--ayuda#{FG:reset}] \tMuestra esta ayuda"
#define VERSION_STRING_ARGV  " [#{FG:lgreen}-v#{FG:reset}] [#{FG:lgreen}--version#{FG:reset}] \tMuesta la version actual del compilador"
#define ERROR_ARGV "#{FG:lwhite}[#{FG:lred}!#{FG:lwhite}] #{FG:reset}Este parametro propuesto es incorrecto o no existe"

#define VERSION_STING_EXEC "VERSION ACTUAL -> "
#endif 

#ifdef EN_COMPILER
#define _LANG_COMPILER_ "EN"
#define USAGE_STRING_ARGV "usage: " NAME_COMPILER " "
#define HELP_STRING_ARGV  " [#{FG:lgreen}-h#{FG:reset}] [#{FG:lgreen}--help#{FG:reset}] "
#define VERSION_STRING_ARGV  " [#{FG:lgreen}-v#{FG:reset}] [#{FG:lgreen}--version#{FG:reset}] "
#define ERROR_ARGV "#{FG:lwhite}[#{FG:lred}!#{FG:lwhite}] #{FG:reset}Este parametro propuesto es incorrecto o no existe"


#define VERSION_STING_EXEC "VERSION ACTUAL -> "
#endif

// si no se definio ningun idioma al compilar, compilar para ingles
#ifndef _LANG_COMPILER_
#undef _LANG_H_
#define ES_COMPILER
#include "lang.h"
#endif

#endif