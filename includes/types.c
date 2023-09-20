#ifndef _TYPES_C_
#define _TYPES_C_
#include "types.h"

unsigned int  typename_to_int(const char* name){
    unsigned int j = 0;
    size_t len = strlen(name);

    for (unsigned int i = 0; i < len; i++){
        j += name[i];
    }

    return j;
}

#endif