#ifndef _X86_8086_ASM_
#define _X86_8086_ASM_

#include <stdint.h>


/*
 *		                    Descripción	(0-15)
 * Bit# Abreviatura         FLAGS (Banderas)                       Categoría
 * 0	    CF	        Bandera de acarreo	                          Estado
 * 1		            Reservado, siempre 1 en EFLAGS2​	
 * 2	    PF  	    Bandera de paridad	                          Estado
 * 3		            Reservado	
 * 4	    AF	        Bandera de ajuste	                          Estado
 * 5		            Reservado	
 * 6	    ZF	        Bandera de cero	                              Estado
 * 7	    SF	        Bandera de signo	                          Estado
 * 8	    TF	        Bandera de trampa (paso único)	              Control
 * 9	    IF	        Bandera de interrupción habilitada	          Control
 * 10	    DF	        Bandera de dirección	                      Control
 * 11	    OF	        Bandera de desbordamiento	                  Estado
 * 
 * 12-13	IOPL	    Nivel de privilegio de E/S (Solo 286+), 
 *                         siempre 1 encima 8086 y 186	              Sistema
 * 
 * 14	    NT	        Bandera de tarea anidada (Solo 286+), 
 *                         siempre 1 en 8086 y 186	                  Sistema
 * 
 * 15		            Reservado, siempre 1 en 8086 y 186, 
 *                         siempre 0 en modelos más recientes.	
 */

/* Flags */
#define CF           (1 << 0)
#define RESERBADO1   (1 << 1)
#define PF           (1 << 2)
#define RESERBADO2   (1 << 3)
#define AF           (1 << 4)
#define RESERBADO3   (1 << 5)
#define ZF           (1 << 6)
#define SF           (1 << 7)
#define TF           (1 << 8)
#define IF           (1 << 9)
#define DF           (1 << 10)
#define OF           (1 << 11)
#define IOPL1        (1 << 12)
#define IOPL2        (1 << 13)
#define NT           (1 << 14)
#define RESERBADO4   (1 << 15)

/**
 * A 16-bit general register.
 *
 * This type encapsulates a 16-bit register such as %ax, %bx, %cx,
 * %dx, %si, %di, %bp or %sp.
 *
 */
typedef union
{
    struct
    {
        union
        {
            uint8_t l;
            uint8_t byte;
        };
        uint8_t h;
    } __attribute__((packed));
    uint16_t word;
} __attribute__((packed)) reg16_t;

struct regs_8086
{
    union
    {
        uint16_t di;
    };
    union
    {
        uint16_t si;
    };
    union
    {
        uint16_t bp;
    };
    union
    {
        uint16_t sp;
    };
    union
    {
        struct
        {
            uint8_t bl;
            uint8_t bh;
        } __attribute__((packed));
        uint16_t bx;
    };
    union
    {
        struct
        {
            uint8_t dl;
            uint8_t dh;
        } __attribute__((packed));
        uint16_t dx;
    };
    union
    {
        struct
        {
            uint8_t cl;
            uint8_t ch;
        } __attribute__((packed));
        uint16_t cx;
    };
    union
    {
        struct
        {
            uint8_t al;
            uint8_t ah;
        } __attribute__((packed));
        uint16_t ax;
    };
} __attribute__((packed));

struct regs_8086_seg
{
    uint16_t cs; /* segmento de rax, eax, ax, ah, al*/ // code (8086)
    uint16_t ss; /* segmento de rbx, ebx, bx, bh, bl*/ // stack(8086)
    uint16_t ds; /* segmento de rcx, ecx, cx, ch, cl*/ // data (8086)
    uint16_t es; /* segmento de rdx, edx, dx, dh, dl*/ // extra(8086)
    //uint16_t fs; /* segmento de rsp, esp, sp, ch, cl*/ // solo apartir del 80386
    //uint16_t gs; /* segmento de rsi, esi, si, ch, cl*/ // solo apartir del 80386
} __attribute__((packed));

struct regs_8086_all
{
    struct regs_8086_seg segs;
    struct regs_8086 regs;
    uint64_t flags;
} __attribute__((packed));

#endif