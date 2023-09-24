#ifndef _TOKENS_H_
#define _TOKENS_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct TOKEN_STRING {
    unsigned char* value;
    enum {
        TOKEN_ID,
        TOKKEN_MACRO_SYSCALL, // para macros %/# syscall
        TOKKEN_MACRO_DEFINE,  // para macros %/# define
        TOKEN_LPAREN,         // para parentesis -> (
        TOKEN_RPAREN,         // para parentesis -> )
        TOKEN_LBRACE,         // para llaves     -> {
        TOKEN_RBRACE,         // para llaves     -> }
        TOKEN_COLON,          // para los dos puntos -> :
        TOKEN_SEMI,           // para los dos puntos -> ;
        TOKEN_COMMA,          // para las comas -> ,
        TOKEN_LT,             // para los -> >
        TOKEN_RT,             // para los -> <
        TOKEN_EOF,            // para el final del archivo 
        TOKEN_ASIGNACION,     // = asigna
        TOKEN_IGUAL,          // == comprueba si son iguales  
        TOKEN_INT,            // para enteros
        TOKEN_REGISTRE,       // para registros
        TOKEN_LCORCHETES,     // para el corchete izquierdo -> [
        TOKEN_RCORCHETES,     // para el corchete derecho -> ]
        TOKEN_REGISTRO,       // para eax, ebx, ecx, edx y etc
        TOKEN_PUNTO,          // para los puntos
        TOKEN_STRING_SIMPLE,  // para strings con comillas simples
        TOKEN_STRING_DOBLE,   // para strings con comillas dobles
        TOKEN_DOC_STRING,     // para doc string's (documentar)
    } type;
} token_t;


token_t* init_token(unsigned char* value, unsigned short type);
static const char* token_type_to_str(unsigned int type);
/*
// tokens del lenguaje
typedef enum tokens_global {
    macros,             // para macros -> % o #
    operadores          // para operadores -> +, -, =,
};

// tokens para operadores
typedef enum tipo_operadores {
    asignacion,         // =
    o_suma,             // +
    o_resta,            // -
    o_multplicacion,    // *
    o_division,         // /
    o_modulo,           // %
    o_and,              // &
    o_xor,              // ^
    o_not               // !
};

typedef enum tipo_macros {
    syscall,            // realiza syscall's
    define              
};
*/
#include "tokens.c"
#endif