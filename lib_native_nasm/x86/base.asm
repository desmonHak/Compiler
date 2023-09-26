%define syscall_x86_32bits_Software int 0x80
%define syscall_x85_64bits_Software syscall

%define syscall_8086_Bios           int 0x10

%define true 1
%define false 0

%define SIZE_INT8  1
%define SIZE_INT16 2
%define SIZE_INT32 4
%define SIZE_INT64 8
%define SIZE_INT(bits) bits/8

; OF = 1 
%define JumpIfOverflow(symbol) jo symbol
; OF = 0 
%define JumpIfNotOverflow(symbol) jno symbol
; SF = 1 
%define JumpIfSign(symbol) js symbol
; SF = 0 
%define JumpIfNotSign(symbol) jns symbol
; ZF = 1 	 
%define JumpIfEqual(symbol) je symbol
;ZF = 0
%define JumpIfNotEqual(symbol) jne symbol
; ZF = 1 	 
%define JumpIfZero(symbol) jz symbol
; ZF = 0 
%define JumpIfNotZero(symbol) jnz symbol

%if __BITS__ == 64
%define SIZE_T_DATA DQ  
%define SIZE_T_BSS  RESQ 
%define SIZE_T_SIZE_OPERATION QWORD
%define TOP_STACk   RSP
%define BASE_STACk  RBP
%define SIZE_T_INDEICE_ORIGEN  RSI
%define SIZE_T_INDEICE_DESTINO RDI
%define SIZE_T_ACUMLADOR       RAX
%define SIZE_T_BASE            RBX
%define SIZE_T_CONTADOR        RCX
%define SIZE_T_DATOS           RDX
%elif __BITS__ == 32
%define SIZE_T_DATA DD  
%define SIZE_T_BSS  RESD 
%define SIZE_T_SIZE_OPERATION DWORD
%define TOP_STACk   ESP
%define BASE_STACk  EBP
%define SIZE_T_INDEICE_ORIGEN  ESI
%define SIZE_T_INDEICE_DESTINO EDI
%define SIZE_T_ACUMLADOR       EAX
%define SIZE_T_BASE            EBX
%define SIZE_T_CONTADOR        ECX
%define SIZE_T_DATOS           EDX
%elif __BITS__ == 16
%define SIZE_T_DATA DW  
%define SIZE_T_BSS  RESW 
%define SIZE_T_SIZE_OPERATION WORD
%define TOP_STACk   SP
%define BASE_STACk  BP
%define SIZE_T_INDEICE_ORIGEN  SI
%define SIZE_T_INDEICE_DESTINO DI
%define SIZE_T_ACUMLADOR       AX
%define SIZE_T_BASE            BX
%define SIZE_T_CONTADOR        CX
%define SIZE_T_DATOS           DX
%endif

%macro SAVE_OLD_STACK_FRAME 0
    push BASE_STACk
    mov  BASE_STACk, TOP_STACk
%endmacro

%macro GET_OLD_STACK_FRAME 0
    %if __BITS__ == 32 || __BITS__ == 64
        leave  
    %elif __BITS__ == 16
        mov TOP_STACk, BASE_STACk
        pop BASE_STACk
    %endif
    ret
%endmacro

     ; Registros:
     ; AL/AH, CL/CH, DL/DH, BL/BH, SPL, BPL, SIL, DIL, R8B-R15B 
     ; AX,    CX,    DX,    BX,    SP,  BP,  SI,  DI,  R8W-R15W 
     ; EAX,   ECX,   EDX,   EBX,   ESP, EBP, ESI, EDI, R8D-R15D 
     ; RAX,   RCX,   RDX,   RBX,   RSP, RBP, RSI, RDI, R8-R15




%define GET_DATE      __DATE__             ;"2010-01-01" 
%define GET_TIME      __TIME__             ;"00:00:42" 
%define GET_DATE_NUM      __DATE_NUM__         ;20100101 
%define GET_TIME_NUM      __TIME_NUM__         ;000042 
%define GET_UTC_DATE      __UTC_DATE__         ;"2009-12-31" 
%define GET_UTC_TIME      __UTC_TIME__         ;"21:00:42" 
%define GET_UTC_DATE_NUM      __UTC_DATE_NUM__     ;20091231 
%define GET_UTC_TIME_NUM      __UTC_TIME_NUM__     ;210042 
%define GET_POSIX_TIME      __POSIX_TIME__       ;1262293242