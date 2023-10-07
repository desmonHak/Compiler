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

#ifndef _TOKENS_H_
#define _TOKENS_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

// lleva un conteo de la linea actual en la que se situa
static uint64_t linea_actual = 0;

typedef struct TOKEN_STRING {
    unsigned char* value;
    uint64_t line;
    enum {
        TOKEN_ID,
        TOKKEN_MACRO_SYSCALL, // para macros %/# syscall
        TOKKEN_MACRO_DEFINE,  // para macros %/# define
        TOKEN_LPAREN,         // para parentesis -> (
        TOKEN_RPAREN,         // para parentesis -> )
        TOKEN_LBRACE,         // para llaves     -> {
        TOKEN_RBRACE,         // para llaves     -> }
        TOKEN_COLON,          // para los dos puntos -> :
        TOKEN_SEMI,           // para los dos puntos -> ;
        TOKEN_COMMA,          // para las comas -> ,
        TOKEN_LT,             // para los -> >
        TOKEN_RT,             // para los -> <
        TOKEN_EOF,            // para el final del archivo 
        TOKEN_ASIGNACION,     // = asigna
        TOKEN_IGUAL,          // == comprueba si son iguales  
        TOKEN_INT,            // para enteros
        TOKEN_REGISTRE,       // para registros
        TOKEN_LCORCHETES,     // para el corchete izquierdo -> [
        TOKEN_RCORCHETES,     // para el corchete derecho -> ]
        TOKEN_REGISTRO,       // para eax, ebx, ecx, edx y etc
        TOKEN_PUNTO,          // para los puntos
        TOKEN_STRING_SIMPLE,  // para strings con comillas simples
        TOKEN_STRING_DOBLE,   // para strings con comillas dobles
        TOKEN_DOC_STRING,     // para doc string's (documentar)
        TOKKEN_MACRO_ENTRY_POINT, // define el punto de entrada
        TOKEN_SPACE, // para los espacios
        TOKEN_NEW_LINE, // para los saltos de linea
        TOKKEN_MACRO_WORD_SIZE, // define el size word de la arquitectura objetivo
    } type;
} token_t;


token_t* init_token(unsigned char* value, unsigned short type);
static const char* token_type_to_str(unsigned int type);
/*
// tokens del lenguaje
typedef enum tokens_global {
    macros,             // para macros -> % o #
    operadores          // para operadores -> +, -, =,
};

// tokens para operadores
typedef enum tipo_operadores {
    asignacion,         // =
    o_suma,             // +
    o_resta,            // -
    o_multplicacion,    // *
    o_division,         // /
    o_modulo,           // %
    o_and,              // &
    o_xor,              // ^
    o_not               // !
};

typedef enum tipo_macros {
    syscall,            // realiza syscall's
    define              
};
*/
#include "tokens.c"
#endif