#include <stdint.h>

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

struct i386_regs
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

struct amd64_regs
{
    union
    {
        uint16_t di;
        uint32_t edi;
        uint64_t rdi
    };
    union
    {
        uint16_t si;
        uint32_t esi;
        uint64_t rsi
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

struct i386_seg_regs
{
    uint16_t cs;
    uint16_t ss;
    uint16_t ds;
    uint16_t es;
    uint16_t fs;
    uint16_t gs;
} __attribute__((packed));

struct i386_all_regs
{
    struct i386_seg_regs segs;
    struct i386_regs regs;
    uint32_t flags;
} __attribute__((packed));

struct amd64_all_regs {
    struct i386_seg_regs segs;
    struct amd64_regs regs;
    uint64_t flags;
} __attribute__((packed));

/* Flags */
#define CF   (1 << 0)
#define PF   (1 << 2)
#define AF   (1 << 4)
#define ZF   (1 << 6)
#define SF   (1 << 7)
#define OF   (1 << 11)

#define IOPL (1 << 13)
#define NT   (1 << 14)
#define RF   (1 << 16)
#define VM   (1 << 17)
#define AC   (1 << 18)
#define VIF  (1 << 19)
#define VIP  (1 << 20)
#define ID   (1 << 21)
/* Segment:offset structure.  Note that the order within the structure
 * is offset:segment.
 */
struct segoff
{
    uint16_t offset;
    uint16_t segment;
} __attribute__((packed));

typedef struct segoff segoff_t;