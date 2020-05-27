global _start

section .text

_start:

    mov rsi, my_label
    call func

    mov rax, 60
    xor rdi, rdi

    syscall

func
    mov rax, 1
    mov rdi, 1
    mov rsi, my_label
    mov rdx, 20
    syscall

    ret

my_label db "Eee. Heeellooo, ASM!"
