mov dh, bl
mov eax, esi
mov r9, rax
add rax, rbx
add al, bh

global _start

section .text

_start:


func:
    mov rax, rcx
    inc rax
    ret

section .rodata

str567 dw "Hello", 0x0
