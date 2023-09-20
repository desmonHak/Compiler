#ifndef _STRING_C_
#define _STRING_C_
#include "strings.h"

uint64_t getSize(String_c* my_string){
    return my_string->size;
}

unsigned char* setStr(String_c *my_string, const unsigned char* string_c, uint64_t size_copy){
    /*
     *
     *  my_string -> objeto de tipo String_c
     *  string_c -> cadena de caracteres a copiar.
     *  size_copy -> cantidad de bytes a copiar de la cadena, 
     *      0 indica que se busca hasta encontrar un \0 al final de la cadena
     * 
     */
    if (!size_copy){
        // si fue 0, obtener el tamaño de la cadena de origen mediante ell idicador fina("\0")
        size_copy = strlen(string_c);
    }
    if (size_copy > my_string->size && my_string->str != NULL){
        // si size_copy es mayor que my_string->size liberar el antiguo espacio
        // y reservar mas.
        free(my_string->str);
        my_string->str = NULL;
    }
    if (my_string->str == NULL){
        // si nunca se llamo a malloc(o se libero el espacio anteriomente), reservar un 
        // nuevo espacio del tamaño de size_copy
        my_string->str = (unsigned char *)malloc(sizeof(unsigned char) * size_copy); 
        my_string->size = size_copy;
    }
    memcpy(my_string->str, string_c, my_string->size);
    return my_string->str;
}

unsigned char* getStr(String_c *my_string){
    return my_string->str;
}

void printStr(String_c *my_string, const char *format, ...){
    va_list args;
    va_start(args, format);
    // imprimir la cadena sin basarse en su terminacion nula
    for (uint64_t chartter = 0; chartter < my_string->getSize(my_string); chartter++) putchar(my_string->str[chartter]);
    vprintf_color(format, args);
    va_end(args);
}

uint64_t _searchCharNotStr(const char *str_c, uint64_t initPosition, uint64_t maxPosition, unsigned char chartter){
    /*
     *  
     *  Buscar en una cadena de caracteres(str_c) desde la posicio(initPosition) el caracter(chartter)
     *  hasta la posicion(maxtPosition)
     * 
     */
    // inicial en la cadena de caracteres desde la posicion initPosition
    const char *stratPosition = str_c + (initPosition * sizeof(const char) ) ;
    // si se encuentra el caracter, restar la direccion de memoria donde se encuentra el caracter, con la direccion inicial de la cadena de caracteres
    // (calcular offset)
    for (; stratPosition < str_c + maxPosition; stratPosition+=sizeof(const char)) if (*stratPosition == chartter) return stratPosition - str_c;
    return 0;
}

uint64_t searchChar(String_c *my_string, unsigned char chartter){
    /*
     *
     *  Busca la posicion especifica de un caracter especificado(chartter)
     *  Dentro del string
     * 
     */
    // buscar la posicion y retornarla:
    //for (uint64_t position = 0; position < my_string->getSize(my_string); position++) if (my_string->str[position] == chartter) return position;
    // si el caracter no se pudo encontrar dentro del String retornar 0.
    //return 0;
    return _searchCharNotStr(my_string->getStr(my_string), 0, my_string->getSize(my_string), chartter);
}

#define NewObject_String_c(NameObject) NewObjet(String_c, NameObject); NameObject.exec(&NameObject)
void ConstructorClass(String_c)(String_c *my_string){
    // atributos:
    my_string->size = 0;
    my_string->str = NULL;
    // metodoso de clase:
    my_string->exec = ConstructorClass(String_c);
    my_string->getSize = getSize;
    my_string->setStr = setStr;
    my_string->getStr = getStr;
    my_string->printStr = printStr;
    my_string->searchChar = searchChar;
}

#endif