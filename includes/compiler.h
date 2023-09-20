#ifndef _COMPILER_H_
#define _COMPILER_H_
#include "tokens.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"

void compile(char *src, Size_file src_size);
void compile_file(name_file name_file_open);

#include "compiler.c"
#endif