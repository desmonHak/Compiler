#include <stdio.h>

#define DEBUG_ENABLE

#include "list.h"

int main(){

    list_c* mi_lista = init_list(sizeof(uint64_t));

    for ( unsigned char i = 0; i < 2048; i++){
        uint64_t* number = (uint64_t*)calloc(1, sizeof(uint64_t));
        *number = i;
        printf("1> %lld %p\n", *number, number);
        list_push(mi_lista, number);
        //printf("2> %lld\n", *number);
    }

    for ( unsigned char i = 0; i < 2048; i++){
        //printf("> %lld\n", *((uint64_t*)list_get_element(mi_lista, i)));
    }

    return 0;
}