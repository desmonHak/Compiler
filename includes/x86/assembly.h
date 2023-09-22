
#ifndef _X86_ASSEMBLY_
#define _X86_ASSEMBLY_

#include "8086/asm.h"
#include "8086/instructions.h"

#include "i386/asm.h"
#include "i386/instructions.h"

#include "amd64/asm.h"
#include "amd64/instructions.h"

/* Segment:offset structure.  Note that the order within the structure
 * is offset:segment.
 */
struct segoff
{
    uint16_t offset;
    uint16_t segment;
} __attribute__((packed));
typedef struct segoff segoff_t;


#endif