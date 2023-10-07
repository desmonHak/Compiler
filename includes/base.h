/*
 *	Licencia Apache, Versión 2.0 con Modificación
 *	
 *	Copyright 2023 Desmon (David)
 *	
 *	Se concede permiso, de forma gratuita, a cualquier persona que obtenga una copia de 
 *	este software y archivos de documentación asociados (el "Software"), para tratar el 
 *	Software sin restricciones, incluidos, entre otros, los derechos de uso, copia, 
 *	modificación, fusión, publicación, distribución, sublicencia y/o venta de copias del 
 *	Software, y para permitir a las personas a quienes se les proporcione el Software 
 *	hacer lo mismo, sujeto a las siguientes condiciones:
 *	
 *	El anterior aviso de copyright y este aviso de permiso se incluirán en todas las 
 *	copias o partes sustanciales del Software.
 *	
 *	EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O 
 *	IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD 
 *	PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN. EN NINGÚN CASO LOS TITULARES DEL 
 *	COPYRIGHT O LOS TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE NINGÚN 
 *	RECLAMO, DAÑO U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE 
 *	OTRA MANERA, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTRO TIPO
 *	DE ACCIONES EN EL SOFTWARE.
 *	
 *	Además, cualquier modificación realizada por terceros se considerará propiedad del 
 *	titular original de los derechos de autor. Los titulares de derechos de autor 
 *	originales no se responsabilizan de las modificaciones realizadas por terceros.
 *	
 *	Queda explícitamente establecido que no es obligatorio especificar ni notificar los 
 *	cambios realizados entre versiones, ni revelar porciones específicas de código 
 *	modificado.
 */
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

#include <stddef.h>
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

#if defined(__x86_64__) /* 64 bit detected */
static unsigned  char compiler_word_arch = 64;
#elif defined(__i386__) /* 32 bit x86 detected */
static unsigned  char compiler_word_arch = 32;
#else 
static unsigned  char compiler_word_arch = 16;
#endif

static unsigned char* entry_point = NULL;



#include "colors-C-C-plus-plus/colors.h"
#include "structs_data/strings.h"
#include "compiler.h"

#include "lang.h"

#define INIT_TYPE_FUNC_DBG(type_return, name_func) "#{FG:lred} "#type_return" #{FG:cyan}"#name_func"#{FG:white}("
#define TYPE_DATA_DBG(type_data, name_arg) " #{FG:lyellow}"#type_data" #{FG:white} "name_arg", "
#define END_TYPE_FUNC_DBG "#{FG:white}); #{FG:reset}"

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
