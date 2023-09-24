#ifndef _MD4_C
#define _MD4_C 1
#include "md4.h"

// https://www.rfc-editor.org/rfc/rfc1320

/*
 *  El hash generado por esta implementación es de tamaño 128 bits, 
 *  es decir, 16 bytes. Esto se puede determinar al observar que el 
 *  hash se almacena como un arreglo de ui8 de longitud 16 en la 
 *  función MD4. Además, la función base16Encode convierte el hash 
 *  a una cadena hexadecimal de longitud 32, lo que sugiere que el hash tiene una longitud de 128 bits (16 * 8 = 128).
*/

string newString(ui8 *c, _uint32_t t)
{
    string r;
    _uint32_t i;
    if (c != null)
    {
        r.len._uint32_t = (t._uint32_t <= 0) ? strlen((const char*)c) : t._uint32_t;
        r.c = (ui8 *)malloc(sizeof(ui8) * (r.len._uint32_t + 1));
        for (i._uint32_t = 0; i._uint32_t < r.len._uint32_t; i._uint32_t++)
            r.c[i._uint32_t] = c[i._uint32_t];
        r.c[r.len._uint32_t] = '\0';
        return r;
    }
    r.len._uint32_t = t._uint32_t;
    r.c = (ui8 *)malloc(sizeof(ui8) * (r.len._uint32_t + 1));
    memset(r.c, (ui8)0, sizeof(ui8) * (t._uint32_t + 1));
    r.sign._uint8_t = 1;
    return r;
}

string stringCat(string first, string second)
{
    string str = newString(NULL, (_uint32_t){first.len._uint32_t + second.len._uint32_t});
    _uint32_t i;

    for (i._uint32_t = 0; i._uint32_t < first.len._uint32_t; i._uint32_t++)
    {
        str.c[i._uint32_t] = first.c[i._uint32_t];
    }
    for (i._uint32_t = first.len._uint32_t; i._uint32_t < str.len._uint32_t; i._uint32_t++)
    {
        str.c[i._uint32_t] = second.c[i._uint32_t - first.len._uint32_t];
    }
    return str;
}

string base16Encode(string in)
{
    string out = newString(NULL, (_uint32_t){in.len._uint32_t * 2});
    _uint32_t i, j;

    j._uint32_t = 0;
    for (i._uint32_t = 0; i._uint32_t < in.len._uint32_t; i._uint32_t++)
    {
        out.c[j._uint32_t++] = BASE16[((in.c[i._uint32_t] & 0xF0) >> 4)];
        out.c[j._uint32_t++] = BASE16[(in.c[i._uint32_t] & 0x0F)];
    }
    out.c[j._uint32_t] = '\0';
    return out;
}

string uint32ToString(_uint32_t l)
{
    string s = newString(NULL, (_uint32_t){4});
    _uint32_t i;
    for (i._uint32_t = 0; i._uint32_t < 4; i._uint32_t++)
    {
        s.c[i._uint32_t] = (l._uint32_t >> (8 * (3 - i._uint32_t))) & 0xFF;
    }
    return s;
}

_uint32_t stringToUint32(string s)
{
    _uint32_t l = (_uint32_t){0}, i = (_uint32_t){0};
    for (; i._uint32_t < 4; i._uint32_t++)
    {
        l._uint32_t = l._uint32_t | (((ui32)((ui8)s.c[i._uint32_t])) << (8 * (3 - i._uint32_t)));
    }
    return l;
}

ui8 *MD4(ui8 *str, _uint32_t len)
{
    string m = newString(str, len), digest;
    ui32 *w, *hash;
    _uint64_t mlen = (_uint64_t){m.len._uint32_t};
    _uint8_t oneBit = (_uint8_t ){0x80};
    _uint32_t i, wlen;

    m = stringCat(m, newString((ui8 *)&oneBit, (_uint32_t){1}));

    // append 0 ≤ k < 512 bits '0', such that the resulting message length in bits
    //	is congruent to −64 ≡ 448 (mod 512)4
    i._uint32_t = ((56 - m.len._uint32_t) % 64);
    if (i._uint32_t < 0) i._uint32_t += 64;
    m = stringCat(m, newString(NULL, i));

    w = malloc(sizeof(ui32) * (m.len._uint32_t / 4 + 2));

    // append length, in bits (hence <<3), least significant word first
    for (i._uint32_t = 0; i._uint32_t < m.len._uint32_t / 4; i._uint32_t++)
    {
        w[i._uint32_t] = stringToUint32(newString(&(m.c[4 * i._uint32_t]), (_uint32_t){4}))._uint32_t;
    }
    w[i._uint32_t++] = (mlen._uint64_t << 3) & 0xFFFFFFFF;
    w[i._uint32_t++] = (mlen._uint64_t >> 29) & 0xFFFFFFFF;

    wlen._uint32_t = i._uint32_t;

    // change endianness, but not for the appended message length, for some reason?
    for (i._uint32_t = 0; i._uint32_t < wlen._uint32_t - 2; i._uint32_t++)
    {
        w[i._uint32_t] = changeEndianness((_uint32_t){w[i._uint32_t]})._uint32_t  ;
    }

    hash = MD4Digest(w, wlen);

    digest = newString(NULL, (_uint32_t){0});
    for (i._uint32_t = 0; i._uint32_t < 4; i._uint32_t++)
    {
        hash[i._uint32_t] = changeEndianness((_uint32_t){hash[i._uint32_t]})._uint32_t;
        digest = stringCat(digest, uint32ToString((_uint32_t){hash[i._uint32_t]}));
    }

    return base16Encode(digest).c;
}

ui32 *MD4Digest(ui32*w, _uint32_t len)
{
    // assumes message.len is a multiple of 64 bytes.
    _uint32_t i = (_uint32_t){0}, j;
    _uint32_t X[16];
    ui32 *digest = malloc(sizeof(_uint32_t) * 4);
    _uint32_t AA, BB, CC, DD;

    for (; i._uint32_t < len._uint32_t / 16; i._uint32_t++)
    {
        for (j._uint32_t = 0; j._uint32_t < 16; j._uint32_t++)
        {
            X[j._uint32_t]._uint32_t = w[i._uint32_t * 16 + j._uint32_t];
        }

        AA = A;
        BB = B;
        CC = C;
        DD = D;

        MD4ROUND1(A._uint32_t, B._uint32_t, C._uint32_t, D._uint32_t, X[0] ._uint32_t, 3);
        MD4ROUND1(D._uint32_t, A._uint32_t, B._uint32_t, C._uint32_t, X[1] ._uint32_t, 7);
        MD4ROUND1(C._uint32_t, D._uint32_t, A._uint32_t, B._uint32_t, X[2] ._uint32_t, 11);
        MD4ROUND1(B._uint32_t, C._uint32_t, D._uint32_t, A._uint32_t, X[3] ._uint32_t, 19);
        MD4ROUND1(A._uint32_t, B._uint32_t, C._uint32_t, D._uint32_t, X[4] ._uint32_t, 3);
        MD4ROUND1(D._uint32_t, A._uint32_t, B._uint32_t, C._uint32_t, X[5] ._uint32_t, 7);
        MD4ROUND1(C._uint32_t, D._uint32_t, A._uint32_t, B._uint32_t, X[6] ._uint32_t, 11);
        MD4ROUND1(B._uint32_t, C._uint32_t, D._uint32_t, A._uint32_t, X[7] ._uint32_t, 19);
        MD4ROUND1(A._uint32_t, B._uint32_t, C._uint32_t, D._uint32_t, X[8] ._uint32_t, 3);
        MD4ROUND1(D._uint32_t, A._uint32_t, B._uint32_t, C._uint32_t, X[9] ._uint32_t, 7);
        MD4ROUND1(C._uint32_t, D._uint32_t, A._uint32_t, B._uint32_t, X[10]._uint32_t, 11);
        MD4ROUND1(B._uint32_t, C._uint32_t, D._uint32_t, A._uint32_t, X[11]._uint32_t, 19);
        MD4ROUND1(A._uint32_t, B._uint32_t, C._uint32_t, D._uint32_t, X[12]._uint32_t, 3);
        MD4ROUND1(D._uint32_t, A._uint32_t, B._uint32_t, C._uint32_t, X[13]._uint32_t, 7);
        MD4ROUND1(C._uint32_t, D._uint32_t, A._uint32_t, B._uint32_t, X[14]._uint32_t, 11);
        MD4ROUND1(B._uint32_t, C._uint32_t, D._uint32_t, A._uint32_t, X[15]._uint32_t, 19);

        MD4ROUND2(A._uint32_t, B._uint32_t, C._uint32_t, D._uint32_t, X[0] ._uint32_t, 3);
        MD4ROUND2(D._uint32_t, A._uint32_t, B._uint32_t, C._uint32_t, X[4] ._uint32_t, 5);
        MD4ROUND2(C._uint32_t, D._uint32_t, A._uint32_t, B._uint32_t, X[8] ._uint32_t, 9);
        MD4ROUND2(B._uint32_t, C._uint32_t, D._uint32_t, A._uint32_t, X[12]._uint32_t, 13);
        MD4ROUND2(A._uint32_t, B._uint32_t, C._uint32_t, D._uint32_t, X[1] ._uint32_t, 3);
        MD4ROUND2(D._uint32_t, A._uint32_t, B._uint32_t, C._uint32_t, X[5] ._uint32_t, 5);
        MD4ROUND2(C._uint32_t, D._uint32_t, A._uint32_t, B._uint32_t, X[9] ._uint32_t, 9);
        MD4ROUND2(B._uint32_t, C._uint32_t, D._uint32_t, A._uint32_t, X[13]._uint32_t, 13);
        MD4ROUND2(A._uint32_t, B._uint32_t, C._uint32_t, D._uint32_t, X[2] ._uint32_t, 3);
        MD4ROUND2(D._uint32_t, A._uint32_t, B._uint32_t, C._uint32_t, X[6] ._uint32_t, 5);
        MD4ROUND2(C._uint32_t, D._uint32_t, A._uint32_t, B._uint32_t, X[10]._uint32_t, 9);
        MD4ROUND2(B._uint32_t, C._uint32_t, D._uint32_t, A._uint32_t, X[14]._uint32_t, 13);
        MD4ROUND2(A._uint32_t, B._uint32_t, C._uint32_t, D._uint32_t, X[3] ._uint32_t, 3);
        MD4ROUND2(D._uint32_t, A._uint32_t, B._uint32_t, C._uint32_t, X[7] ._uint32_t, 5);
        MD4ROUND2(C._uint32_t, D._uint32_t, A._uint32_t, B._uint32_t, X[11]._uint32_t, 9);
        MD4ROUND2(B._uint32_t, C._uint32_t, D._uint32_t, A._uint32_t, X[15]._uint32_t, 13);

        MD4ROUND3(A._uint32_t, B._uint32_t, C._uint32_t, D._uint32_t, X[0] ._uint32_t, 3);
        MD4ROUND3(D._uint32_t, A._uint32_t, B._uint32_t, C._uint32_t, X[8] ._uint32_t, 9);
        MD4ROUND3(C._uint32_t, D._uint32_t, A._uint32_t, B._uint32_t, X[4] ._uint32_t, 11);
        MD4ROUND3(B._uint32_t, C._uint32_t, D._uint32_t, A._uint32_t, X[12]._uint32_t, 15);
        MD4ROUND3(A._uint32_t, B._uint32_t, C._uint32_t, D._uint32_t, X[2] ._uint32_t, 3);
        MD4ROUND3(D._uint32_t, A._uint32_t, B._uint32_t, C._uint32_t, X[10]._uint32_t, 9);
        MD4ROUND3(C._uint32_t, D._uint32_t, A._uint32_t, B._uint32_t, X[6] ._uint32_t, 11);
        MD4ROUND3(B._uint32_t, C._uint32_t, D._uint32_t, A._uint32_t, X[14]._uint32_t, 15);
        MD4ROUND3(A._uint32_t, B._uint32_t, C._uint32_t, D._uint32_t, X[1] ._uint32_t, 3);
        MD4ROUND3(D._uint32_t, A._uint32_t, B._uint32_t, C._uint32_t, X[9] ._uint32_t, 9);
        MD4ROUND3(C._uint32_t, D._uint32_t, A._uint32_t, B._uint32_t, X[5] ._uint32_t, 11);
        MD4ROUND3(B._uint32_t, C._uint32_t, D._uint32_t, A._uint32_t, X[13]._uint32_t, 15);
        MD4ROUND3(A._uint32_t, B._uint32_t, C._uint32_t, D._uint32_t, X[3] ._uint32_t, 3);
        MD4ROUND3(D._uint32_t, A._uint32_t, B._uint32_t, C._uint32_t, X[11]._uint32_t, 9);
        MD4ROUND3(C._uint32_t, D._uint32_t, A._uint32_t, B._uint32_t, X[7] ._uint32_t, 11);
        MD4ROUND3(B._uint32_t, C._uint32_t, D._uint32_t, A._uint32_t, X[15]._uint32_t, 15);

        A._uint32_t += AA._uint32_t;
        B._uint32_t += BB._uint32_t;
        C._uint32_t += CC._uint32_t;
        D._uint32_t += DD._uint32_t;
    }

    digest[0] = A._uint32_t;
    digest[1] = B._uint32_t;
    digest[2] = C._uint32_t;
    digest[3] = D._uint32_t;
    resetMD4Registers();
    return digest;
}

_uint32_t changeEndianness(_uint32_t x)
{
    return (_uint32_t){((x._uint32_t & 0xFF) << 24) | ((x._uint32_t & 0xFF00) << 8) | ((x._uint32_t & 0xFF0000) >> 8) | ((x._uint32_t & 0xFF000000) >> 24)};
}

void setMD4Registers(_uint32_t AA, _uint32_t BB, _uint32_t CC, _uint32_t DD)
{
    A = AA;
    B = BB;
    C = CC;
    D = DD;
}

void resetMD4Registers(void)
{
    setMD4Registers((_uint32_t){0x67452301}, (_uint32_t){0xefcdab89}, (_uint32_t){0x98badcfe}, (_uint32_t){0x10325476});
}
#endif