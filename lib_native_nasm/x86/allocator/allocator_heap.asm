 ;	Licencia Apache, Versión 2.0 con Modificación
 ;	
 ;	Copyright 2023 Desmon (David)
 ;	
 ;	Se concede permiso, de forma gratuita, a cualquier persona que obtenga una copia de 
 ;	este software y archivos de documentación asociados (el "Software"), para tratar el 
 ;	Software sin restricciones, incluidos, entre otros, los derechos de uso, copia, 
 ;	modificación, fusión, publicación, distribución, sublicencia y/o venta de copias del 
 ;	Software, y para permitir a las personas a quienes se les proporcione el Software 
 ;	hacer lo mismo, sujeto a las siguientes condiciones:
 ;	
 ;	El anterior aviso de copyright y este aviso de permiso se incluirán en todas las 
 ;	copias o partes sustanciales del Software.
 ;	
 ;	EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O 
 ;	IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD 
 ;	PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN. EN NINGÚN CASO LOS TITULARES DEL 
 ;	COPYRIGHT O LOS TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE NINGÚN 
 ;	RECLAMO, DAÑO U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE 
 ;	OTRA MANERA, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTRO TIPO
 ;	DE ACCIONES EN EL SOFTWARE.
 ;	
 ;	Además, cualquier modificación realizada por terceros se considerará propiedad del 
 ;	titular original de los derechos de autor. Los titulares de derechos de autor 
 ;	originales no se responsabilizan de las modificaciones realizadas por terceros.
 ;	
 ;	Queda explícitamente establecido que no es obligatorio especificar ni notificar los 
 ;	cambios realizados entre versiones, ni revelar porciones específicas de código 
 ;	modificado.
 ;


%if   __BITS__ == 64
[BITS 64]

%elif __BITS__ == 32
[BITS 32]
%elif __BITS__ == 16  
[BITS 16]
%endif


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

global init_bss
global end_bss
global init_alloc
section .data
    init_bss      SIZE_T_DATA __bss_start ; inicio de bss
    end_bss       SIZE_T_DATA __bss_end   ; final de bss
    init_alloc    SIZE_T_DATA (__bss_end + 1) ; inicio del heap
    align_value db 1 ;  tamaño de alineamiento
    msg dd  __BITS__

    %ifdef DEBUG_ENABLE
    format_init_bss   db "init bss: 0x%p",   0xa, 0x0
    format_end_bss    db "end bss: 0x%p",    0xa, 0x0
    format_init_alloc db "init Alloc: 0x%p", 0xa, 0x0
    format_esp        db "value esp: 0x%p",  0xa, 0x0
    format_ebp        db "value ebp: 0x%p",  0xa, 0x0

    format_struct_size_block     db "[+] value size_block: 0x%p",  0xa, 0x0
    format_struct_padding        db "[+] padding del bloque: 0x%hx",   0xa, 0x0
    format_struct_status         db "[+] value status: 0x%hhx",  0xa, 0x0
    format_struct_pointer        db "[+] value pointer: 0x%p",  0xa, 0x0

    format_memresever db "dirrecion de memoria inicializada: 0x%p", 0xa, 0xa,0x0
    format_counter_alloc db "new counter_alloc:  0x%p", 0xa, 0x0
    %endif
%endif


section .text
    %if   __BITS__ == 64
        global init_allocator
        init_allocator:
    %elif __BITS__ == 32
    global _init_allocator
    _init_allocator:
    %define init_allocator _init_allocator

        SAVE_OLD_STACK_FRAME
        mov byte [__bss_start], 0xff
        mov byte [__bss_end],   0xff

        cmp SIZE_T_SIZE_OPERATION [counter_alloc], 0x0
        jne is_not_zero

            ;mov SIZE_T_BASE, align_value

            ;mov SIZE_T_DATOS, __BITS__
            ;dec SIZE_T_DATOS

            ;add SIZE_T_BASE, SIZE_T_DATOS
            ;not SIZE_T_DATOS
            ;and SIZE_T_BASE, SIZE_T_DATOS
            

            lea SIZE_T_BASE, [align_value + __BITS__ - 1]
            mov SIZE_T_DATOS, (__BITS__ - 1)
            not SIZE_T_DATOS
            and SIZE_T_BASE, SIZE_T_DATOS

            mov [align_value], SIZE_T_BASE

            ;mov SIZE_T_BASE, init_alloc

            ;mov SIZE_T_DATOS, __BITS__
            ;dec SIZE_T_DATOS

            ;add SIZE_T_BASE, SIZE_T_DATOS
            ;not SIZE_T_DATOS
            ;and SIZE_T_BASE, SIZE_T_DATOS

            lea SIZE_T_BASE, [init_alloc + __BITS__ - 1]
            mov SIZE_T_DATOS, (__BITS__ - 1)
            not SIZE_T_DATOS
            and SIZE_T_BASE, SIZE_T_DATOS


            mov SIZE_T_SIZE_OPERATION [init_alloc], SIZE_T_BASE
            mov [counter_alloc], SIZE_T_BASE
            set_status SIZE_T_BASE, 0
        is_not_zero:
            GET_OLD_STACK_FRAME
    %endif



; x64 -> C Calling Convention
;   funtion(RDI, RSI, DRX, RCX, R8, R9)

    %if   __BITS__ == 64
        global alloc_heap_run_time
        alloc_heap_run_time:
    %elif __BITS__ == 32
        global _alloc_heap_run_time
        _alloc_heap_run_time:
        %define alloc_heap_run_time _alloc_heap_run_time
    %endif
        ; se guarda en DI la cantidad de memoria a reservar
        SAVE_OLD_STACK_FRAME

        call aligned_addr

        set_status SIZE_T_BASE, 1 ; poner que el nuevo bloque reservado esta en uso

        %ifdef DEBUG_ENABLE
            push SIZE_T_BASE
            push format_counter_alloc 
            call func_printf
        %endif         

        %ifdef DEBUG_ENABLE
            call _print_debug_alloc
        %endif         

        ; se espera que el valor alineado se devuelva en SIZE_T_BASE(RBX/EBX/BX)
        ;mov SIZE_T_ACUMLADOR, [init_alloc]
        ;xor SIZE_T_ACUMLADOR, SIZE_T_ACUMLADOR
        ;add SIZE_T_ACUMLADOR, SIZE_T_BASE

        mov SIZE_T_ACUMLADOR, SIZE_T_BASE
        GET_OLD_STACK_FRAME
        ret
        
        aligned_addr:
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

            ; reservar espacio para la estcutura en la pila
            ; sub TOP_STACk, sizeof_Header_block_heap

            ; reservar espacio para un puntero:
            ; sub TOP_STACk, __BITS__/8

            %if   __BITS__ == 64
                ; rdi tiene el valor a alinear, RSI es la direccion base
                add RDI, sizeof_Header_block_heap ; sumarle a la memoria a reservar, el tamaño del header block
                mov SIZE_T_BASE, RDI ; mover la memoria a reservar al registro base
                mov SIZE_T_CONTADOR, SIZE_T_BASE ; guardar todo antes de sumarle la direccion base
                add SIZE_T_BASE, RSI ; sumarle la direccion base
            %elif __BITS__ == 32 || __BITS__ == 16  
                ; se espera que el valor a alinear este en 
                ; BASE_STACk + ((__BITS__/8) *2)
                mov SIZE_T_BASE, [BASE_STACk + ((__BITS__/8) *3)] ; memoria a reservar
                add SIZE_T_BASE, sizeof_Header_block_heap ; sumarle a la memoria a reservar, el tamaño del header block
                mov SIZE_T_CONTADOR, SIZE_T_BASE ; guardar todo antes de sumarle la direccion base
                add SIZE_T_BASE, [BASE_STACk + ((__BITS__/8) *2)] ; sumarle la direccion base
            %endif

            ; alineando
            ;mov SIZE_T_DATOS, __BITS__
            ;dec SIZE_T_DATOS

            ;add SIZE_T_BASE, SIZE_T_DATOS
            ;not SIZE_T_DATOS
            ;and SIZE_T_BASE, SIZE_T_DATOS

            lea SIZE_T_BASE, [SIZE_T_BASE + __BITS__ - 1]
            mov SIZE_T_DATOS, (__BITS__ - 1)
            not SIZE_T_DATOS
            and SIZE_T_BASE, SIZE_T_DATOS

            mov SIZE_T_SIZE_OPERATION [SIZE_T_BASE + Header_block_heap.size_block], SIZE_T_CONTADOR
                                               ; poner en el header del nuevo bloque, 
                                               ; la suma de bloque solicitado + bloque cabecera


            push SIZE_T_BASE

            mov SIZE_T_BASE, [counter_alloc]
            cmp byte [SIZE_T_BASE + Header_block_heap.status], 1 ; si es 1, el bloque es valido
            ; si es 0 supondremos que el bloque anterior no existe debido a que este es el
            ; primer bloque en reserbase, o podemos suponer que el bloque anterior esta libre.
            jne bloque_no_valido

                ; si el bloque es valido entonces guarda una copia en ebx
                mov  SIZE_T_CONTADOR, SIZE_T_BASE
                pop  SIZE_T_BASE  ; restaurar eax
                mov  [SIZE_T_BASE + Header_block_heap.pointer], SIZE_T_CONTADOR ; mover a pointer, ebx
                jmp  end
                bloque_no_valido:
                    pop  SIZE_T_BASE
                    mov SIZE_T_SIZE_OPERATION [SIZE_T_BASE + Header_block_heap.pointer], 0x0
            end:

            mov [counter_alloc], SIZE_T_BASE   
            ret



    %ifdef DEBUG_ENABLE
    global func_WinMain
    func_WinMain:
        SAVE_OLD_STACK_FRAME

        call init_allocator
        
        push SIZE_T_SIZE_OPERATION [init_bss]
        push format_init_bss 
        call func_printf
    
        ; sumar al tope de la pila el tamaño de palabra *2
        ; de los dos push's para restaurar la pila
        ; add TOP_STACk, (__BITS__/8) * 2

        push SIZE_T_SIZE_OPERATION [end_bss]
        push format_end_bss 
        call func_printf


        push SIZE_T_SIZE_OPERATION [init_alloc]
        push format_init_alloc 
        call func_printf


        push TOP_STACk
        push format_esp 
        call func_printf

    
        push BASE_STACk
        push format_ebp 
        call func_printf

        

        push 5                                  ; memoria a reservar
        push SIZE_T_SIZE_OPERATION [counter_alloc] ; direccion base a usar
        call alloc_heap_run_time
        push SIZE_T_ACUMLADOR
        push format_memresever 
        call func_printf


        push 10                            ; memoria a reservar
        push SIZE_T_SIZE_OPERATION [counter_alloc] ; direccion base a usar
        call alloc_heap_run_time
        push SIZE_T_ACUMLADOR
        push format_memresever 
        call func_printf



        sub esp, 2 * Header_block_heap
        ; Accede a las estructuras a través de ESP

        mov SIZE_T_BASE, [esp + (Header_block_heap * 0)]                         
        set_size_block SIZE_T_BASE, 0xfb
        set_pointer SIZE_T_BASE, 0xfa
        set_status SIZE_T_BASE, 0xfc
        call _print_debug_alloc

        mov SIZE_T_BASE, [esp + (Header_block_heap * 1)] ; Accede a la segunda estructura
        create_struct_Header_block_heap SIZE_T_BASE, 0xab, 0xaa, 0xac
        call _print_debug_alloc

        push 0
        call func_exit
        %endif

%if   __BITS__ == 64
%elif __BITS__ == 32
%elif __BITS__ == 16  
%endif


    %ifdef DEBUG_ENABLE
    global _print_debug_alloc
    _print_debug_alloc:
        ; el registro base(SIZE_T_BASE) tiene la direccion a la estructura a imprimir
        SAVE_OLD_STACK_FRAME

        sub TOP_STACk, 2

        ; obtiene la direccion del miembro y lo coloca en SIZE_T_CONTADOR
        push AX
        get_size_block SIZE_T_CONTADOR, SIZE_T_BASE ; obtiene el size block
        mov AX, [SIZE_T_CONTADOR]
        mov uint16_t [TOP_STACk+2], AX ; guarda el size block en la pila;
        pop AX
        push SIZE_T_SIZE_OPERATION [SIZE_T_CONTADOR]
        push format_struct_size_block 
        call func_printf
        add TOP_STACk, (__BITS__/8) * 2
        
        mov SIZE_T_CONTADOR, [TOP_STACk]                     ; eax = MemoryAddress
        add SIZE_T_CONTADOR, sizeof_Header_block_heap        ; eax += HeaderSize
        dec SIZE_T_CONTADOR                                  ; eax -= 1
        add SIZE_T_CONTADOR, [align_value]                   ; eax += Alignment
        not SIZE_T_CONTADOR                                  ; eax = ~eax
        inc SIZE_T_CONTADOR                                  ; eax += 1
        and SIZE_T_CONTADOR, [align_value]                   ; eax &= Alignment
        dec SIZE_T_CONTADOR                                  ; eax -= 1 (final result in eax)


        ;mov ax, [TOP_STACk]
        ;sub ax, sizeof_Header_block_heap ; obtener el tamaño de los datos reservados
        push SIZE_T_CONTADOR
        push format_struct_padding 
        call func_printf
        add TOP_STACk, (__BITS__/8) * 2

        get_pointer SIZE_T_CONTADOR, SIZE_T_BASE ; obtiene el pointer al siguiente bloque
        push SIZE_T_SIZE_OPERATION [SIZE_T_CONTADOR]
        push format_struct_pointer
        call func_printf
        add TOP_STACk, (__BITS__/8) * 2

        get_status SIZE_T_CONTADOR, SIZE_T_BASE ; obtiene el estado del bloque actual
        push WORD [SIZE_T_CONTADOR]
        push format_struct_status 
        call func_printf
        add TOP_STACk, (__BITS__/8) * 2

        inc TOP_STACk
        inc TOP_STACk
        GET_OLD_STACK_FRAME
    %endif

