default rel ; 
extern puts ; tells NASM that puts is defined in another file. leaves gaps for linker to fill in
global main

section .data
msg db "Hello from assembly!", 0

section .text
main:
    sub  rsp, 40        ; 32 bytes "shadow space" + 8 to keep the stack 16-byte aligned, sp = stack pointer
    lea  rcx, [msg]     ; stores the adress of msg into rcx (rcx is the register where you put an argument for a function)
    call puts
    xor  eax, eax       ; return 0
    add  rsp, 40
    ret