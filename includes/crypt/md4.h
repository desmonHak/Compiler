#ifndef _MD4_H
#define _MD4_H	1

#include <stdlib.h>
#include <string.h>
#include "type_data_c.h"

static const char *BASE16 = "0123456789abcdef=";

#define F(X,Y,Z) (((X)&(Y))|((~(X))&(Z)))
#define G(X,Y,Z) (((X)&(Y))|((X)&(Z))|((Y)&(Z)))
#define H(X,Y,Z) ((X)^(Y)^(Z))

#ifndef LEFTROTATE
#define LEFTROTATE(A,N) ((A)<<(N))|((A)>>(32-(N)))
#endif

#define MD4ROUND1(a,b,c,d,x,s) a += F(b,c,d) + x; a = LEFTROTATE(a, s);
#define MD4ROUND2(a,b,c,d,x,s) a += G(b,c,d) + x + (ui32)0x5A827999; a = LEFTROTATE(a, s);
#define MD4ROUND3(a,b,c,d,x,s) a += H(b,c,d) + x + (ui32)0x6ED9EBA1; a = LEFTROTATE(a, s);


typedef struct string{
        ui8 *c;
        _uint32_t len;
        _uint8_t sign;
} string;

static ui32 *MD4Digest(ui32*w, _uint32_t len);
static void setMD4Registers(_uint32_t AA, _uint32_t BB, _uint32_t CC, _uint32_t DD);
static _uint32_t changeEndianness(_uint32_t x);
static void resetMD4Registers(void);
static string stringCat(string first, string second);
static string uint32ToString(_uint32_t l);
static _uint32_t stringToUint32(string s);
ui8 *MD4(ui8*str, _uint32_t len); //this is the prototype you want to call. Everything else is internal.

static _uint32_t A = (_uint32_t){0x67452301};
static _uint32_t B = (_uint32_t){0xefcdab89};
static _uint32_t C = (_uint32_t){0x98badcfe};
static _uint32_t D = (_uint32_t){0x10325476};

#include "md4.c"
#endif