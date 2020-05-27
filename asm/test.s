global _start

section .text

    nop
    nop
    nop

    mov rax, my_label
	mov rsi, 4
    mov qword [rax], 5
    nop
    nop
    nop

    mov rax, 60
	mov rdi, 0
    nop
	syscall
	nop

my_label db "Eee. Heeellooo, ASM!"
