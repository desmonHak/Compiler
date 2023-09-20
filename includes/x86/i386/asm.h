#ifndef _X86_I386_ASM_
#define _X86_I386_ASM_

#include <stdint.h>


/*
 *		                    Descripción	(16-31)
 * Bit# Abreviatura         EFLAGS (Banderas)                           Categoría
 * 16	    RF	        Bandera de resumen (Solo 386+)	Sistema
 * 17	    VM	        Bandera de modo Virtual 8086 (Solo 386+)	    Sistema
 * 18	    AC	        Control de alineación (Solo 486SX+ )	        Sistema
 * 19	    VIF	        Bandera de interrupción virtual (Pentium+)	    Sistema
 * 20	    VIP	        Interrupción virtual pendiente (Pentium+)	    Sistema
 * 21	    ID	        Capaz de utilizar instrucción CPUID (Pentium+)	Sistema
 * 22		            Reservado	
 * 23		            Reservado	
 * 24		            Reservado	
 * 25		            Reservado	
 * 26		            Reservado	
 * 27		            Reservado	
 * 28		            Reservado	
 * 29		            Reservado	
 * 30		            Reservado	
 * 31		 Ai         Juego de instrucciones alternativo habilitado	Sistema
 *                          (sólo procesadores VIA C5XL)
 */
#define RF   (1 << 16)
#define VM   (1 << 17)
#define AC   (1 << 18)
#define VIF  (1 << 19)
#define VIP  (1 << 20)
#define ID   (1 << 21)
#define AI   (1 << 31)

/**
 * A 32-bit general register.
 *
 * This type encapsulates a 32-bit register such as %eax, %ebx, %ecx,
 * %edx, %esi, %edi, %ebp or %esp.
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
    uint32_t dword;
} __attribute__((packed)) reg32_t;

struct regs_i386
{
    union
    {
        uint16_t di;
        uint32_t edi;
    };
    union
    {
        uint16_t si;
        uint32_t esi;
    };
    union
    {
        uint16_t bp;
        uint32_t ebp;
    };
    union
    {
        uint16_t sp;
        uint32_t esp;
    };
    union
    {
        struct
        {
            uint8_t bl;
            uint8_t bh;
        } __attribute__((packed));
        uint16_t bx;
        uint32_t ebx;
    };
    union
    {
        struct
        {
            uint8_t dl;
            uint8_t dh;
        } __attribute__((packed));
        uint16_t dx;
        uint32_t edx;
    };
    union
    {
        struct
        {
            uint8_t cl;
            uint8_t ch;
        } __attribute__((packed));
        uint16_t cx;
        uint32_t ecx;
    };
    union
    {
        struct
        {
            uint8_t al;
            uint8_t ah;
        } __attribute__((packed));
        uint16_t ax;
        uint32_t eax;
    };
} __attribute__((packed));

struct regs_i386_seg
{
    uint16_t cs; /* segmento de rax, eax, ax, ah, al*/ // code (8086)
    uint16_t ss; /* segmento de rbx, ebx, bx, bh, bl*/ // stack(8086)
    uint16_t ds; /* segmento de rcx, ecx, cx, ch, cl*/ // data (8086)
    uint16_t es; /* segmento de rdx, edx, dx, dh, dl*/ // extra(8086)
    uint16_t fs; /* segmento de rsp, esp, sp, ch, cl*/ // solo apartir del 80386
    uint16_t gs; /* segmento de rsi, esi, si, ch, cl*/ // solo apartir del 80386
} __attribute__((packed));


struct regs_i386_all
{
    struct regs_i386_seg segs;
    struct regs_i386 regs;
    uint32_t flags;
} __attribute__((packed));

#endif