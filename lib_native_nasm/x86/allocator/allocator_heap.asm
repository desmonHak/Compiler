%include "allocator_defines.asm"

%if __BITS__ == 32 || __BITS__ == 64


section .bss
    ; tiene que estar como primer valor de bss definido
    %ifndef __bss_start
    __bss_start resb 1
    %endif

    ; demas datos sin inicializar
    counter_alloc SIZE_T_BSS  1 ; espacio para llevar el conteo del allocator
                                ; aqui se almacena la ulima direccion de memoria asignada

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

    format_struct_size_block     db "value size_block: 0x%p",  0xa, 0x0
    format_struct_status         db "value status: 0x%hhx",  0xa, 0x0
    format_struct_pointer        db "value pointer: 0x%p",  0xa, 0x0

    format_memresever db "dirrecion de memoria inicializada: 0x%p", 0xa, 0x0
    format_counter_alloc db "new counter_alloc:  0x%p", 0xa, 0x0
    %endif
%endif

%if   __BITS__ == 64
%elif __BITS__ == 32
section .text
    global func_WinMain
    func_WinMain:
        SAVE_OLD_STACK_FRAME

        mov byte [__bss_start], 0xff
        mov byte [__bss_end],   0xff

        cmp SIZE_T_SIZE_OPERATION [counter_alloc], 0x0
        jne is_not_zero

            mov SIZE_T_BASE, init_alloc

            mov SIZE_T_DATOS, __BITS__
            dec SIZE_T_DATOS

            add SIZE_T_BASE, SIZE_T_DATOS
            not SIZE_T_DATOS
            and SIZE_T_BASE, SIZE_T_DATOS

            mov SIZE_T_SIZE_OPERATION [init_alloc], SIZE_T_BASE

        is_not_zero: ; si fue 0 (init alloc no se alineo)


        %ifdef DEBUG_ENABLE
        push SIZE_T_SIZE_OPERATION [init_bss]
        push format_init_bss 
        call func_printf
    
        ; sumar al tope de la pila el tamaño de palabra *2
        ; de los dos push's para restaurar la pila
        add TOP_STACk, (__BITS__/8) * 2

        push SIZE_T_SIZE_OPERATION [end_bss]
        push format_end_bss 
        call func_printf
        add TOP_STACk, (__BITS__/8) * 2

        push SIZE_T_SIZE_OPERATION [init_alloc]
        push format_init_alloc 
        call func_printf
        add TOP_STACk, (__BITS__/8) * 2

        push TOP_STACk
        push format_esp 
        call func_printf
        add TOP_STACk, (__BITS__/8) * 2
    
        push BASE_STACk
        push format_ebp 
        call func_printf
        add TOP_STACk, (__BITS__/8) * 2
        %endif

        push 5                                  ; memoria a reservar
        push SIZE_T_SIZE_OPERATION [init_alloc] ; direccion base a usar
        call _alloc_heap_run_time
        push SIZE_T_ACUMLADOR
        push format_memresever 
        call func_printf
        add TOP_STACk, (__BITS__/8) * 2


        sub esp, 2 * Header_block_heap
        ; Accede a las estructuras a través de ESP

        mov SIZE_T_BASE, [esp + (Header_block_heap * 0)]                         
        set_size_block(SIZE_T_BASE, 0xfb)    
        set_pointer(SIZE_T_BASE, 0xfa)
        set_status(SIZE_T_BASE, 0xfc)
        call _print_debug_alloc

        mov SIZE_T_BASE, [esp + (Header_block_heap * 1)] ; Accede a la segunda estructura
        create_struct_Header_block_heap SIZE_T_BASE, 0xab, 0xaa, 0xac
        call _print_debug_alloc

        push 0
        call _exit
%elif __BITS__ == 16  
%endif


    %ifdef DEBUG_ENABLE
    global _print_debug_alloc
    _print_debug_alloc:
        SAVE_OLD_STACK_FRAME

        get_size_block SIZE_T_CONTADOR, SIZE_T_BASE
        push SIZE_T_SIZE_OPERATION [SIZE_T_CONTADOR]
        push format_struct_size_block 
        call func_printf
        add TOP_STACk, (__BITS__/8) * 2

        get_pointer SIZE_T_CONTADOR, SIZE_T_BASE
        push SIZE_T_SIZE_OPERATION [SIZE_T_CONTADOR]
        push format_struct_pointer
        call func_printf
        add TOP_STACk, (__BITS__/8) * 2

        get_status SIZE_T_CONTADOR, SIZE_T_BASE
        push WORD [SIZE_T_CONTADOR]
        push format_struct_status 
        call func_printf
        add TOP_STACk, (__BITS__/8) * 2

        GET_OLD_STACK_FRAME
    %endif


; x64 -> C Calling Convention
;   funtion(RDI, RSI, DRX, RCX, R8, R9)

    global _malloc_heap_run_time
    _alloc_heap_run_time:
        ; se guarda en DI la cantidad de memoria a reservar
        SAVE_OLD_STACK_FRAME

        call .aligned_addr
        ; se espera que el valor alineado se devuelva en SIZE_T_BASE(RBX/EBX/BX)
        ;mov SIZE_T_ACUMLADOR, [init_alloc]
        ;xor SIZE_T_ACUMLADOR, SIZE_T_ACUMLADOR
        ;add SIZE_T_ACUMLADOR, SIZE_T_BASE
        %ifdef DEBUG_ENABLE
            push SIZE_T_BASE
            push format_counter_alloc 
            call func_printf
        %endif         
        mov SIZE_T_ACUMLADOR, SIZE_T_BASE
        

        GET_OLD_STACK_FRAME
        ret
        
        .aligned_addr:
            ;   _alloc_heap_run_time(16, 24, 32....)
            ;
            ; mov value, __BITS__      (SIZE_T_DATOS[ECX])
            ; dec value                (SIZE_T_DATOS[ECX])
            ; add to_be_aligned, value (SIZE_T_BASE [EBX])
            ;
            ; not value                (SIZE_T_DATOS[ECX])
            ;
            ; and to_be_aligned, value (SIZE_T_BASE [EBX])
            ;
            ;   AND_operator((to_be_aligned + sizeof(size_t) - 1), 
            ;       NOT_operator(sizeof(size_t) - 1));
            ;
            ; 64bits:
            ;   align(3);  //  8
            ;   align(8);  //  8
            ;   align(12); // 16
            ;   align(16); // 16
            ;
            ; 32bits:
            ;   align(3);  //  4
            ;   align(8);  //  8
            ;   align(12); // 12
            ;   align(16); // 16


            %if   __BITS__ == 64
                ; rdi tiene el valor a alinear, RSI es la direccion base
                mov SIZE_T_BASE, RDI
                add SIZE_T_BASE, RSI
            %elif __BITS__ == 32 || __BITS__ == 16  
                ; se espera que el valor a alinear este en 
                ; BASE_STACk + ((__BITS__/8) *2)
                mov SIZE_T_BASE, [BASE_STACk + ((__BITS__/8) *2)]
                add SIZE_T_BASE, [BASE_STACk + ((__BITS__/8) *3)]
            %endif

            mov SIZE_T_DATOS, __BITS__
            dec SIZE_T_DATOS

            add SIZE_T_BASE, SIZE_T_DATOS
            not SIZE_T_DATOS
            and SIZE_T_BASE, SIZE_T_DATOS
            mov [counter_alloc], SIZE_T_BASE   

            ret


        