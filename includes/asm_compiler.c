#ifndef _ASM_COMPILER_C_
#define _ASM_COMPILER_C_
#include "asm_compiler.h"

list_c* convert_assembly(ast_t* ast){
    // lista donde se almacenara instrucciones asm
    list_c* list = (list_c*)init_list(sizeof(unsigned char*));

    switch (ast->type)
    {
    case AST_INIT:
        /* code */
        break;
    
    default:
        break;
    }
    return list;
}   

#endif