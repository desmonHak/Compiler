default rel         ; Utiliza por defecto el direccionamiento relativo RIP como [rel msg].
;[rel msg]

; funciones globales a exportar:
global WinMain

extern ExitProcess  ; funciones externas en las bibliotecas del sistema
extern MessageBoxA

section .text
WinMain:
    push rbp
    mov rbp, rsp
    and rsp, 0fffffffffffffff0h ; asegúrese de que la pila está alineada a 16 bytes   

    sub rsp, 32

    %define BASE_STACk rbp
    mov byte  [BASE_STACk-0x2], 0x00 ; var = n holaaaaaaa mundo\0
    mov rax, 0x6f646e756d206161 ; var =  holaaaaaaa mundo\0
    mov   [BASE_STACk-0xa], RAX ; var =  holaaaaaaa mundo\0
    mov rax, 0x61616161616c6f68 ; var =  holaaaaaaa mundo\0
    mov   [BASE_STACk-0x12], RAX ; var =  holaaaaaaa mundo\0


    ;sub rsp, 28h      ; reservar shadow space y hacer RSP % 16 == 0

    ; int MessageBoxA(
    ;   [in, optional] HWND   hWnd      = HWND_DESKTOP,
    ;   [in, optional] LPCSTR lpText    = BASE_STACk - 0x12,
    ;   [in, optional] LPCSTR lpCaption = BASE_STACk - 0x12,
    ;   [in]           UINT   uType     = MB_OK
    ; );

    mov rcx, 0                   ; hWnd = HWND_DESKTOP
    ;lea rdx, [rax]              ; LPCSTR lpText
    lea rdx, [BASE_STACk - 0x12] ; LPCSTR lpText
    lea r8,  [BASE_STACk - 0x12] ; LPCSTR lpCaption
    mov r9d, 0                   ; uType = MB_OK
    call MessageBoxA             ; eax = MessageBoxA(HWND_DESKTOP, mssg, mssg, MB_OK)

    mov  ecx, eax                ; exit status = return value of MessageBoxA
    call ExitProcess             ; ExitProcess(ecx = eax)

    ;add rsp, 28h                ; si fueras a retirarte, restaura RSP

    ret