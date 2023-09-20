#ifndef _AST_C_
#define _AST_C_

#include "ast.h"

ast_t* init_ast(unsigned int type){
    ast_t* ast = (ast_t*)calloc(1, sizeof(ast_t));
    ast->type = type;
    //if (type == AST_COMPOUND) ast->children = init_list(sizeof(ast_t));
    ast->children = init_list(sizeof(ast_t));

    return ast;
}

#endif