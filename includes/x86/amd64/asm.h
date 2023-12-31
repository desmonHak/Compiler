/*
 *	Licencia Apache, Versión 2.0 con Modificación
 *	
 *	Copyright 2023 Desmon (David)
 *	
 *	Se concede permiso, de forma gratuita, a cualquier persona que obtenga una copia de 
 *	este software y archivos de documentación asociados (el "Software"), para tratar el 
 *	Software sin restricciones, incluidos, entre otros, los derechos de uso, copia, 
 *	modificación, fusión, publicación, distribución, sublicencia y/o venta de copias del 
 *	Software, y para permitir a las personas a quienes se les proporcione el Software 
 *	hacer lo mismo, sujeto a las siguientes condiciones:
 *	
 *	El anterior aviso de copyright y este aviso de permiso se incluirán en todas las 
 *	copias o partes sustanciales del Software.
 *	
 *	EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O 
 *	IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD 
 *	PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN. EN NINGÚN CASO LOS TITULARES DEL 
 *	COPYRIGHT O LOS TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE NINGÚN 
 *	RECLAMO, DAÑO U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE 
 *	OTRA MANERA, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTRO TIPO
 *	DE ACCIONES EN EL SOFTWARE.
 *	
 *	Además, cualquier modificación realizada por terceros se considerará propiedad del 
 *	titular original de los derechos de autor. Los titulares de derechos de autor 
 *	originales no se responsabilizan de las modificaciones realizadas por terceros.
 *	
 *	Queda explícitamente establecido que no es obligatorio especificar ni notificar los 
 *	cambios realizados entre versiones, ni revelar porciones específicas de código 
 *	modificado.
 */

#ifndef _X86_AMD64_ASM_
#define _X86_AMD64_ASM_

#include <stdint.h>


/*
 *		                    Descripción	(32-63)
 * Bit# Abreviatura         RFLAGS (Banderas)                           Categoría
 * 32-63		            Reservado
 */

/**
 * A 64-bit general register.
 *
 * This type encapsulates a 64-bit register such as %rax, %rbx, %rcx,
 * %rdx, %rsi, %rdi, %rbp or %rsp.
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
    uint64_t qword;
} __attribute__((packed)) reg64_t;

struct regs_amd64
{
    union
    {
        uint16_t di;
        uint32_t edi;
        uint64_t rdi;
    };
    union
    {
        uint16_t si;
        uint32_t esi;
        uint64_t rsi;
    };
    union
    {
        uint16_t bp;
        uint32_t ebp;
        uint64_t rbp;
    };
    union
    {
        uint16_t sp;
        uint32_t esp;
        uint64_t rsp;
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
        uint64_t rbx;
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
        uint64_t rdx;
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
        uint64_t rcx;
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
        uint64_t rax;
    };
} __attribute__((packed));

struct regs_amd64_seg
{
    uint16_t cs; /* segmento de rax, eax, ax, ah, al*/ // code (8086)
    uint16_t ss; /* segmento de rbx, ebx, bx, bh, bl*/ // stack(8086)
    uint16_t ds; /* segmento de rcx, ecx, cx, ch, cl*/ // data (8086)
    uint16_t es; /* segmento de rdx, edx, dx, dh, dl*/ // extra(8086)
    uint16_t fs; /* segmento de rsp, esp, sp, ch, cl*/ // solo apartir del 80386
    uint16_t gs; /* segmento de rsi, esi, si, ch, cl*/ // solo apartir del 80386
} __attribute__((packed));


struct regs_amd64_all
{
    struct regs_amd64_seg segs;
    struct regs_amd64 regs;
    uint64_t flags;
} __attribute__((packed));

#endif