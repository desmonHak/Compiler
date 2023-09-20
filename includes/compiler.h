#ifndef _COMPILER_H_
#define _COMPILER_H_

#include "sintaxis/tokens.h"
#include "sintaxis/lexer.h"
#include "sintaxis/ast.h"
#include "sintaxis/parser.h"

void compile(char *src, Size_file src_size);
void compile_file(name_file name_file_open);

#include "compiler.c"
#endif