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

#ifndef _LEXER_H_
#define _LEXER_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"
#include "../WL_lib/WL_lib.h"

#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b

typedef struct LEXER_STRUCT {
    unsigned char *src;
    Size_file src_size;  // tamaño del documento
    unsigned char c;
    unsigned int i;
} lexer_t;

lexer_t* init_lexer(unsigned char *src, Size_file src_size);
void lexer_advance(lexer_t* lexer);
void lexer_skip_whitespace(lexer_t* lexer);
token_t* lexer_parser_id(lexer_t* lexer);
token_t* lexer_advance_with(lexer_t* lexer, token_t* token);
token_t* lexer_advance_with_junp(lexer_t* lexer, token_t* token, unsigned int offset);
unsigned char lexer_peek(lexer_t* lexer, unsigned int offset);
token_t* lexer_advance_current(lexer_t* lexer, unsigned int type);
token_t* lexer_parser_number(lexer_t* lexer);
token_t* lexer_next_token(lexer_t* lexer);
void print_tokents(lexer_t* lexer);

#include "lexer.c"
#endif