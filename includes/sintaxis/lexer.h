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