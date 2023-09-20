#ifndef _PARSER_C_
#define _PARSER_C_
#include "parser.h"
#include <stdio.h>
#include "ast.h"

parser_t *init_parser(lexer_t *lexer)
{
    parser_t *parser = (parser_t *)calloc(1, sizeof(parser_t));
    parser->lexer = lexer;
    parser->token = lexer_next_token(lexer);

    return parser;
}

token_t *parser_eat(parser_t *parser, unsigned int type)
{
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(token_t *, parser_eat) \
		TYPE_DATA_DBG(parser_t *, "parser = %p") \
        TYPE_DATA_DBG(unsigned int, "type = %s") \
		END_TYPE_FUNC_DBG, parser, token_type_to_str(type) \
	);
    #endif
    /*
     *
     *  Consume un token, comprueb si es del tipo esperado 
     *  y imprime un mensaje de error en el caso de no serlo.
     *  Si es el token esperado avanza el lexerr al siguiente token
     * 
     */
    if (parser->token->type != type)
    {
        printf("[Parser]: Token no esperado: %s, se esperaba un: %s \n", token_to_str(parser->token), token_type_to_str(type));
        exit(1);
    }
    parser->token = lexer_next_token(parser->lexer);
    return parser->token;
}

ast_t *parser_parser_id(parser_t *parser)
{
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_id) \
		TYPE_DATA_DBG(parser_t *, "parser = %p") \
		END_TYPE_FUNC_DBG, parser \
	);
    #endif
/*
 *
 *  Esta funcion se encarfa del analisis de identificadores.
 *  obtiene el valor del identificador(un nombre por ejemplo)
 *  y avanza al siguiente token.
 * 
 */
    char *value = calloc(strlen(parser->token->value) + 1, sizeof(char));
    strcpy(value, parser->token->value);
    parser_eat(parser, TOKEN_ID);

    // printf("ID --> %s\n", value);
    if (parser->token->type == TOKEN_ASIGNACION)
    {
        /*
         *
         *  Si el token es una asignacion, se crea un nodo en el AST
         *  para la asignacion y se continua analizando la expresion
         * 
         */
        // para asignacion
        parser_eat(parser, TOKEN_ASIGNACION);
        ast_t *ast = init_ast(AST_ASSIGNMENT);
        ast->name = value;
        printf("--> %s\n", ast->name);
        ast->value = parser_parser_expr(parser);
        return ast;
    }
    ast_t *ast = init_ast(AST_VARIABLE);
    ast->name = value;

    printf("%s  ===  %s\n",token_to_str(parser->token), value);
    if(parser->token->type == TOKEN_COLON){
        parser_eat(parser, TOKEN_COLON);

        while(parser->token->type == TOKEN_ID){
            ast->data_type = typename_to_int(parser->token->value);
            parser_eat(parser, TOKEN_ID);

            if(parser->token->type == TOKEN_LT){
                parser_eat(parser, TOKEN_LT);
                parser_eat(parser, TOKEN_RT);
            }
        }  
    }
    return ast;
}

ast_t *parser_parser_list(parser_t *parser)
{
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_list) \
		TYPE_DATA_DBG(parser_t *, "parser = %p") \
		END_TYPE_FUNC_DBG, parser \
	);
    #endif
    /*
     *
     *  Esta funcion analiza las expresiones separadas por comas y entre parentesis.
     *  Creando un nodo AST_COMPOUND y coloca las expresiones analizadas en
     *  sus hijos  
     * 
     */
    // se come un parentesis izquierdo(()
    parser_eat(parser, TOKEN_LPAREN);

    // se define que es una composicion y se pone en el ast:
    ast_t *ast = init_ast(AST_COMPOUND);

    // se pushea y se llama:
    list_push(ast->children, parser_parser_expr(parser));

    while (parser->token->type == TOKEN_COMMA)
    {
        parser_eat(parser, TOKEN_COMMA);
        list_push(ast->children, parser_parser_expr(parser));
    }
    parser_eat(parser, TOKEN_RPAREN);

    if(parser->token->type == TOKEN_COLON){
        parser_eat(parser, TOKEN_COLON);

        while(parser->token->type == TOKEN_ID){
            ast->data_type = typename_to_int(parser->token->value);
            parser_eat(parser, TOKEN_ID);

            if(parser->token->type == TOKEN_LT){
                parser_eat(parser, TOKEN_LT);
                parser_eat(parser, TOKEN_RT);
            }
        }  
    }

    return ast;
}

ast_t *parser_parser_int(parser_t *parser){
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_int) \
		TYPE_DATA_DBG(parser_t *, "parser = %p") \
		END_TYPE_FUNC_DBG, parser \
	);
    #endif
    /*
     *  
     *  Es funcion analiza los valores enteros, creando un nodo AST
     *  de tipo AST_VALUE y collocando dentro el valor analizado en sus hijos
     * 
     */
    // obtener el valor antes de eliminarlos
    
    uint64_t mi_value = atoll(parser->token->value);
    //printf("%s\n",parser->token->value);
    parser_eat(parser, TOKEN_INT);
    //printf("%s %d\n",token_to_str(lexer_next_token(parser->lexer)), mi_value);


    if(lexer_next_token(parser->lexer)->type == TOKEN_COMMA) parser_eat(parser, TOKEN_COMMA);
    //if(lexer_next_token(parser->lexer)->type == TOKEN_RPAREN) parser_eat(parser, TOKEN_RPAREN);

    ast_t *ast = init_ast(AST_VALUE);
    ast->value = mi_value;
    list_push(ast->children, parser_parser_expr(parser));
    return ast;
}

ast_t *parser_parser_macro_syscall(parser_t *parser){
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_macro_syscall) \
		TYPE_DATA_DBG(parser_t *, "parser = %p") \
		END_TYPE_FUNC_DBG, parser \
	);
    #endif
    parser_eat(parser, TOKKEN_MACRO_SYSCALL);
    ast_t *ast = init_ast(AST_SYSCALL);
    ast->name = malloc(sizeof(char) * strlen("syscall "));
    strcpy(ast->name, "syscall");

    list_c* valores_syscall = init_list(sizeof(uint64_t));

    if(parser->token->type == TOKEN_LCORCHETES){
        // comerser el corchete
        parser_eat(parser, TOKEN_LCORCHETES);
        // si el valor contenido entre los corchetes empieza por el nombre de un registro
        while(parser->token->type != TOKEN_RCORCHETES){
            // obetenemos el registro
            unsigned char *registro = parser->token->value;
            if (parser->token->type != TOKEN_REGISTRO) {
                /*
                 *
                 *  Si esto ocurre quiere decir que #syscall [] contenia dentro el primer registro
                 *  asignado correctamente en el formato <registro> = <valor>, pero que por algun
                 *  motivo los siguientes a este no seguian el formato,
                 * 
                 */
                if (parser->token->type == TOKEN_COMMA) 
                    printf_color("#{FG:lwhite}[#{FG:lred}Sintax error#{FG:lwhite}]#{FG:reset} : en #{FG:lred}%d#{FG:reset}, no se a expecificado un registro -> #{FG:lyellow}%s#{FG:reset}\n", parser->lexer->i, parser->token->value);
                else if (parser->token->type == TOKEN_INT) 
                    printf_color("#{FG:lwhite}[#{FG:lred}Sintax error#{FG:lwhite}]#{FG:reset} : en #{FG:lred}%d#{FG:reset}, no se a expecificado un registro al que asignar el valor -> #{FG:lyellow}%s#{FG:reset}\n", parser->lexer->i, parser->token->value);
                else 
                    printf_color("#{FG:lwhite}[#{FG:lred}Sintax error#{FG:lwhite}]#{FG:reset} : en #{FG:lred}%d#{FG:reset}, Usted no cerror la macro syscall -> #{FG:lyellow}%s#{FG:reset}\n", parser->lexer->i, parser->token->value);
                exit(1);
            }
            parser_eat(parser, TOKEN_REGISTRO);     // eliminamos el token del registro
            parser_eat(parser, TOKEN_ASIGNACION);   // eliminamos el simbolo de igual

            // obtenemos el valor entero y lo asociamos con el registroo
            ast->data_almacenada.nombre_valor.value.val64 = atoll(parser->token->value); 
            parser_eat(parser, TOKEN_INT);                   // comemos el token int

            ast->data_almacenada.nombre_valor.name = registro;
            printf("registro %s = %d\n", ast->data_almacenada.nombre_valor.name, ast->data_almacenada.nombre_valor.value.val64);
            
            // si el token siguiente al del valor es un token coma eliminarlo
            if(parser->token->type == TOKEN_COMMA) parser_eat(parser, TOKEN_COMMA);
        }
        parser_eat(parser, TOKEN_RCORCHETES);
    } else if(parser->token->type == TOKEN_LPAREN){
        // comerser el parentesis
        parser_eat(parser, TOKEN_LPAREN);

        while(parser->token->type != TOKEN_RPAREN){ // mientras no sea el parentesis final

            if (parser->token->type == TOKEN_INT){  // si el inicio del parentesis es un entero
                // si el valor contenido entre los parentesis empieza por un numero

                // guardar los valores obtenidos en un ast syscall con los registros:
                if (compiler_word_arch == 64){
                    // para 64 bits
                    ast->data_almacenada.nombre_valor.name = "aaa";
                    ast->data_almacenada.nombre_valor.value.val64 = atoll(parser->token->value); 
                    parser_eat(parser, TOKEN_INT);
                    parser_eat(parser, TOKEN_COMMA);
                } else if (compiler_word_arch == 32){
                    // para 32 bits
                } else if (compiler_word_arch == 16){
                    // para 16 bits
                }else {
                    printf("[parser_parser_macro_syscall] Este size de palabra no se tenia contemplado: %d\n", compiler_word_arch);
                    exit(1);
                }
                
            } else {
                printf_color("#{FG:lwhite}[#{FG:lred}Sintax error#{FG:lwhite}]#{FG:reset} : en #{FG:lred}%d#{FG:reset}, No es un valor entero -> #{FG:lyellow}%s#{FG:reset}\n", parser->lexer->i, parser->token->value);
                exit(1);
            }
        }
        // eliminar el ultimo parentesis del final
        parser_eat(parser, TOKEN_RPAREN);
    } else {
        printf_color("#{FG:lwhite}[#{FG:lred}Sintax error#{FG:lwhite}]#{FG:reset} : en #{FG:lred}%d#{FG:reset}, valor no esperado -> #{FG:lyellow}%s#{FG:reset}\n", parser->lexer->i, parser->token->value);
        exit(1);
    }
    
    //list_push(ast->children, parser_parser_expr(parser));
    /*list_push(ast->children);

    while(lexer_next_token(parser->lexer)->type == TOKEN_INT){

    }*/

    //list_push(ast->children, parser_parser_expr(parser));
    
    //printf("%s\n", parser->token->value);

    return ast;
}


void print_ast_recursive(ast_t* node, int indent, int is_last_child) {
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void, print_ast_recursive) \
		TYPE_DATA_DBG(ast_t*, "node = %p") \
        TYPE_DATA_DBG(ast_t*, "indent = %lu") \
        TYPE_DATA_DBG(ast_t*, "is_last_child = %lu") \
		END_TYPE_FUNC_DBG, node, indent, is_last_child \
	);
    #endif
    if (node == NULL) {
        return;
    }
    if (indent == 0){
        printf("|--- ");
    }
    for (int i = 0; i < indent - 1; i++) {
        printf(is_last_child ? " \t|" : "|\t");
    }

    if (indent > 0) {
        printf(is_last_child ? "--- " : "|--- ");
    }

    // Imprimir información sobre el nodo
    switch (node->type) {
        case AST_COMPOUND:
            printf("Compound(%s)\n", node->name);
            break;
        case AST_SYSCALL:
            printf("Syscall(%s)\n", node->name);
            break;
        case AST_ASSIGNMENT:
            printf("Assignment: %s\n", node->name);
            break;
        case AST_VARIABLE:
            printf("Variable: %s\n", node->name);
            break;
        case AST_STATEMENT:
            printf("Statement\n");
            break;
        case AST_NOOP:
            printf("Noop\n");
            break;
        case AST_VALUE:
            printf("Value(%llu)\n", node->value);
            break;
        // Agrega más casos según sea necesario para otros tipos de nodos
        default:
            printf("Unknown Node Type\n");
    }

    // Recorrer los hijos del nodo recursivamente
    for (size_t i = 0; i < node->children->size; i++) {
        int is_last = (i == node->children->size - 1);
        print_ast_recursive(node->children->items[i], indent + 1, is_last);
    }
}


// Función principal para imprimir el AST
void print_ast(ast_t* root) {
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void, print_ast) \
		TYPE_DATA_DBG(ast_t*, "root = %p") \
		END_TYPE_FUNC_DBG, root \
	);
    #endif
    if (root == NULL) {
        printf("AST is empty.\n");
        return;
    }

    printf("Abstract Syntax Tree:\n");
    print_ast_recursive(root, 0, 1); // El último hijo es verdadero al principio
}

ast_t *parser_parser_expr(parser_t *parser)
{
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_expr) \
		TYPE_DATA_DBG(parser_t *, "parser = %p") \
		END_TYPE_FUNC_DBG, parser \
	);
    #endif
    /*
     *
     *  Esta funcion analiza una expresion y llama a una funcion de analisis.
     *
     */
    switch (parser->token->type)
    {
    case TOKEN_ID:              return parser_parser_id(parser);
    //case TOKEN_LPAREN:          return parser_parser_list(parser);
    case TOKEN_RPAREN:           
        parser_eat(parser, TOKEN_RPAREN);
        return init_ast(AST_NOOP);
    case TOKKEN_MACRO_SYSCALL:  return parser_parser_macro_syscall(parser);
    case TOKEN_INT:             return parser_parser_int(parser);
    //case TOKEN_COMMA:           return init_ast(AST_NOOP);
    default:
        printf("[Parser]: Se esperaba un token %s\n", token_to_str(parser->token));
        exit(1);
    }
}

ast_t *parser_parser_compound(parser_t *parser)
{
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_compound) \
		TYPE_DATA_DBG(parser_t *, "parser = %p") \
		END_TYPE_FUNC_DBG, parser \
	);
    #endif
    ast_t *compound = init_ast(AST_COMPOUND);

    while (parser->token->type != TOKEN_EOF)
    {
        print_ast_recursive(compound, 0, 1);


        list_push(compound->children, parser_parser_expr(parser));
    }

    return init_ast(AST_NOOP);
}

ast_t *parser_parser(parser_t *parser)
{
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_compound) \
		TYPE_DATA_DBG(parser_t *, "parser = %p") \
		END_TYPE_FUNC_DBG, parser \
	);
    #endif
    // switch(parser->token->type){}
    return parser_parser_compound(parser);
}
#endif