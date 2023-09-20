#ifndef _TOKENS_C_
#define _TOKENS_C_
#include "tokens.h"

token_t* init_token(unsigned char* value, unsigned short type){
    // inicializa un token reservando memoria para el y dandole valores
    token_t * my_token = (token_t *)calloc(1, sizeof(token_t));
    my_token->type = type;
    my_token->value = value;
    return my_token;
}

static const char* token_type_to_str(unsigned int type){
    // que sea estativo hace que las cadenas se asignen en la pila
    switch (type)
    {
        case TOKEN_ID: 
            return "TOKEN_ID";
        case TOKKEN_MACRO_SYSCALL: // para macros %/# syscall
            return "TOKKEN_MACRO_SYSCALL";
        case TOKKEN_MACRO_DEFINE:  // para macros %/# define
            return "TOKKEN_MACRO_DEFINE";
        case TOKEN_LPAREN:         // para parentesis -> (
            return "TOKEN_LPAREN";
        case TOKEN_RPAREN:         // para parentesis -> )
            return "TOKEN_RPAREN";
        case TOKEN_LBRACE:         // para llaves     -> {
            return "TOKEN_LBRACE";
        case TOKEN_RBRACE:         // para llaves     -> }
            return "TOKEN_RBRACE";
        case TOKEN_COLON:          // para los dos puntos -> :
            return "TOKEN_COLON";
        case TOKEN_SEMI:           // para los dos puntos -> ;
            return "TOKEN_SEMI";
        case TOKEN_COMMA:          // para las comas -> ,
            return "TOKEN_COMMA";
        case TOKEN_LT:             // para los -> >
            return "TOKEN_LT";
        case TOKEN_RT:             // para los -> <
            return "TOKEN_RT";
        case TOKEN_EOF:            // para el final del archivo 
            return "TOKEN_EOF";
        case TOKEN_ASIGNACION:     // = asigna
            return "TOKEN_ASIGNACION";
        case TOKEN_IGUAL:          // == comprueba si son iguales  
            return "TOKEN_IGUAL";
        case TOKEN_INT:             // para enteros
            return "TOKEN_INT";
        case TOKEN_LCORCHETES:     // para el corchete izquierdo -> [
            return "TOKEN_LCORCHETES";
        case TOKEN_RCORCHETES:     // para el corchete derecho
            return "TOKEN_RCORCHETES";
        case TOKEN_REGISTRO:        // para eax, ebx, ecx, edx y etc
            return "TOKEN_REGISTRO";
        default:
            printf("Este token no exite"); break;
    }
    return "not_stringable";
}


char* token_to_str(token_t* token){
    const char* type_str = token_type_to_str(token->type);
    const char template[] = "<type=%s, \tint_type=%d, \tvalue=%s>";
    char* str = (char*)calloc(strlen(type_str) + (sizeof(template) / sizeof(const char) + 8), sizeof(char));
    sprintf(str, template, type_str, token->type, token->value);
    return str;

}

#endif