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

    unsigned char* instrucciones;

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
                    instrucciones = format_intrucion(ASM_MOV("%s", "%llu"), values->name, values->value.val64);
                    // printf("[%d] %s = %llu\n",i, values->name, values->value.val64);
                    break;
                case 32:
                    /*
                    size = (snprintf(NULL, 0, ASM_MOV("%s", "%u"), values->name, values->value.val32) + 1) * sizeof(unsigned char);
                    debug_malloc(unsigned char, instrucciones, sizeof(unsigned char) * size);
                    sprintf(instrucciones, ASM_MOV("%s", "%u"), values->name, values->value.val32);
                    */
                    instrucciones = format_intrucion(ASM_MOV("%s", "%llu"), values->name, values->value.val64);
                    // printf("[%d] %s = %u\n",i, values->name, values->value.val32);
                    break;
                case 16:
                    /*
                    size = (snprintf(NULL, 0, ASM_MOV("%s", "%hu"), values->name, values->value.val16) + 1) * sizeof(unsigned char);
                    debug_malloc(unsigned char, instrucciones, sizeof(unsigned char) * size);
                    sprintf(instrucciones, ASM_MOV("%s", "%hu"), values->name, values->value.val16);
                    */
                    instrucciones = format_intrucion(ASM_MOV("%s", "%llu"), values->name, values->value.val64);
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
            instrucciones = format_intrucion(ASM_INTERRUPCION_SYSCALL()"\n");
            break;
        case 32:
            instrucciones = format_intrucion(ASM_INTERRUPCION("0x%x")"\n", 0x80);
            break;
        case 16:
            instrucciones = format_intrucion(ASM_INTERRUPCION("0x%x")"\n", 0x10);
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
        case AST_INIT:
            puts("Nodo de inicio");
            break;
        case AST_COMPOUND:
            printf("Compound(%s)\n", node->name);
            break;
        case AST_SYSCALL:
            asm_syscall(node, list, is_last);
            break;
        // Agrega más casos según sea necesario para otros tipos de nodos
        default:
            printf("Unknown Node Type\n");
    }


    // Recorrer los hijos del nodo recursivamente
    for (size_t i = 0; i < node->children->size; i++) {
        get_list_assembly(node->children->items[i], list, (i == node->children->size - 1));
    }
    return list;
}

list_c* convert_assembly(ast_t* ast){
    // lista donde se almacenara instrucciones asm
    list_c* list = (list_c*)init_list(sizeof(unsigned char*));



    return get_list_assembly(ast, list, 1);
}   

#endif