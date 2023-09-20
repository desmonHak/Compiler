#ifndef _STRING_H_
#define _STRING_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../class_c.h"

typedef class_c String_c {
    // metodos:
    CreateMethod(void, exec, class_c String_c*); // constructor = void ConstructorClass(String_c)(String_c *my_string)
    CreateMethod(uint64_t, getSize, class_c String_c*); // uint64_t getSize(string_c* my_string)
    CreateMethod(unsigned char*, setStr, class_c String_c*, const unsigned char*, uint64_t); // unsigned char* setStr(String_c *my_string, const unsigned char* string_c, uint64_t size_copy)
    CreateMethod(unsigned char*, getStr, class_c String_c*); // unsigned char* getStr(String_c *my_string)
    CreateMethod(void, printStr, class_c String_c*, const char *, ...); // void printStr(String_c *my_string, const char *format, ...)
    CreateMethod(uint64_t, searchChar, class_c String_c*, unsigned char); // uint64_t searchChar(String_c *my_string, unsigned char chartter)
    // atributos:
    CreateAtribute(unsigned char*, str);
    CreateAtribute(uint64_t, size);
} String_c;

uint64_t getSize(String_c* my_string);

#include "strings.c"
#endif