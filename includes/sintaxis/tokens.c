/*
 *	Licencia Apache, Versión 2.0 con Modificación
 *	
 *	Copyright 2023 Desmon (David)
 *	
 *	Se concede permiso, de forma gratuita, a cualquier persona que obtenga una copia de 
 *	este software y archivos de documentación asociados (el "Software"), para tratar el 
 *	Software sin restricciones, incluidos, entre otros, los derechos de uso, copia, 
 *	modificación, fusión, publicación, distribución, sublicencia y/o venta de copias del 
 *	Software, y para permitir a las personas a quienes se les proporcione el Software 
 *	hacer lo mismo, sujeto a las siguientes condiciones:
 *	
 *	El anterior aviso de copyright y este aviso de permiso se incluirán en todas las 
 *	copias o partes sustanciales del Software.
 *	
 *	EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O 
 *	IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD 
 *	PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN. EN NINGÚN CASO LOS TITULARES DEL 
 *	COPYRIGHT O LOS TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE NINGÚN 
 *	RECLAMO, DAÑO U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE 
 *	OTRA MANERA, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTRO TIPO
 *	DE ACCIONES EN EL SOFTWARE.
 *	
 *	Además, cualquier modificación realizada por terceros se considerará propiedad del 
 *	titular original de los derechos de autor. Los titulares de derechos de autor 
 *	originales no se responsabilizan de las modificaciones realizadas por terceros.
 *	
 *	Queda explícitamente establecido que no es obligatorio especificar ni notificar los 
 *	cambios realizados entre versiones, ni revelar porciones específicas de código 
 *	modificado.
 */

#ifndef _TOKENS_C_
#define _TOKENS_C_
#include "tokens.h"

token_t* init_token(unsigned char* value, unsigned short type){
    // inicializa un token reservando memoria para el y dandole valores
    token_t * my_token = (token_t *)calloc(1, sizeof(token_t));
    my_token->type = type;
    my_token->value = value;
    my_token->line = linea_actual;
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
        case TOKEN_PUNTO:
            return "TOKEN_PUNTO";
        case TOKEN_STRING_SIMPLE:
            return "TOKEN_STRING_SIMPLE";
        case TOKEN_STRING_DOBLE:
            return "TOKEN_STRING_DOBLE";
        case TOKEN_DOC_STRING:
            return "TOKEN_DOC_STRING";
        case TOKKEN_MACRO_ENTRY_POINT:
            return "TOKKEN_MACRO_ENTRY_POINT";
        case TOKEN_SPACE:
            return "TOKEN_SPACE";
        case TOKEN_NEW_LINE:
            return "TOKEN_NEW_LINE";
        case TOKKEN_MACRO_WORD_SIZE:
            return "TOKKEN_MACRO_WORD_SIZE";
        default:
            printf("Este token no exite"); break;
    }
    return "not_stringable";
}


char* token_to_str(token_t* token){
    const char* type_str = token_type_to_str(token->type);
    char template[59];
    if (token->value[0] != '\0' && token->value[0] != '\n' && token->value[0] != '\r') 
        strcpy(template, "<type=%s, \tint_type=%d, \tvalue=%s, line=%"PRIu64">");
    else 
        strcpy(template, "<type=%s, \tint_type=%d, \tvalue=not printeable, line=%"PRIu64">");
    char* str = (char*)calloc(strlen(type_str) + (sizeof(template) / sizeof(const char) + 8), sizeof(char));
    sprintf(str, template, type_str, token->type, token->value, token->line);
    return str;

}

#endif