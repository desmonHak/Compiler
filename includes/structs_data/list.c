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
#ifndef _LIST_C_
#define _LIST_C_
#include "list.h"

list_c* init_list(size_t item_size){
    list_c *list = (list_c*)calloc(1, sizeof(list_c));
    list->size = 0;
    list->itme_size = item_size;
    list->items = NULL;

    return list;
}

void list_push(list_c* list, void* item){
    list->size++;
    /*
    if (list->items) list->items = (void**)calloc(1, list->itme_size);
    else list->items = (void**)realloc(list->items, (list->size * list->itme_size));
    list->items[list->size - 1] = item;
    */
    if (list->items) {
        list->items = (void**)realloc(list->items, (list->size * sizeof(void*)));  // Allocate space for all items
    } else {
        list->items = (void**)malloc(sizeof(void*));  // Allocate space for the first item
    }
    
    if (list->items) {
        list->items[list->size - 1] = item;  // Add the item to the list
    } else {
        printf("error\n");
        exit(1);
    }
}

void* free_list(list_c* item_size){
    free(item_size);
    return NULL;
}

#endif