global _start

section .text

_start:
    
    add rax, -15

	nop
	nop
    nop
	sub rax, 0x3C
	xor rdi, rdi
	
	syscall

func:
    mov rax, rcx
    inc rax
    ret

section .rodata

str567 dw "Hello", 0x0
