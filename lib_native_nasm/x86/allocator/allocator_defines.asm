%include "../base.asm"

%define DEBUG_ENABLE

%define authot "Desmon"
%define github "https://github.com/desmonhak"


;
;                          __________________________        __________________________
;                         |                         v       |                         v 
;   --------------------------------  --------------------------------
;   |size_block|status|pointer|data|  |size_block|status|pointer|data|           ... .....
;   --------------------------------  --------------------------------
;       16        1      0x11   ...         8       0     0x1a    ...
;              [bloque ocupado]                  [blqoue libre]
;
; cabecera del bloque de memoria solicitado
struc Header_block_heap
    .size_block: SIZE_T_BSS 1  ; tamaño del (bloque solicitado + bloque cabecera + alineamiento)
    .pointer:    SIZE_T_BSS 1  ; puntero al siguiente bloque
    .status:        resw    1  ; estados del bloque, 1 usado, 0 libre
endstruc

%define set_size_block(addr_base, value) mov SIZE_T_SIZE_OPERATION [addr_base + Header_block_heap.size_block], value 
%define set_pointer(addr_base, value)    mov SIZE_T_SIZE_OPERATION [addr_base + Header_block_heap.pointer   ], value
%define set_status(addr_base, value)     mov WORD                  [addr_base + Header_block_heap.status    ], value 
%macro get_size_block 2
    lea %1, [%2 + Header_block_heap.size_block]
%endmacro
%macro get_pointer 2
    lea %1, [%2 + Header_block_heap.pointer]
%endmacro
%macro get_status 2
    lea %1, [%2 + Header_block_heap.status]
%endmacro

; crea una estructura Header_block_heap:
; create_struct_Header_block_heap direccion_base, valor_size_block, valor_pointer, ...
%macro create_struct_Header_block_heap 4
        mov SIZE_T_SIZE_OPERATION [%1 + Header_block_heap.size_block], %2
        mov SIZE_T_SIZE_OPERATION [%1 + Header_block_heap.pointer   ], %3
        mov WORD                  [%1 + Header_block_heap.status    ], %4
%endmacro

; modo largo y protegido:
;    
;    ____________________    <--- 0xxffff
;   |        Stack       |
;   |--------------------|   <--- ERBP/EBP/BP
;   |          |         |
;   |          v         |
;   |                    |
;   |   Area sin mapear  |
;   |                    |
;   |          ^         |
;   |          |         |
;   |--------------------|  <- brk (program break)
;   |        HE AP       |
;   |--------------------|  <- __bss_end
;   |         bss        |
;   |--------------------|  <- __bss_start
;   |         data       |
;   |--------------------|
;   |         text       |
;   |--------------------|  <--- 0x0000
;