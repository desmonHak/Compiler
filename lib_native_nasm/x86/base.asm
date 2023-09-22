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