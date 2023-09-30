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

list_c *init_list(size_t item_size)
{
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(list_c *, init_list) \
		TYPE_DATA_DBG(size_t, "item_size = %zu") \
		END_TYPE_FUNC_DBG, item_size \
	);
    #endif
    list_c *list;
    debug_calloc(list_c, list, 1, sizeof(list_c));
    //list_c *list = (list_c *)calloc(1, sizeof(list_c));
    list->size = 0;              // cantidad de elementos en la lista
    list->itme_size = item_size; // tamaño de cada elemento en la lista
    list->items = NULL;          // puntero a unalista de punteros

    return list;
}

void list_resize(list_c *list)
{
    /*
     *
     *  redimensiona la lista
     *
     */
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void, list_resize) \
		TYPE_DATA_DBG(list_c *, "list = %p") \
		END_TYPE_FUNC_DBG, list \
	);
    #endif

    // si items es nulo se reserva memoria
    if (list->items == NULL) {
        debug_calloc(void*, list->items, 1, list->itme_size);
        //list->items = (void **)calloc(1, list->itme_size);
    } else {  // si items no era nulo, redimensionar la lista para agrgar el nuevo elemento
        debug_realloc(void*, list->items, (list->size * list->itme_size));
        //list->items = (void **)realloc(list->items, (list->size * list->itme_size));
    }
}

void list_push(list_c *list, void *item)
{
    /*
     *
     *  Pone un nuevo elemento al final de la lista
     *
     */
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void, list_push) \
		TYPE_DATA_DBG(list_c *, "list = %p") \
        TYPE_DATA_DBG(void *, "item = %p") \
		END_TYPE_FUNC_DBG, list, item \
	);
    #endif

    if (list->items) {
        list->items = (void**)realloc(list->items, (list->size * sizeof(void*)));  // Allocate space for all items
    } else {
        list->items = (void**)malloc(sizeof(void*));  // Allocate space for the first item
    }
    
    if (list->items) {
        list->items[list->size - 1] = item;  // Add the item to the list
    } else {
        // Handle memory allocation failure
        // You might want to add error handling here.
    }


    list->size++;                   // aumentar el tamaño de la lista en uno
    list_resize(list);              // crea la lista interna, sino la redimensiona al nuevo tamaño especifico
    list->items[list->size] = item; // asignar el nuevo elemento a la ultima posicion de la lista
}

void *list_pop(list_c *list)
{
    /*
     *
     *  Elimina el ultimo elemento de la lista y lo devuelve
     *
     */
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void*, list_pop) \
		TYPE_DATA_DBG(list_c *, "list = %p") \
		END_TYPE_FUNC_DBG, list \
	);
    #endif

    void *node = list->items[list->size];
    list->size--;      // disminuir el tamaño de la lista en uno
    list_resize(list); // crea la lista interna, sino la redimensiona al nuevo tamaño especifico
    return node;
}

void *list_get_last_element(list_c *list)
{
    /*
     *
     *  Devuelve el ultimo elemento de la lista
     *
     */
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void*, list_get_last_element) \
		TYPE_DATA_DBG(list_c *, "list = %p") \
		END_TYPE_FUNC_DBG, list \
	);
    #endif
    return list->items[list->size];
}

void list_set_size(list_c *list, size_t size)
{
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void, list_set_size) \
		TYPE_DATA_DBG(list_c *, "list = %p") \
        TYPE_DATA_DBG(void *, "size = %zu") \
		END_TYPE_FUNC_DBG, list, size \
	);
    #endif
    /*
     *
     *  Cambia el tamaño de la lista, pero no la redimensina(llamar a list_resize)
     *  para realizar la redimension.
     *
     */
    list->size = size;
}

size_t list_get_size(list_c *list)
{
    /*
     *
     *  Devuelve el tamaño de la lista
     *
     */
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(size_t, list_get_size) \
		TYPE_DATA_DBG(list_c *, "list = %p") \
		END_TYPE_FUNC_DBG, list \
	);
    #endif

    return list->size;
}

void *list_get_element(list_c *list, size_t position)
{
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void*, list_get_element) \
		TYPE_DATA_DBG(list_c *, "list = %p") \
        TYPE_DATA_DBG(size_t, "position = %zu") \
		END_TYPE_FUNC_DBG, list, position \
	);
    #endif
    /*
     *
     *  Devuelve un elemento de la lista que esta en la posicion position
     *
     */
    return list->items[position];
}

void *list_delete_element(list_c *list, size_t position)
{
    /*
     *
     *  elimina un elemento de la lista que esta en la posicion position
     *  devolviendo el elemento eliminado
     *
     */
    #ifdef DEBUG_ENABLE
	DEBUG_PRINT(DEBUG_LEVEL_INFO, \
		INIT_TYPE_FUNC_DBG(void*, list_delete_element) \
		TYPE_DATA_DBG(list_c *, "list = %p") \
        TYPE_DATA_DBG(size_t, "position = %zu") \
		END_TYPE_FUNC_DBG, list, position \
	);
    #endif
    void **new_list_temp; //= (void **)calloc(list->size, list->itme_size);
    debug_calloc(void*, new_list_temp, list->itme_size, list->itme_size);
    void *elemento = list->items[position]; // elemento a eliminar

    memcpy(new_list_temp, list->items, position); // copia los elementos hasta el elemnto a eliminar
    // copia los elementos  a continuacion del elemento eliminado:
    memcpy(new_list_temp + position, list->items + position, list->size - position);
    free(list->items); // liberar la antigua memoria
    list->items = new_list_temp;

    return elemento;
}
#endif