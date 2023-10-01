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
    .status:        resb    1  ; estados del bloque, 1 usado, 0 libre
endstruc

%define sizeof_Header_block_heap Header_block_heap.size_block + Header_block_heap.pointer + Header_block_heap.status

%macro set_size_block 2
    mov SIZE_T_SIZE_OPERATION [%1 + Header_block_heap.size_block], %2 
%endmacro
%macro set_pointer 2
    mov SIZE_T_SIZE_OPERATION [%1 + Header_block_heap.pointer], %2 
%endmacro
%macro set_status 2
    mov byte [%1 + Header_block_heap.status], %2 
%endmacro

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
;   push eax = esp-4, el ultimo valor pueso en la pila siempe esta en esp-4
;   pop  eax = esp+4
;    
;    ____________________    <--- 0xxffff (direcciones altas)
;   |        Stack       |
;   |--------------------|   <--- RSP/ESP/SP
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
;   |--------------------|  <--- 0x0000 (direcciones baja)
;

;    
;    ____________________    <--- 0xxffff (direcciones altas)
;   |        frame1      |
;   |--------------------|   
;   |        frame2      |
;   |--------------------| <---- ebp
;   |        frame 3     |
;   |____________________| <---- ebp - 4 (variable local de 4 bytes)
;   |  varLocal1[ebp-4]  |
;   |____________________| <---- ebp - 6 (variable local de 2 bytes)
;   |  varLocal1[ebp-6]  |
;   |--------------------|  
;   |        HE AP       |
;   |--------------------|  
;   |         bss        |
;   |--------------------|  
;   |         data       |
;   |--------------------|
;   |         text       |
;   |--------------------|  
;
 ; Contents                off ebp      off esp
 ; caller's variables      [ebp+16]    [esp+24]
 ; Argument 2              [ebp+12]    [esp+20]
 ; Argument 1              [ebp+8]     [esp+16]
 ; Caller Return Address   [ebp+4]     [esp+12]
 ; Saved ebp               [ebp]       [esp+8]
 ; Local variable 1        [ebp-4]     [esp+4]
 ; Local variable 2        [ebp-8]     [esp]
 ; 
 ; my_sub2: ; Returns first argument
 ;     push ebp  ; Prologue    [ebp] o [esp+8]
 ;     mov ebp, esp
 ;     mov eax, [ebp+8]
 ;     mov esp, ebp  ; Epilogue
 ;     pop ebp
 ;     ret

 function:
        push    ebp
        mov     ebp, esp
        sub     esp, 48 ; reserbar 40 bytes, + 8(de la direccion de retorno + el antiguo frame)
                        ; variable local
        mov     DWORD PTR [ebp-40], 1
        mov     DWORD PTR [ebp-36], 1
        mov     DWORD PTR [ebp-4], 1
        mov     edx, DWORD PTR [ebp+8]
        mov     eax, DWORD PTR [ebp+12]
        add     eax, edx
        leave
        ret