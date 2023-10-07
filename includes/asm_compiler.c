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

#ifndef _ASM_COMPILER_C_
#define _ASM_COMPILER_C_
#include "asm_compiler.h"

unsigned char* format_intrucion(unsigned char* format, ...){
    /*
     *
     *  Formatea un string(la intruccion) con sus valores
     * 
     */

    unsigned char* instrucciones;
    va_list args;
    va_start(args, format);

    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(unsigned char*, format_intrucion) \
		TYPE_DATA_DBG(unsigned char*, "format = %s") \
        TYPE_DATA_DBG(va_list*, "... = %p") \
		END_TYPE_FUNC_DBG, format, args \
	);
    #endif

    size_t size = (vsnprintf(NULL, 0, format, args) + 1) * sizeof(unsigned char);
    debug_malloc(unsigned char, instrucciones, sizeof(unsigned char) * size);
    vsprintf(instrucciones, format, args);
    va_end(args);
    return instrucciones;
}

void get_tab_by_level(){
    /*
     *
     *  Devuelve una tabulacion con una cantidad especificada
     *  por tab_level
     *
     */
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void, get_tab_by_level) \
        "Tab level: %u"
		END_TYPE_FUNC_DBG,  tab_level \
	);
    #endif
    if (tab != NULL){
        free(tab);
    }
    tab = (char*)malloc(sizeof(char) * (tab_level +1));
    memset(tab, '\t', tab_level);
    tab[tab_level] = 0x0;
}

void asm_syscall(ast_t* node, list_c* list, size_t is_last){
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void, asm_syscall) \
		TYPE_DATA_DBG(ast_t*, "node = %p") \
        TYPE_DATA_DBG(list_c*, "list = %p") \
        TYPE_DATA_DBG(size_t, "is_last = %zu") \
		END_TYPE_FUNC_DBG, node, list, is_last \
	);
    #endif

    unsigned char* instrucciones = NULL;

    //printf("Syscall(%s)\n", node->name);
    //printf("pointer regs -> %p, size list: %lld\n", node->data_almacenada.regs, node->data_almacenada.nombre_valor->size);
    for(unsigned char i = 0; i < node->data_almacenada.nombre_valor->size; i++){
        name_value* values = (name_value*)(node->data_almacenada.nombre_valor->items[i]);
        if (!strcmp(values->name, "int")){
            instrucciones = format_intrucion(ASM_INTERRUPCION("%s")"\n", values->value.pointer);
            goto exit_not_syscall;
        } else if(!strcmp(values->name, "syscall")){
            instrucciones = format_intrucion(ASM_INTERRUPCION_SYSCALL()"\n");
            goto exit_not_syscall;
        }else{
            switch(compiler_word_arch){
                case 64:
                    /*
                    size = (snprintf(NULL, 0, ASM_MOV("%s", "%llu"), values->name, values->value.val64) + 1) * sizeof(unsigned char);
                    debug_malloc(unsigned char, instrucciones, sizeof(unsigned char) * size);
                    sprintf(instrucciones, ASM_MOV("%s", "%llu"), values->name, values->value.val64);
                    */
                    instrucciones = format_intrucion("%s"ASM_MOV("%s", "%llu"), tab, values->name, values->value.val64);
                    // printf("[%d] %s = %llu\n",i, values->name, values->value.val64);
                    break;
                case 32:
                    /*
                    size = (snprintf(NULL, 0, ASM_MOV("%s", "%u"), values->name, values->value.val32) + 1) * sizeof(unsigned char);
                    debug_malloc(unsigned char, instrucciones, sizeof(unsigned char) * size);
                    sprintf(instrucciones, ASM_MOV("%s", "%u"), values->name, values->value.val32);
                    */
                    instrucciones = format_intrucion("%s"ASM_MOV("%s", "%"SCNu32), tab, values->name, values->value.val32);
                    // printf("[%d] %s = %"SCNu32"\n",i, values->name, values->value.val32);
                    break;
                case 16:
                    /*
                    size = (snprintf(NULL, 0, ASM_MOV("%s", "%hu"), values->name, values->value.val16) + 1) * sizeof(unsigned char);
                    debug_malloc(unsigned char, instrucciones, sizeof(unsigned char) * size);
                    sprintf(instrucciones, ASM_MOV("%s", "%hu"), values->name, values->value.val16);
                    */
                    instrucciones = format_intrucion("%s"ASM_MOV("%s", "%u"), tab, values->name, values->value.val16);
                    // printf("[%d] %s = %hu\n",i, values->name, values->value.val16);
                    break;
                default:
                    printf("wtf con esta arquitectura\n");
            }
        }
        printf("%s\n", instrucciones);
        //printf("is_last = %zu\n",is_last);
        list_push(list, instrucciones);
    }
    switch(compiler_word_arch){
        case 64:
            instrucciones = format_intrucion("%s"ASM_INTERRUPCION_SYSCALL()"\n", tab);
            break;
        case 32:
            instrucciones = format_intrucion("%s"ASM_INTERRUPCION("0x%x")"\n", tab, 0x80);
            break;
        case 16:
            instrucciones = format_intrucion("%s"ASM_INTERRUPCION("0x%x")"\n", tab, 0x10);
            break;
    }
    exit_not_syscall:
        list_push(list, instrucciones);
        printf("%s\n", instrucciones);
}

void print_list_assembly(list_c* list){
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void, print_list_assembly) \

        TYPE_DATA_DBG(list_c*, "list = %p") \

		END_TYPE_FUNC_DBG,  list \
	);
    #endif
    for (size_t i = 0; i < list->size; i++){
        printf("%s\n", (unsigned char*)list->items[i]);
    }
}

void stringToHex(const char *input, char *output) {
    while (*input) {
        sprintf(output, "%02x", *input);  // Convierte el caracter a formato hexadecimal
        input++;
        output += 2;  // Avanza dos posiciones en la cadena de salida
    }
}

void convert_string_to_push_reverse(list_c* list, size_t frame, name_value *value){
    /*
     *
     *  Convierte una cadena de caracteres como "hola mundo" a una secuencia
     *  de movimientos a la pila en orden inverso:
     * 
     *      ; para una CPU de 64bits:
     *      push "do"
     *      push "hola mun" ;  64/8 bytes por movimieno a la pìla
     * 
     *      ; para una CPU de 32bits:
     *      push "do"
     *      push " mun"
     *      push "hola"
     * 
     *      ; para una CPU de 16bits:
     *      push "do"
     *      push "un"
     *      push " m"
     *      push "la"
     *      push "ho"
     * 
     *  De tal manera que se recibe el marco de pila actual y se calcula la direccion
     *  en run time de la pila donde se almacenan los datos.
     *
     */
    if (value->type_data != valor_string) return;
    // si el valor no es un string finalizar
    //list_c *list = init_list(sizeof(unsigned char*));
    size_t size_str = strlen(value->value.string); // tamaño del string
    unsigned char size_word = compiler_word_arch / 8; // tamaño de palabra para el que es destinada la instruccion
    unsigned char *value_str, *instrucciones;
    for (size_t i = 0; i < size_str; i += size_word){
        char cadenaHex[2 * size_word + 1];
        debug_calloc(unsigned char, value_str, 2 *size_word + 1, sizeof(unsigned char));
        // copiar una cantidad de size_word(16, 32, 64) bytes al nuevo buffer reservado
        memcpy(value_str, value->value.string + i, size_word);
        stringToHex(value_str, cadenaHex); // convertir el string de caracteres, a un string con su representacion hex
        if (i+size_word > size_str){
            if( size_str - i == 1) {
                instrucciones = format_intrucion("%s"ASM_MOV("byte  [BASE_STACk-0x%x]", "0x%s ; %s = n %s"), tab, i, cadenaHex, value->name, value->value);
            } else if( size_str - i == 2){
                instrucciones = format_intrucion("%s"ASM_MOV("word  [BASE_STACk-0x%x]", "0x%s ; %s =  %s"), tab, i, cadenaHex, value->name, value->value);
            } else if( size_str - i <= 4){
                instrucciones = format_intrucion("%s"ASM_MOV("dword  [BASE_STACk-0x%x]", "0x%s ; %s =  %s"), tab, i, cadenaHex, value->name, value->value);
            } else if( size_str - i <= 8){
                instrucciones = format_intrucion("%s"ASM_MOV("qword  [BASE_STACk-0x%x]", "0x%s ; %s =  %s"), tab, i, cadenaHex, value->name, value->value);
            } else{
                puts("error-?");
                exit(1);
            }
        } else{
            instrucciones = format_intrucion("%s"ASM_MOV("SIZE_T_SIZE_OPERATION  [BASE_STACk-0x%x]", "0x%s ; %s = %s"), tab, i, cadenaHex, value->name, value->value);
        }
        
        printf("%s\n", instrucciones);
        list_push(list, instrucciones);
        /*switch (compiler_word_arch)
        {
        case 64:

            break;
        
        default:
            break;
        }*/
    }
    //return list;

}

void asm_var_create(ast_t* node, list_c* list, size_t is_last){
    unsigned char* instrucciones = NULL;
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void, asm_var_create) \
		TYPE_DATA_DBG(ast_t*, "node = %p") \
        TYPE_DATA_DBG(list_c*, "list = %p") \
        TYPE_DATA_DBG(size_t, "is_last = %zu") \
		END_TYPE_FUNC_DBG, node, list, is_last \
	);
    #endif
    printf("Size stack frame: %zu\n", stack_frame.total_size_stack_frame);
        for (unsigned char i = 0; i < node->data_almacenada.nombre_valor->size; i++)
        {
            name_value *var = (name_value *)(node->data_almacenada.nombre_valor->items[i]);
            list_push(stack_frame.stack_frame_var, var); // guardar la variable en el stack
            printf("%s = ", var->name);
            switch (var->type_data)
            {
            case valor_8bits:
                printf("<8@%hhu>\n", var->value.val8);
                stack_frame.total_size_stack_frame += 1; // 1byte
                instrucciones = format_intrucion("%s"ASM_MOV("byte  [BASE_STACk-0x%x]%"PRIu64, " ; %s"), tab, stack_frame.total_size_stack_frame, var->value.val8, var->name);
                break;
            case valor_16bits:
                printf("<16@%hu>\n", var->value.val16);
                stack_frame.total_size_stack_frame += 2; // 2byte
                instrucciones = format_intrucion("%s"ASM_MOV("word  [BASE_STACk-0x%x]", "%u ; %s"), tab, stack_frame.total_size_stack_frame, var->value.val16, var->name);
                break;
            case valor_32bits:
                printf("<32@%"SCNu32">\n", var->value.val32);
                stack_frame.total_size_stack_frame += 4; // 4byte
                instrucciones = format_intrucion("%s"ASM_MOV("dword [BASE_STACk-0x%x]", "%"SCNu32"  ; %s"), tab, stack_frame.total_size_stack_frame, var->value.val32, var->name);
                break;
            case valor_64bits:
                printf("<64@%"PRIu64">\n", var->value.val64);
                stack_frame.total_size_stack_frame += 8; // 8byte
                instrucciones = format_intrucion("%s"ASM_MOV("qword [BASE_STACk-0x%x]%"PRIu64, " ; %s"), tab, stack_frame.total_size_stack_frame, var->value.val64, var->name);
                break;
            case valor_puntero_generico:
                printf("<pointer@%p>\n", var->value.pointer);
                stack_frame.total_size_stack_frame += (compiler_word_arch/8); // el tamaño de palabra al que se compila pero en byte
                break;
            case valor_string:
                //stack_frame.total_size_stack_frame += (compiler_word_arch/8); // el tamaño de palabra al que se compila pero en byte
                convert_string_to_push_reverse(list, stack_frame.total_size_stack_frame, var);
                stack_frame.total_size_stack_frame += strlen(var->value.string);
                printf("<string@'%s'>\n", var->value.string);
                break;
            default:
                printf(__FILE__ " Type data(%d)\n", node->type);
                break;
            }
        }
    // si se creo unanueva instruccion añadirlo
    if (instrucciones != NULL) list_push(list, instrucciones);
}

void asm_set_entry_point(ast_t* node, list_c* list, size_t is_last){
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO, \
            INIT_TYPE_FUNC_DBG(list_c*, asm_set_entry_point) \
            TYPE_DATA_DBG(ast_t*, "node = %p") \
            TYPE_DATA_DBG(list_c*, "list = %p") \
            TYPE_DATA_DBG(size_t, "is_last = %zu") \
            END_TYPE_FUNC_DBG, node, list, is_last \
        );
    #endif
    entry_point = (node->name);
    unsigned char* instrucciones = format_intrucion("%s"ASM_DEFINE("ENTRY_POINT", "%s"), tab, entry_point);
    list_push(list, instrucciones);
}

void asm_set_word_size(ast_t* node, list_c* list, size_t is_last){
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO, \
            INIT_TYPE_FUNC_DBG(list_c*, asm_set_word_size) \
            TYPE_DATA_DBG(ast_t*, "node = %p") \
            TYPE_DATA_DBG(list_c*, "list = %p") \
            TYPE_DATA_DBG(size_t, "is_last = %zu") \
            END_TYPE_FUNC_DBG, node, list, is_last \
        );
    #endif
    entry_point = (node->name);
    unsigned char* instrucciones = format_intrucion("%s"ASM_DEFINE("COMPILER_WORD_ARCh", "%hhu"), tab, compiler_word_arch);
    list_push(list, instrucciones);
}


list_c* get_list_assembly(ast_t* node, list_c* list, size_t is_last){
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(list_c*, get_list_assembly) \
		TYPE_DATA_DBG(ast_t*, "node = %p") \
        TYPE_DATA_DBG(list_c*, "list = %p") \
        TYPE_DATA_DBG(size_t, "is_last = %zu") \
		END_TYPE_FUNC_DBG, node, list, is_last \
	);
    #endif
    if (node == NULL) {
        return list;
    }

    switch (node->type) {
        case AST_NOOP: break;
        case AST_VAR:
            asm_var_create(node, list, is_last);
            break;
        case AST_INIT:
            puts("Nodo de inicio");
            break;
        case AST_COMPOUND:
            printf("Compound(%s)\n", node->name);
            break;
        case AST_FUNC_ETIQUETA:
            asm_funncion_etiqueta(node, list, is_last);
            break;
        case AST_SYSCALL:
            asm_syscall(node, list, is_last);
            break;
        case AST_ENTRY_POINT:
            asm_set_entry_point(node, list, is_last);
            break;
        case AST_WORD_SIZE:
            asm_set_word_size(node, list, is_last);
            break;
        default:
            printf(__FILE__" Unknown Node Type: %i\n", node->type);
            print_ast(node);
            exit(1);
    }


    // Recorrer los hijos del nodo recursivamente
    for (size_t i = 0; i < node->children->size; i++) {
        get_list_assembly(node->children->items[i], list, (i == node->children->size - 1));
    }
    return list;
}

void asm_funncion_etiqueta(ast_t* node, list_c* list, size_t is_last){
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void, asm_funncion_etiqueta) \
		TYPE_DATA_DBG(ast_t*, "node = %p") \
        TYPE_DATA_DBG(list_c*, "list = %p") \
        TYPE_DATA_DBG(size_t, "is_last = %zu") \
		END_TYPE_FUNC_DBG, node, list, is_last \
	);
    #endif
    list_push(list, format_intrucion("%s%s:", tab, node->name));
    tab_level++;
    get_tab_by_level();
}

list_c* convert_assembly(ast_t* ast){
    // lista donde se almacenara instrucciones asm
    list_c* list = (list_c*)init_list(sizeof(unsigned char*));
    char *header = malloc(sizeof(char)* (strlen("%include \"base.asm\"\n") + 1));
    strcpy(header, "%include \"base.asm\"\n");
    list_push(list, header);
    stack_frame.stack_frame_var = (list_c*)init_list(sizeof(name_value));// inicializar la lista enlazada del stack frame
    get_tab_by_level();

    return get_list_assembly(ast, list, 1);
}   

#endif