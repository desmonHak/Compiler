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

#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../structs_data_C/DebugLibC/debug_c.h"
#include "lexer.h"
#include "ast.h"
#include "types.h"
#include "../structs_data/list.h"

typedef struct PARSER_STRUCT
{
    lexer_t *lexer;
    token_t *token;
} parser_t;

parser_t *init_parser(lexer_t *lexer);
ast_t *parser_parser_int(parser_t *parser);
token_t *parser_eat(parser_t *parser, unsigned int type);
ast_t *parser_parser_id(parser_t *parser);
ast_t *parser_parser_expr(parser_t *parser);
ast_t *parser_parser_compound(parser_t *parser);
ast_t *parser_parser_list(parser_t *parser);
ast_t *parser_parser(parser_t *parser);
ast_t *parser_parser_macro_syscall(parser_t *parser);
void print_ast_recursive(ast_t *node, int indent, int is_last_child);
void print_ast(ast_t *root);

#include "parser.c"
#endif