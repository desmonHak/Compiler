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

#ifndef _LEXER_C_
#define _LEXER_C_
#include "lexer.h"

lexer_t* init_lexer(unsigned char *src, Size_file src_size){
    lexer_t *my_lexer = (lexer_t *)calloc(1, sizeof(lexer_t));
    my_lexer->src = src;
    my_lexer->src_size = src_size;
    my_lexer->i = 0;
    my_lexer->c = my_lexer->src[my_lexer->i];
    return my_lexer;
}

void lexer_advance(lexer_t* lexer){
    if (lexer->i < lexer->src_size && lexer->c != '\0'){
        lexer->i++;
        lexer->c = lexer->src[lexer->i];
    }
}


void lexer_skip_whitespace(lexer_t* lexer){
    // si la posicion antual es alguno de estos caracteres " \t\r\n"
    // saltar al siguiente caracter
    //while (lexer->c == '\r' || lexer->c == '\n' || lexer->c == ' ' || lexer->c == '\t')
    while (lexer->c == '\r' || lexer->c == '\t')
        lexer_advance(lexer);
}

token_t* lexer_parser_id(lexer_t* lexer){
    unsigned char * value = (unsigned char*)calloc(1, sizeof(unsigned char));

    while (isalnum(lexer->c) || lexer->c == '_')
    {
        value = (unsigned char*)realloc(value, (strlen(value) + 2) * sizeof(unsigned char));
        strcat(value, (char[]){lexer->c, 0});

        // siempre que el siguiente caracter sea una letra o un dijito, ejecutara lexer_advance, sino interumpe el bucle
        if (isalnum(lexer->src[lexer->i+1]) ||  lexer->src[lexer->i+1] == '_') 
            lexer_advance(lexer);
        else break;
    }

    #define registrosx86A !strcmp(value, "rax") || !strcmp(value, "eax") || !strcmp(value, "ax") || !strcmp(value, "ah") || !strcmp(value, "al")
    #define registrosx86B !strcmp(value, "rbx") || !strcmp(value, "ebx") || !strcmp(value, "bx") || !strcmp(value, "bh") || !strcmp(value, "bl")
    #define registrosx86C !strcmp(value, "rcx") || !strcmp(value, "ecx") || !strcmp(value, "cx") || !strcmp(value, "ch") || !strcmp(value, "cl")
    #define registrosx86D !strcmp(value, "rdx") || !strcmp(value, "edx") || !strcmp(value, "dx") || !strcmp(value, "dh") || !strcmp(value, "dl")

    // si el valor es un registro, retornar TOKEN_REGISTRO
    if (registrosx86A || registrosx86B || registrosx86C || registrosx86D) return init_token(value, TOKEN_REGISTRO);

    return init_token(value, TOKEN_ID);
}

token_t* lexer_advance_with(lexer_t* lexer, token_t* token){
    lexer_advance(lexer);
    return token;
}
token_t* lexer_advance_with_junp(lexer_t* lexer, token_t* token, unsigned int offset){
    /*
     *
     *  avanza el cursor del parser en un desplazamiento indicado por el offset
     *
     */
    if (lexer->i + offset < lexer->src_size && lexer->src[lexer->i+offset] != '\0'){
        lexer->i += offset;
        lexer->c = lexer->src[lexer->i];
    }
    //lexer_advance(lexer);
    return token;
}

unsigned char lexer_peek(lexer_t* lexer, unsigned int offset){
    //printf("min -> %"PRIu64"\n", MIN(lexer->i + offset, lexer->src_size));
    return lexer->src[MIN(lexer->i + offset, lexer->src_size)];
}

token_t* lexer_advance_current(lexer_t* lexer, unsigned int type){
    unsigned char * value = (unsigned char*)calloc(2, sizeof(unsigned char));
    value[0]= lexer->c; value[1] = '\0';
    token_t* token = init_token(value, type);
    lexer_advance(lexer);
    return token;
}

token_t* lexer_parser_number(lexer_t* lexer){
    /*
     *
     *  Esta funcion convierte un valor en entero asignando un token de tipo int
     *  permite detectar si es un valor hexadecimal, binario o decimal tmb
     *
     */

    unsigned char * value = (unsigned char*)calloc(1, sizeof(unsigned char));

    while (isdigit(lexer->c) || lexer->c == 'x' || lexer->c == 'b')
    {
        /*
         *
         *  Si es un digitol decimal(todos son numeros ),
         *  O un valor hexadimal (hay un caracter x de por medio),
         *  O un valor binario (hay un caracter b de por medio),
         *  Se considera como entero
         * 
         */
        value = (unsigned char*)realloc(value, (strlen(value) + 2) * sizeof(unsigned char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }
    return init_token(value, TOKEN_INT);
}

token_t* lexer_parser_string(lexer_t* lexer){
    unsigned short type_token = 0;
    unsigned char * value = (unsigned char*)calloc(1, sizeof(unsigned char));
    unsigned char caracter_prohibido = '"';
    if ( 
        lexer->src[lexer->i]   == '"' && 
        lexer->src[lexer->i+1] == '"' && 
        lexer->src[lexer->i+2] == '"'    
    ) {
        type_token = TOKEN_DOC_STRING;
        caracter_prohibido = '"';
        lexer_advance(lexer);lexer_advance(lexer);
    } else if (
        lexer->src[lexer->i]   == '\'' && 
        lexer->src[lexer->i+1] == '\'' && 
        lexer->src[lexer->i+2] == '\''   
    ) { 
        type_token = TOKEN_DOC_STRING;
        caracter_prohibido = '\'';
        lexer_advance(lexer);lexer_advance(lexer);
    } else if (
        lexer->src[lexer->i]   == '"'
    ) {
        type_token = TOKEN_STRING_DOBLE;
        caracter_prohibido = '"';
    } else if (lexer->src[lexer->i]   == '\'') {
        type_token = TOKEN_STRING_SIMPLE;
        caracter_prohibido = '\'';
    } 
    lexer_advance(lexer);

    while (1){
        // si se encontro una \ y no se encontr el caracter prohibido o uno de escape
        // se finaliza el bucle 
        //printf(" last(%c) %hu = %c -> caracter_prohibido  %hu = %c \n", lexer->src[lexer->i-1], lexer->c, lexer->c, caracter_prohibido, caracter_prohibido );
        if(
            (lexer->c == caracter_prohibido && lexer->src[lexer->i-1] != '\\') 
        ) { 
            //puts("ex");
            break;
        }
        /*else if (lexer->c == 0x0){
            puts("ERROR  lexer");
            exit(1);
        }*/

        value = (unsigned char*)realloc(value, (strlen(value) + 2) * sizeof(unsigned char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }
    lexer_advance(lexer);
    return init_token(value, type_token);
}

void print_tokents(lexer_t* lexer){
    token_t* tok;
    while((tok = lexer_next_token(lexer))->type != TOKEN_EOF){
        printf("%s\n", token_to_str(tok));
    }
}


token_t* lexer_next_token(lexer_t* lexer){
    volver:
    while (lexer->c != '\0')
    {
        lexer_skip_whitespace(lexer);
        
        /*
         *  analizar primero si es un digito con isdigit que llamar a isalnum, pues
         *  isalnum devuelve true para digitos y letras, por tanto puede interpretarse
         *  con un string un entero si no se realizar previamente isdigit.
         */
        //if (isdigit(lexer->c)) return lexer_advance_with(lexer, lexer_parser_number(lexer));
        if (isdigit(lexer->c)) return lexer_parser_number(lexer);

        if (isalnum(lexer->c) != 0 ) 
            return lexer_advance_with(lexer, lexer_parser_id(lexer));


        switch (lexer->c)
        {

        // para el simbolo de asignacion y igualacion
        case '=':
            if (lexer_peek(lexer, 1) == '=') return lexer_advance_with(lexer, init_token("==", TOKEN_IGUAL));
            return lexer_advance_with(lexer, init_token("=", TOKEN_ASIGNACION));
        case '#': //return lexer_advance_current(lexer, TOKKEN_MACRO_DEFINE);
        case '%':
            //if (isalnum (lexer_peek(lexer, 1))) return lexer_advance_with(lexer, init_token("#", TOKKEN_MACRO_DEFINE));
            //else printf("No se esperaba este caracter(lexer_peek): %c\n", lexer_peek(lexer, 1)); exit(1); break;
            // #syscall
            /*if (isalnum (lexer_peek(lexer, 1)) != 0 && lexer_peek(lexer, 1) == (unsigned char)'s')    {  
                return lexer_advance_with_junp(lexer, init_token("#syscall", TOKKEN_MACRO_SYSCALL), 9); // avanza luego 9 posiciones
            }
            // #define
            else if (isalnum (lexer_peek(lexer, 1)) != 0 && lexer_peek(lexer, 1) == (unsigned char)'d') 
                return lexer_advance_with_junp(lexer, init_token("#define", TOKKEN_MACRO_DEFINE), 8); // avanza luego 8 posiciones
            else{puts("que podra ser");}*/
            
            if (isalnum((int)lexer_peek(lexer, 1)) != 0){ 
                
                switch (lexer_peek(lexer, 1))
                {
                case 's':
                    return lexer_advance_with_junp(lexer, init_token("#syscall", TOKKEN_MACRO_SYSCALL), 8); // avanza luego 9 posiciones
                case 'd':
                    return lexer_advance_with_junp(lexer, init_token("#define", TOKKEN_MACRO_DEFINE), 7); // avanza luego 8 posiciones
                case 'w':
                    return lexer_advance_with_junp(lexer, init_token("#word_size", TOKKEN_MACRO_WORD_SIZE), 10); // avanza luego 8 posiciones
                case 'e':
                    return lexer_advance_with_junp(lexer, init_token("#entry_point", TOKKEN_MACRO_ENTRY_POINT), 12); // avanza luego 13 posiciones
                default:
                    puts("que podra ser");
                    return lexer_advance_current(lexer, TOKKEN_MACRO_DEFINE);
                }
            }
        case '"' :
        case '\'': return lexer_parser_string(lexer);
        case '_': return lexer_advance_with(lexer, lexer_parser_id(lexer));
        case '(': return lexer_advance_current(lexer, TOKEN_LPAREN);
        case ')': return lexer_advance_current(lexer, TOKEN_RPAREN);
        case '[': return lexer_advance_current(lexer, TOKEN_LCORCHETES);
        case ']': return lexer_advance_current(lexer, TOKEN_RCORCHETES);
        case '{': return lexer_advance_current(lexer, TOKEN_LBRACE);
        case '}': return lexer_advance_current(lexer, TOKEN_RBRACE);
        case ':': return lexer_advance_current(lexer, TOKEN_COLON);
        case ',': return lexer_advance_current(lexer, TOKEN_COMMA);
        case '>': return lexer_advance_current(lexer, TOKEN_LT);
        case '<': return lexer_advance_current(lexer, TOKEN_RT);
        case ';': return lexer_advance_current(lexer, TOKEN_SEMI);
        case '.': return lexer_advance_current(lexer, TOKEN_PUNTO);
        case '\0': break;
        case '\n': ++linea_actual ; return lexer_advance_current(lexer, TOKEN_NEW_LINE);
        case ' ': 
            //return lexer_advance_current(lexer, TOKEN_SPACE);
            lexer->c = lexer->src[++lexer->i];
            //printf("(%hhu), (%c), linea: %"PRIu64"\n", lexer->c, lexer->c, linea_actual);
            goto volver;
        default: printf("No se esperaba este caracter: (%hhu), (%c), linea: %"PRIu64"\n", lexer->c, lexer->c, linea_actual); exit(1); break;
        }
    }

    // si el while no se ejcuto, se encontro el final del archivo:
    return init_token(0, TOKEN_EOF);
}

#endif