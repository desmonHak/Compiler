#ifndef _X86_AMD64_INSTRUCTIONS_H_ 
#define _X86_AMD64_INSTRUCTIONS_H_ 64

static char* string_ID_regs_amd64[] = {
    "rax","rbx","rcx",
    "rdx","rsi","rsi",
    "rsp","rbp",

    "eax","ebx","ecx",
    "edx","esi","esi",
    "esp","ebp",

    "ax","bx","cx",
    "dx","si","si",
    "sp","bp",

    "al", "ah", "bl", "bh",
    "cl", "ch", "dl", "dh",
};

#define SYSCALL_AMD64() 

#endif