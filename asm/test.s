global _start

section .text

_start:
    mov cx, 8
L1:
    dec cx
    loope L1
    loopne L1
    loopz L1
    loopnz L1

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
