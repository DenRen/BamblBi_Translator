global _start

section .text

_start:
	mov rax, 10000000000000
	mov rdi, rax
	push rax
	pop rbx
	
	mov rax, 0x3C
	xor rdi, rdi
	
	syscall