default rel         ; Use RIP-relative addressing like [rel msg] by default
global WinMain
extern ExitProcess  ; external functions in system libraries 
extern MessageBoxA

; nasm -f win64 output.asm
; gcc output.obj -o output.exe -nostartfiles -luser32 -lgdi32 -luser32

section .text
WinMain:
    push rbp
    mov rbp, rsp
    and rsp, 0fffffffffffffff0h ;make sure stack 16-byte aligned   
    ;mov eax, 'hola'
    ;mov dword  [rbp-0x0], eax ; var =  hola mundo\0
    ;mov rax, ' mundo\0'
    ;mov qword  [rbp-0x8], rax ; var = hola mundo\0

    jmp salt
    mssg:    db 'Hello world!', 0
    salt:

    ;mov dword [rsp], 0x43414341
    ;mov dword [rsp + 4], 0x004241

    ;mov dword [rsp + 8], 0x43414341
    ;mov dword [rsp + 12], 0x004241

    ;sub rsp, 0x10 ; make some room on the stack
    ;mov dword [rbp - 8],0x41424142
    ;mov dword [rbp - 12], 0x00434143 
    ;mov rax, 0x0043414341424142
    ;mov  [rbp ], rax
    ;mov dword [rbp ],0x41424142 ; poner rbp
    ;mov dword [rbp + 4], 0x00434143 
    
    ;sub rsp, 16
    ;mov rax, 0x0042414243434343
    ;mov [rbp -8], rax
    ;mov rax, 0x4142414243434343
    ;mov qword [rbp -16], rax 

    sub rsp, 32
    ;mov qword rax, 0x0000000000006f64
    ;mov [rbp-8], rax ; var = hola mundo\0
    ;mov rax, 0x6e756d20616c6f68
    ;mov qword [rbp-16],  rax ; var =  hola mundo\0
    ;mov dword rax, 0x00006f64

    %define BASE_STACk rbp
                mov byte  [BASE_STACk-0x2], 0x00 ; var = n holaaaaaaa mundo\0
                mov rax, 0x6f646e756d206161 ; var =  holaaaaaaa mundo\0
                mov   [BASE_STACk-0xa], RAX ; var =  holaaaaaaa mundo\0
                mov rax, 0x61616161616c6f68 ; var =  holaaaaaaa mundo\0
                mov   [BASE_STACk-0x12], RAX ; var =  holaaaaaaa mundo\0


    ;sub rsp, 28h      ; reserve shadow space and make RSP%16 == 0
    mov rcx, 0       ; hWnd = HWND_DESKTOP
    ;lea rdx,[rax]    ; LPCSTR lpText
    lea rdx, [BASE_STACk-0x12]  
    lea r8,[mssg]   ; LPCSTR lpCaption
    mov r9d, 0       ; uType = MB_OK
    call MessageBoxA

    mov  ecx,eax        ; exit status = return value of MessageBoxA
    call ExitProcess

    ;add rsp, 28h       ; if you were going to ret, restore RSP

    ret