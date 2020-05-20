global _start

section .text

_start:
    
    idiv r14
    mov rsi, rdi

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
