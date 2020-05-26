global _start

section .text

    nop
    nop
    nop

    mov rax, rbx
	mov rsi, my_label

    nop
    nop
    nop

    mov rax, 60
	mov rdi, 0
    nop
	syscall
	nop

my_label db "Eee. Heeellooo, ASM!"
