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

#endif