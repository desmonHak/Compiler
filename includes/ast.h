#ifndef _AST_H_
#define _AST_H_

#include <stdint.h>

#include "list.h"

#if defined(__x86_64__) || defined(__i386__)
#include "assembly.h"
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
 *  Asocia un nombre con un valor, una estructura
 *  o un puntero.
 *  Se puede usar para descibir variables + valor, 
 *  registro + valor y etc.
 * 
 */
typedef struct name_value {
    unsigned char* name; // nombre
    union {
        uint8_t   val8;   // para valores de 8bits
        uint16_t val16;   // para valores de 16bits
        uint32_t val32;   // para valores de 32bits
        uint64_t val64;   // para valores de 64bits
        void*    pointer; // para punteros
    } value;             // valor asociado

} name_value;

typedef struct  AST_STRUCT
{
    enum {
        AST_COMPOUND,            // si es un compuesto
        AST_SYSCALL,             // para macros syscall
        //AST_FUNTION_DEFINITION,
        AST_FUNTION,
        AST_ASSIGNMENT,          // para asignaciones
        AST_DEFINITION_TYPE,
        AST_VARIABLE,            // para variabes
        AST_STATEMENT,           // para declaraciones
        AST_NOOP,                // no requiere una operacion
        AST_VALUE
        
    } type;
    list_c *children;
    char* name;
    struct AST_STRUCT* value;    // valor ast 
    int data_type;               // lugar donde almacenar el tipo
    
    union {
        name_value nombre_valor; 
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