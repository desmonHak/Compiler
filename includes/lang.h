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