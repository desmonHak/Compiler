#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../debug_c.h"
#include "lexer.h"
#include "ast.h"
#include "types.h"
#include "../structs_data/list.h"

typedef struct PARSER_STRUCT {
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
void print_ast_recursive(ast_t* node, int indent, int is_last_child);
void print_ast(ast_t* root);

#include "parser.c"
#endif