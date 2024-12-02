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
#ifndef _STRING_H_
#define _STRING_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "colors.h"
#include "class_c.h"

typedef class_c String_c {
    // metodos:
    CreateMethod(void, exec, class_c String_c*);                                             // constructor = void ConstructorClass(String_c)(String_c *my_string)
    CreateMethod(uint64_t, getSize, class_c String_c*);                                      // uint64_t getSize(string_c* my_string)
    CreateMethod(unsigned char*, setStr, class_c String_c*, const unsigned char*, uint64_t); // unsigned char* setStr(String_c *my_string, const unsigned char* string_c, uint64_t size_copy)
    CreateMethod(unsigned char*, getStr, class_c String_c*);                                 // unsigned char* getStr(String_c *my_string)
    CreateMethod(void, printStr, class_c String_c*, const char *, ...);                      // void printStr(String_c *my_string, const char *format, ...)
    CreateMethod(uint64_t, searchChar, class_c String_c*, unsigned char);                    // uint64_t searchChar(String_c *my_string, unsigned char chartter)
    // atributos:
    CreateAtribute(unsigned char*, str);
    CreateAtribute(uint64_t, size);
} String_c;

uint64_t getSize(String_c* my_string);

#include "string_class.c"
#endif