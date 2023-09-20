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