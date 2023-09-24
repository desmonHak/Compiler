#ifndef _AST_H_
#define _AST_H_

#include <stdint.h>

#include "../structs_data/list.h"

#if defined(__x86_64__) || defined(__i386__)
#include "../x86/assembly.h"
#else 
#error "Esta arquitectura no es x86"
#endif

#if defined(__x86_64__) /* 64 bit detected */

#elif defined(__i386__) /* 32 bit x86 detected */

#else 
#error "Esta arquitectura no es x86"
#endif

/*
 *
 *  Registro 1 = eax, 2 = ebx, 3 = ecx, ...
 * 
 */
#if defined(__x86_64__) /* 64 bit detected */
static char* string_ID_regs[] = {
    "rax","rbx","rcx",
    "rdx","rsi","rsi",
    "7","8","9",  "0"
};
#elif defined(__i386__) /* 32 bit x86 detected */
static char* string_ID_regs[] = {
    "eax","ebx","ecx",
    "edx","esi","esi",
    "7","8","9",  "0"
};
#else
static char* string_ID_regs[] = {
    "1","2","3",
    "4","5","6",
    "7","8","9",  "0"
};
#endif

typedef struct AST_STRUCT ast_t;

/*
 *
 *  Asocia un nombre con un valor, una estructura
 *  o un puntero.
 *  Se puede usar para descibir variables + valor, 
 *  registro + valor y etc.
 * 
 */
typedef struct name_value {
    unsigned char* name; // nombre
    union {
        uint8_t   val8;          // para valores de 8bits
        uint16_t val16;         // para valores de 16bits
        uint32_t val32;         // para valores de 32bits
        uint64_t val64;         // para valores de 64bits
        void*    pointer;       // para punteros
        ast_t*   ast_node;      // para otros nodos ast
        unsigned char* string;  // para strings
    } value;              // valor asociado
    unsigned char  type_data; // almaena el tipo de dato almacenado
    enum {
        valor_8bits,
        valor_16bits,
        valor_32bits,
        valor_64bits,
        valor_puntero_generico,
        valor_nodo_ast,
        valor_string
    } type_data_values;
} name_value;

typedef struct  AST_STRUCT
{
    enum {
        AST_INIT,                // inicio del ast
        AST_COMPOUND,            // si es un compuesto
        AST_SYSCALL,             // para macros syscall
        //AST_FUNTION_DEFINITION,
        AST_FUNTION,
        AST_ASSIGNMENT,          // para asignaciones
        AST_DEFINITION_TYPE,
        AST_VARIABLE,            // para variabes
        AST_STATEMENT,           // para declaraciones
        AST_NOOP,                // no requiere una operacion
        AST_VALUE,               // para valores enteros constantes
        AST_VAR,                 // para variables
        AST_END                  // final del ast
        
    } type;
    list_c *children;
    char* name;
    struct AST_STRUCT* value;    // valor ast 
    int data_type;               // lugar donde almacenar el tipo
    
    union {
        list_c* nombre_valor; // lista de name_value
        #if defined(__x86_64__) /* 64 bit detected */
        struct amd64_all_regs* regs;
        #elif defined(__i386__) /* 32 bit x86 detected */
        struct i386_all_regs* regs;
        #else 
        #error "Esta arquitectura no es x86"
        #endif
    
    } data_almacenada;          // datos que almacena el ast


} ast_t;

#include "ast.c"
#endif