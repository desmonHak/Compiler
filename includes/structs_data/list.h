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

#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../debug_c.h"

#ifndef INIT_TYPE_FUNC_DBG
#define INIT_TYPE_FUNC_DBG(type_return, name_func) "#{FG:lred} "#type_return" #{FG:cyan}"#name_func"#{FG:white}("
#define TYPE_DATA_DBG(type_data, name_arg) " #{FG:lyellow}"#type_data" #{FG:white} "name_arg", "
#define END_TYPE_FUNC_DBG "#{FG:white}); #{FG:reset}"
#endif

typedef struct LIST_STRUCT {
    void** items;
    size_t size;
    size_t itme_size;
} list_c;

void *list_pop(list_c *list);
void list_resize(list_c *list);
size_t list_get_size(list_c *list);
list_c *init_list(size_t item_size);
void list_push(list_c *list, void *item);
void *list_get_last_element(list_c *list);
void list_set_size(list_c *list, size_t size);
void *list_get_element(list_c *list, size_t position);
void *list_delete_element(list_c *list, size_t position);

#include "list.c"
#endif