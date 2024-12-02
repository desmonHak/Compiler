#include <stdio.h>
#include "class_c.h"
#include "string_class.h"

int main() {
    NewObject_String_c(my_string);
    my_string.setStr(&my_string, "Hola mundo", 0);
    printf("mi str: ");
    my_string.printStr(&my_string, "\n");
    printf("posicion del primer espacio: %llu\n", my_string.searchChar(&my_string, ' ') );

    return 0;
}