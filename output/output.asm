default rel         ; configura el ensamblador para que utilice la dirección de memoria relativa al puntero de instrucción (RIP). En el modelo x64, el uso de direcciones relativas al puntero de instrucción es común y facilita la portabilidad del código.
global WinMain
extern ExitProcess  ; external functions in system libraries 
extern MessageBoxA

section .data 
title:  db 'Win64', 0
msg:    db 'Hello world!', 0

section .text
WinMain:
	; sub rsp, 28h: Esta instrucción sustrae 40 bytes (28h en hexadecimal) del valor actual de rsp. Esto se hace para reservar espacio en la pila antes de llamar a MessageBoxA. En la convención x64 de Windows, se requiere que la pila esté alineada a múltiplos de 16 bytes antes de realizar una llamada a función.
    sub rsp, 28h      ; Este espacio es utilizado para almacenar los primeros cuatro argumentos de la función si es necesario y asegura que la pila esté alineada correctamente antes de la llamada.
    mov rcx, 0       ; hWnd = HWND_DESKTOP
    lea rdx,[msg]    ; LPCSTR lpText
    lea r8,[title]   ; LPCSTR lpCaption
    mov r9d, 0       ; uType = MB_OK
    call MessageBoxA ; En sistemas Windows x64, la convención de llamada estándar es fastcall. Esto significa que los primeros cuatro argumentos se pasan a través de los registros RCX, RDX, R8, y R9. En tu código, estas instrucciones son utilizadas correctamente para pasar los argumentos a la función MessageBoxA.

    mov  ecx,eax        ; exit status = return value of MessageBoxA
    call ExitProcess

    add rsp, 28h       ; if you were going to ret, restore RSP

    ret