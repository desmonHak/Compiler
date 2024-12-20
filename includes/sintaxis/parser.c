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

#ifndef _PARSER_C_
#define _PARSER_C_
#include "parser.h"

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
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(token_t *, parser_eat)
                    TYPE_DATA_DBG(parser_t *, "parser = %p")
                        TYPE_DATA_DBG(unsigned int, "type = %s")
                            END_TYPE_FUNC_DBG,
                parser, token_type_to_str(type));
#endif
    /*
     *
     *  Consume un token, comprueb si es del tipo esperado
     *  y imprime un mensaje de error en el caso de no serlo.
     *  Si es el token esperado avanza el lexerr al siguiente token
     *
     */
    while (parser->token->type == TOKEN_SPACE)
        parser->token = lexer_next_token(parser->lexer);
    if (TOKEN_SPACE == parser->token->type)
        return parser->token;
    if (TOKEN_SPACE == type && parser->token->type != type)
        return parser->token;
    if (parser->token->type != type)
    {
        printf("[Parser]: Token no esperado: %s, se esperaba un: %s \n", token_to_str(parser->token), token_type_to_str(type));
        exit(1);
    }
    parser->token = lexer_next_token(parser->lexer);
    return parser->token;
}

ast_t *paser_paser_var(unsigned char *type_data, unsigned char *name_id, parser_t *parser)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(ast_t *, paser_paser_var)
                    TYPE_DATA_DBG(unsigned char *, "name_id = %p")
                        TYPE_DATA_DBG(parser_t *, "parser = %p")
                            END_TYPE_FUNC_DBG,
                name_id, parser);
#endif
    /*
     *
     *  Se encarga de analizar variables
     *
     */
    // parser_eat(parser, TOKEN_ID); // comerse el ID

    // crear un nombre/dato
    name_value *data;
    debug_malloc(name_value, data, sizeof(name_value));
    data->name = name_id; // asignar el nombre de la variable a la estructura

    // crear un nodo ast de tipo variable
    ast_t *ast = init_ast(AST_VAR);

    /*
     *
     * iniciar la lista de nombres variables(puede ser que se este haciendo
     * varias declaraciones de variables en la misma linea)
     *
     */
    ast->data_almacenada.nombre_valor = init_list(sizeof(name_value));
    list_push(ast->data_almacenada.nombre_valor, data);

    parser_eat(parser, TOKEN_ASIGNACION);

    if (parser->token->type == TOKEN_STRING_SIMPLE)
    {
        // si el valor asignandose es un string de comillas simples
        data->value.string = parser->token->value;
        data->type_data = valor_string;
        parser_eat(parser, TOKEN_STRING_SIMPLE);
    }
    else if (parser->token->type == TOKEN_STRING_DOBLE)
    {
        // si el valor asignandose es un string de comillas dobles
        data->value.string = parser->token->value;
        data->type_data = valor_string;
        parser_eat(parser, TOKEN_STRING_DOBLE);
    }
    else if (parser->token->type == TOKEN_DOC_STRING)
    {
        // si el valor asignandose es un string de comillas dobles o simples pero triples
        data->value.string = parser->token->value;
        data->type_data = valor_string;
        parser_eat(parser, TOKEN_DOC_STRING);
    }
    else
    {
        // si no fue el caso
        switch (parser->token->type)
        {
        // si el valor es un numero constante entero
        case TOKEN_INT:
            if (type_data == NULL || strcmp(type_data, "uint64_t") == 0 || strcmp(type_data, "int64_t") == 0)
            {
                /*
                 *
                 *  Si el tipo de dato no fue espeificado(tipado dinamico), u
                 *  es de tipo uint64/int64 se guarda el valor como un entero de 64bits
                 *
                 */
                data->value.val64 = atoll(parser->token->value);
                data->type_data = valor_64bits;
            }
            else if (strcmp(type_data, "uint32_t") == 0 || strcmp(type_data, "int32_t") == 0)
            {
                data->value.val32 = atol(parser->token->value);
                data->type_data = valor_32bits;
            }
            else if (strcmp(type_data, "uint16_t") == 0 || strcmp(type_data, "int16_t") == 0)
            {
                data->value.val16 = atol(parser->token->value);
                data->type_data = valor_16bits;
            }
            else if (strcmp(type_data, "uint8_t") == 0 || strcmp(type_data, "int8_t") == 0)
            {
                data->value.val8 = atol(parser->token->value);
                data->type_data = valor_8bits;
            }
            else
            {
                DEBUG_PRINT(DEBUG_LEVEL_INFO, "tipo de dato desconocido: %s", type_data);
                // printf("tipo de dato desconocido: %s", type_data);
                exit(1);
            }
            parser_eat(parser, TOKEN_INT);
            break;
        /*case TOKEN_LCORCHETES:
            data->value.ast_node = parser_parser_int(parser);
            data->type_data = valor_nodo_ast;
            parser_eat(parser, TOKEN_LCORCHETES);
            break;*/
        default:
            DEBUG_PRINT(DEBUG_LEVEL_INFO, "No se esperaba este tipo de dato %s", token_to_str(parser->token));
            exit(1);
        }
    }

    // lexer_next_token(parser->lexer)->type
    if (parser->token->type == TOKEN_SEMI)
    {
        // si hay un punto y coma eliminarlo
        parser_eat(parser, TOKEN_SEMI);
    }
    return ast;
}

ast_t *parser_parser_funtion_etiqueta(unsigned char *name_id, parser_t *parser)
{

    if (parser->token->type == TOKEN_COLON)
    {
        // si hay dos puntos
        parser_eat(parser, TOKEN_COLON);
    }
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_funtion)
                    TYPE_DATA_DBG(unsigned char *, "name_id = %s")
                        TYPE_DATA_DBG(parser_t *, "parser = %p")
                            END_TYPE_FUNC_DBG,
                name_id, parser);
#endif
    ast_t *ast = init_ast(AST_FUNC_ETIQUETA);
    ast->name = name_id;
    ast->value = parser_parser_expr(parser); // hacer una nueva rama del ast que contendra los nodos ast para la funcion
    return ast;
}
ast_t *parser_parser_funtion(unsigned char *name_id, parser_t *parser)
{

    if (parser->token->type == TOKEN_COLON)
    {
        // si hay dos puntos
        parser_eat(parser, TOKEN_COLON);
    }
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_funtion)
                    TYPE_DATA_DBG(unsigned char *, "name_id = %s")
                        TYPE_DATA_DBG(parser_t *, "parser = %p")
                            END_TYPE_FUNC_DBG,
                name_id, parser);
#endif
    ast_t *ast = init_ast(AST_FUNC);
    ast->name = name_id;
    ast->value = parser_parser_expr(parser); // hacer una nueva rama del ast que contendra los nodos ast para la funcion
    return ast;
}

bool is_type_data(unsigned char *type)
{
    if (
        (strcmp(type, "uint8_t") == 0) ||
        (strcmp(type, "uint16_t") == 0) ||
        (strcmp(type, "uint32_t") == 0) ||
        (strcmp(type, "uint64_t") == 0) ||
        (strcmp(type, "int8_t") == 0) ||
        (strcmp(type, "int16_t") == 0) ||
        (strcmp(type, "int32_t") == 0) ||
        (strcmp(type, "int64_t") == 0) ||
        (strcmp(type, "string") == 0) ||
        (strcmp(type, "char") == 0) ||
        (strcmp(type, "float") == 0) ||
        (strcmp(type, "bool") == 0))
        return true;
    return false;
}

ast_t *parser_parser_id(parser_t *parser)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_id)
                    TYPE_DATA_DBG(parser_t *, "parser = %p")
                        END_TYPE_FUNC_DBG,
                parser);
#endif
    /*
     *
     *  Esta funcion se encarfa del analisis de identificadores.
     *  obtiene el valor del identificador(un nombre por ejemplo)
     *  y avanza al siguiente token.
     *
     */
    // ast_t *ast = NULL;

    unsigned char *name_id = NULL, *type_data = NULL;

    if (is_type_data(parser->token->value))
    {
        // si el ID coincide con el nombre de algun tipo de dato
        type_data = parser->token->value;
        parser_eat(parser, TOKEN_ID);
    }
    name_id = parser->token->value;
    parser_eat(parser, TOKEN_ID);

    switch (parser->token->type)
    {

    case TOKEN_ID:
    case TOKEN_ASIGNACION:
        // type_data == NULL se desconoce el tipo de dato
        // type_data != NULL se conoce el tipo de dato
        return paser_paser_var(type_data, name_id, parser);
    case TOKEN_LPAREN:
        return parser_parser_funtion(name_id, parser);
    case TOKEN_COLON:
        return parser_parser_funtion_etiqueta(name_id, parser);
    default:
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "No se esperaba este token %s", token_to_str(parser->token));
        exit(1);
    }
}

ast_t *parser_parser_list(parser_t *parser)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_list)
                    TYPE_DATA_DBG(parser_t *, "parser = %p")
                        END_TYPE_FUNC_DBG,
                parser);
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

    if (parser->token->type == TOKEN_COLON)
    {
        parser_eat(parser, TOKEN_COLON);

        while (parser->token->type == TOKEN_ID)
        {
            ast->data_type = typename_to_int(parser->token->value);
            parser_eat(parser, TOKEN_ID);

            if (parser->token->type == TOKEN_LT)
            {
                parser_eat(parser, TOKEN_LT);
                parser_eat(parser, TOKEN_RT);
            }
        }
    }

    return ast;
}

ast_t *parser_parser_int(parser_t *parser)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_int)
                    TYPE_DATA_DBG(parser_t *, "parser = %p")
                        END_TYPE_FUNC_DBG,
                parser);
#endif
    /*
     *
     *  Es funcion analiza los valores enteros, creando un nodo AST
     *  de tipo AST_VALUE y collocando dentro el valor analizado en sus hijos
     *
     */
    // obtener el valor antes de eliminarlos

    uint64_t mi_value = atoll(parser->token->value);
    // printf("%s\n",parser->token->value);
    parser_eat(parser, TOKEN_INT);
    // printf("%s %d\n",token_to_str(lexer_next_token(parser->lexer)), mi_value);

    if (lexer_next_token(parser->lexer)->type == TOKEN_COMMA)
        parser_eat(parser, TOKEN_COMMA);
    // if(lexer_next_token(parser->lexer)->type == TOKEN_RPAREN) parser_eat(parser, TOKEN_RPAREN);

    ast_t *ast = init_ast(AST_VALUE);
    ast->data_almacenada.nombre_valor = init_list(sizeof(name_value));

    name_value *data;
    debug_malloc(name_value, data, sizeof(name_value));
    data->name = NULL;
    data->value.val64 = mi_value;
    list_push(ast->data_almacenada.nombre_valor, data);

    list_push(ast->children, parser_parser_expr(parser));
    return ast;
}

ast_t *parser_parser_macro_syscall(parser_t *parser)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_macro_syscall)
                    TYPE_DATA_DBG(parser_t *, "parser = %p")
                        END_TYPE_FUNC_DBG,
                parser);
#endif
    parser_eat(parser, TOKKEN_MACRO_SYSCALL);
    ast_t *ast = init_ast(AST_SYSCALL);
    ast->name = malloc(sizeof(char) * strlen("syscall "));
    strcpy(ast->name, "syscall");

    printf("Token analizado: %s\n", token_to_str(parser->token));
    if (parser->token->type == TOKEN_LCORCHETES)
    {
        // comerser el corchete
        parser_eat(parser, TOKEN_LCORCHETES);
        // si el valor contenido entre los corchetes empieza por el nombre de un registro
        ast->data_almacenada.nombre_valor = init_list(sizeof(name_value));

        while (parser->token->type != TOKEN_RCORCHETES)
        {
            // obetenemos el registro
            unsigned char *registro = parser->token->value;

            /*
             *
             *  Si se encontro un punto se econtro un atributo, por lo que se elimina el punto y se
             *  Espera obtener un token id que sea el nombre del atributo
             *
             */
            if (parser->token->type == TOKEN_PUNTO)
            {
                parser_eat(parser, TOKEN_PUNTO);
                name_value *data;
                debug_malloc(name_value, data, sizeof(name_value));

                if (!strcmp(parser->token->value, "int"))
                {
                    // guardamos int:
                    data->name = parser->token->value;

                    parser_eat(parser, TOKEN_ID);
                    parser_eat(parser, TOKEN_ASIGNACION);

                    // guardamos el valor de la interrupcion:
                    data->value.pointer = parser->token->value;
                    parser_eat(parser, TOKEN_INT);
                }
                else if (!strcmp(parser->token->value, "syscall"))
                {
                    data->name = parser->token->value;
                    parser_eat(parser, TOKEN_ID);
                }
                else
                {
                    puts("Este atributo no existe");
                    exit(1);
                }
                list_push(ast->data_almacenada.nombre_valor, data);
                // si el token siguiente al del valor es un token coma eliminarlo
                if (parser->token->type == TOKEN_COMMA)
                    parser_eat(parser, TOKEN_COMMA);
                continue;
            }

            // volver:
            if (parser->token->type != TOKEN_REGISTRO)
            {
                /*
                 *
                 *  Si esto ocurre quiere decir que #syscall [] contenia dentro el primer registro
                 *  asignado correctamente en el formato <registro> = <valor>, pero que por algun
                 *  motivo los siguientes a este no seguian el formato,
                 *
                 */
                /*if (parser->token->type == TOKEN_SPACE) {
                    // si se trataba de un espacio el token, se elimina y se vuelve atras
                    parser_eat(parser, TOKEN_SPACE);
                    goto volver;
                }*/

                // printf("%s\n",token_to_str(lexer_next_token(parser->lexer)));
                switch (parser->token->type ){
                    case TOKEN_COMMA:
                        printf_color("#{FG:lwhite}[#{FG:lred}Sintax error#{FG:lwhite}]#{FG:reset} : en #{FG:lred}%d#{FG:reset}, no se a expecificado un registro -> #{FG:lyellow}%s#{FG:reset}\n", parser->lexer->i, parser->token->value);
                    case TOKEN_INT:
                        printf_color("#{FG:lwhite}[#{FG:lred}Sintax error#{FG:lwhite}]#{FG:reset} : en #{FG:lred}%d#{FG:reset}, no se a expecificado un registro al que asignar el valor -> #{FG:lyellow}%s#{FG:reset}\n", parser->lexer->i, parser->token->value);
                    default:
                        printf_color("#{FG:lwhite}[#{FG:lred}Sintax error#{FG:lwhite}]#{FG:reset} : en #{FG:lred}%d#{FG:reset}, Usted no cerro la macro syscall -> #{FG:lyellow}%s#{FG:reset}\n", parser->lexer->i, parser->token->value);
                }
                exit(1);
            }

            parser_eat(parser, TOKEN_REGISTRO);   // eliminamos el token del registro
            parser_eat(parser, TOKEN_ASIGNACION); // eliminamos el simbolo de igual

            name_value *data;
            debug_malloc(name_value, data, sizeof(name_value));

            // obtenemos el valor entero y lo asociamos con el registroo
            data->value.val64 = atoll(parser->token->value);
            parser_eat(parser, TOKEN_INT); // comemos el token int

            data->name = registro;
            printf("registro %s = %llu\n", data->name, data->value.val64);
            list_push(ast->data_almacenada.nombre_valor, data);
            // si el token siguiente al del valor es un token coma eliminarlo
            if (parser->token->type == TOKEN_COMMA)
                parser_eat(parser, TOKEN_COMMA);
        }
        parser_eat(parser, TOKEN_RCORCHETES);
    }
    else if (parser->token->type == TOKEN_LPAREN)
    {
        // comerser el parentesis
        parser_eat(parser, TOKEN_LPAREN);
        unsigned char counter = 0; // contador de registros
        ast->data_almacenada.nombre_valor = init_list(sizeof(name_value));
        while (parser->token->type != TOKEN_RPAREN)
        { // mientras no sea el parentesis final

            if (parser->token->type == TOKEN_INT)
            { // si el inicio del parentesis es un entero
                // si el valor contenido entre los parentesis empieza por un numero
                name_value *data;
                debug_malloc(name_value, data, sizeof(name_value));

                // guardar los valores obtenidos en un ast syscall con los registros:
                if (compiler_word_arch == 64)
                {
                    // para 64 bits
                    data->value.val64 = atoll(parser->token->value);
                    data->name = string_ID_regs_amd64[counter];
                    counter++;
                }
                else if (compiler_word_arch == 32)
                {
                    // para 32 bits
                    data->value.val32 = atol(parser->token->value);
                    data->name = string_ID_regs_i386[counter];
                    counter++;
                }
                else if (compiler_word_arch == 16)
                {
                    // para 16 bits
                    data->value.val16 = atoi(parser->token->value);
                    data->name = string_ID_regs_8086[counter];
                    counter++;
                }
                else
                {
                    printf("[parser_parser_macro_syscall] Este size de palabra no se tenia contemplado: %d\n", compiler_word_arch);
                    exit(1);
                }
                list_push(ast->data_almacenada.nombre_valor, data);
                printf("registro numero %s -> value = %" PRIu64 "\n", data->name, data->value.val64);

                if (parser->token->type == TOKEN_INT)
                    parser_eat(parser, TOKEN_INT);
                else
                    puts("[eror sintaxis] falta un numero");
                if (parser->token->type == TOKEN_COMMA)
                    parser_eat(parser, TOKEN_COMMA);
                else
                { // se encontro el ultimo numero de la macro, el cual no tiene coma
                    puts("final de la macro");
                }
            }
            else
            {
                printf_color("#{FG:lwhite}[#{FG:lred}Sintax error#{FG:lwhite}]#{FG:reset} : en #{FG:lred}%d#{FG:reset}, No es un valor entero -> #{FG:lyellow}%s#{FG:reset}\n", parser->lexer->i, parser->token->value);
                exit(1);
            }
        }
        // eliminar el ultimo parentesis del final
        parser_eat(parser, TOKEN_RPAREN);
    }
    else
    {
        printf_color("#{FG:lwhite}[#{FG:lred}Sintax error#{FG:lwhite}]#{FG:reset} : en #{FG:lred}%d#{FG:reset}, valor no esperado -> #{FG:lyellow}%s#{FG:reset}\n", parser->lexer->i, parser->token->value);
        exit(1);
    }

    // list_push(ast->children, parser_parser_expr(parser));
    /*list_push(ast->children);

    while(lexer_next_token(parser->lexer)->type == TOKEN_INT){

    }*/

    // list_push(ast->children, parser_parser_expr(parser));

    // printf("%s\n", parser->token->value);

    return ast;
}

ast_t *parser_parser_macro_entry_point(parser_t *parser)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_macro_entry_point)
                    TYPE_DATA_DBG(parser_t *, "parser = %p")
                        END_TYPE_FUNC_DBG,
                parser);
#endif
    ast_t *ast = init_ast(AST_ENTRY_POINT);
    parser_eat(parser, TOKKEN_MACRO_ENTRY_POINT);
    ast->name = parser->token->value;
    parser_eat(parser, TOKEN_ID);
    return ast;
}

ast_t *parser_parser_word_size(parser_t *parser)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_word_size)
                    TYPE_DATA_DBG(parser_t *, "parser = %p")
                        END_TYPE_FUNC_DBG,
                parser);
#endif
    ast_t *ast = init_ast(AST_WORD_SIZE);
    parser_eat(parser, TOKKEN_MACRO_WORD_SIZE);
    compiler_word_arch = atol(parser->token->value);
    parser_eat(parser, TOKEN_INT);
    return ast;
}

void print_ast_recursive(ast_t *node, int indent, int is_last_child)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, print_ast_recursive)
                    TYPE_DATA_DBG(ast_t *, "node = %p")
                        TYPE_DATA_DBG(ast_t *, "indent = %lu")
                            TYPE_DATA_DBG(ast_t *, "is_last_child = %lu")
                                END_TYPE_FUNC_DBG,
                node, indent, is_last_child);
#endif
    if (node == NULL)
    {
        return;
    }
    if (indent == 0)
    {
        printf("|--- ");
    }
    for (int i = 0; i < indent - 1; i++)
    {
        printf(is_last_child ? " \t|" : "|\t");
    }

    if (indent > 0)
    {
        printf(is_last_child ? "--- " : "|--- ");
    }

    // Imprimir información sobre el nodo
    switch (node->type)
    {
    case AST_INIT:
        puts("Nodo de inicio");
        break;
    case AST_COMPOUND:
        printf("Compound(%s)\n", node->name);
        break;
    case AST_SYSCALL:
        printf("Syscall(%s)\n", node->name);
        printf("pointer regs -> %p, size list: %lld\n", node->data_almacenada.regs, node->data_almacenada.nombre_valor->size);
        for (unsigned char i = 0; i < node->data_almacenada.nombre_valor->size; i++)
        {
            name_value *values = (name_value *)(node->data_almacenada.nombre_valor->items[i]);
            if (compiler_word_arch == 64)
            {
                printf("[%d] %s = %llu\n", i, values->name, values->value.val64);
            }
            else if (compiler_word_arch == 32)
            {
                printf("[%d] %s = %" SCNu32 "\n", i, values->name, values->value.val32);
            }
            else if (compiler_word_arch == 16)
            {
                printf("[%d] %s = %hu\n", i, values->name, values->value.val16);
            }
            else
            {
                puts("wtf");
            }
        }
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
        printf("Value(%p)\n", node->value);
        break;
    case AST_FUNC_ETIQUETA:
        printf("Name funcion: %s\n", node->name);
        printf("Pointer Node AST: %p\n", node->value);
        break;
    case AST_WORD_SIZE:
        printf("set word size to: %hhu\n", compiler_word_arch);
        break;
    case AST_ENTRY_POINT:
        printf("punto de entrada establecido en %s\n", node->name);
        break;
    case AST_VAR:
        for (unsigned char i = 0; i < node->data_almacenada.nombre_valor->size; i++)
        {
            name_value *var = (name_value *)(node->data_almacenada.nombre_valor->items[i]);
            printf("%s = ", var->name);
            switch (var->type_data)
            {
            case valor_8bits:
                printf("<8@%hhu>\n", var->value.val8);
                break;
            case valor_16bits:
                printf("<16@%hu>\n", var->value.val16);
                break;
            case valor_32bits:
                printf("<32@%" SCNu32 ">\n", var->value.val32);
                break;
            case valor_64bits:
                printf("<64@%" PRIu64 ">\n", var->value.val64);
                break;
            case valor_puntero_generico:
                printf("<pointer@%p>\n", var->value.pointer);
                break;
            case valor_nodo_ast:
                printf("<ast@%p>\n", var->value.ast_node);
                print_ast(var->value.ast_node);
            case valor_string:
                printf("<string@'%s'>\n", var->value.string);
                break;
            default:
                break;
            }
        }
        break;
    default:
        printf("Unknown Node Type(%d)\n", node->type);
    }

    // Recorrer los hijos del nodo recursivamente
    for (size_t i = 0; i < node->children->size; i++)
    {
        int is_last = (i == node->children->size - 1);
        print_ast_recursive(node->children->items[i], indent + 1, is_last);
    }
}

// Función principal para imprimir el AST
void print_ast(ast_t *root)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, print_ast)
                    TYPE_DATA_DBG(ast_t *, "root = %p")
                        END_TYPE_FUNC_DBG,
                root);
#endif
    if (root == NULL)
    {
        printf("AST is empty.\n");
        return;
    }

    printf("Abstract Syntax Tree(size: %zu): \n", root->children->size);
    print_ast_recursive(root, 0, 1); // El último hijo es verdadero al principio
}

ast_t *parser_parser_expr(parser_t *parser)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_expr)
                    TYPE_DATA_DBG(parser_t *, "parser = %p")
                        END_TYPE_FUNC_DBG,
                parser);
#endif
    /*
     *
     *  Esta funcion analiza una expresion y llama a una funcion de analisis.
     *
     */
    printf("Token %s\n", token_to_str(parser->token));
    switch (parser->token->type)
    {
    case TOKEN_ID:
        return parser_parser_id(parser);
    // case TOKEN_LPAREN:          return parser_parser_list(parser);
    /*case TOKEN_RPAREN:
        parser_eat(parser, TOKEN_RPAREN);
        return init_ast(AST_NOOP);*/
    case TOKEN_SPACE:
        parser_eat(parser, TOKEN_SPACE);
    case TOKEN_NEW_LINE:
        parser_eat(parser, TOKEN_NEW_LINE);
        return init_ast(AST_NOOP);
    case TOKKEN_MACRO_SYSCALL:
        return parser_parser_macro_syscall(parser);
    case TOKEN_INT:
        return parser_parser_int(parser);
    // case TOKEN_COMMA:           return init_ast(AST_NOOP);
    case TOKEN_EOF:
        return init_ast(AST_END);
        puts("Token EOF");
    case TOKKEN_MACRO_ENTRY_POINT:
        return parser_parser_macro_entry_point(parser);
    case TOKKEN_MACRO_WORD_SIZE:
        return parser_parser_word_size(parser);
    default:
        printf("[Parser]: Se esperaba un token %s\n", token_to_str(parser->token));
        exit(1);
    }
    // solo se ejecuta si se finaliza el switch
    return parser_parser_expr(parser);
}

ast_t *parser_parser_compound(parser_t *parser)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(ast_t *, parser_parser_compound)
                    TYPE_DATA_DBG(parser_t *, "parser = %p")
                        END_TYPE_FUNC_DBG,
                parser);
#endif
    ast_t *compound = init_ast(AST_INIT);
    while (parser->token->type != TOKEN_EOF)
    {
        // print_ast_recursive(compound, 0, 1);
        list_push(compound->children, parser_parser_expr(parser));
    }

    return compound;
}

ast_t *parser_parser(parser_t *parser)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(ast_t *, parser_parser)
                    TYPE_DATA_DBG(parser_t *, "parser = %p")
                        END_TYPE_FUNC_DBG,
                parser);
#endif
    // switch(parser->token->type){}
    return parser_parser_compound(parser);
}
#endif