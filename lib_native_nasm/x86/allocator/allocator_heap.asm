%include "../base.asm"
%define DEBUG_ENABLE

%define authot "Desmon"
%define github "https://github.com/desmonhak"

%if __BITS__ == 32 || __BITS__ == 64
; modo largo y protegido:
;    
;    ____________________    <--- 0xxffff
;   |        Stack       |
;   |--------------------|   <--- ERBP/EBP/BP
;   |          |         |
;   |          v         |
;   |                    |
;   |                    |
;   |          ^         |
;   |          |         |
;   |--------------------|
;   |        HE AP       |
;   |--------------------|  <- __bss_end
;   |         bss        |
;   |--------------------|  <- __bss_start
;   |         data       |
;   |--------------------|
;   |         text       |
;   |--------------------|  <--- 0x0000
;

section .bss
    ; tiene que estar como primer valor de bss definido
    %ifndef __bss_start
    __bss_start resb 1
    %endif

    ; demas datos sin inicializar
    ;init_alloc resb  1

    %ifndef __bss_end
    __bss_end resb 1
    %endif

section .data
    init_bss      SIZE_T_DATA __bss_start
    end_bss       SIZE_T_DATA __bss_end
    init_alloc    SIZE_T_DATA (__bss_end + 1) 
    msg dd  __BITS__

    %ifdef DEBUG_ENABLE
    format_init_bss   db "init bss: 0x%p",   0xa, 0x0
    format_end_bss    db "end bss: 0x%p",    0xa, 0x0
    format_init_alloc db "init Alloc: 0x%p", 0xa, 0x0
    format_esp        db "value esp: 0x%p",  0xa, 0x0
    format_ebp        db "value ebp: 0x%p",  0xa, 0x0
    %endif
%endif

%if   __BITS__ == 64
%elif __BITS__ == 32
extern _printf
extern _exit
section .text
    global _WinMain@16
    _WinMain@16:
        SAVE_OLD_STACK_FRAME

        mov byte [__bss_start], 0xff
        mov byte [__bss_end],   0xff

        %ifdef DEBUG_ENABLE
        push SIZE_T_SIZE_OPERATION [init_bss]
        push format_init_bss 
        call _printf
    
        ; sumar al tope de la pila el tamaño de palabra *2
        ; de los dos push's para restaurar la pila
        add TOP_STACk, (__BITS__/8) * 2

        push SIZE_T_SIZE_OPERATION [end_bss]
        push format_end_bss 
        call _printf
        add TOP_STACk, (__BITS__/8) * 2

        push SIZE_T_SIZE_OPERATION [init_alloc]
        push format_init_alloc 
        call _printf
        add TOP_STACk, (__BITS__/8) * 2

        push TOP_STACk
        push format_esp 
        call _printf
        add TOP_STACk, (__BITS__/8) * 2
    
        push BASE_STACk
        push format_ebp 
        call _printf
        add TOP_STACk, (__BITS__/8) * 2
        %endif

        push 0
        call _exit
%elif __BITS__ == 16  
%endif

; x64 -> C Calling Convention
;   funtion(RDI, RSI, DRX, RCX, R8, R9)

    global _malloc_heap_run_time
    _malloc_heap_run_time:
        ; se guarda en DI la cantidad de memoria a reservar
        SAVE_OLD_STACK_FRAME
        mov SIZE_T_ACUMLADOR, [init_alloc]

        %if   __BITS__ == 64
        add SIZE_T_ACUMLADOR, SIZE_T_INDEICE_DESTINO
        %elif __BITS__ == 32 || __BITS__ == 16  
        add SIZE_T_ACUMLADOR, [BASE_STACk + (__BITS__/8)]
        %endif

        GET_OLD_STACK_FRAME