;nop
ja L1
nop
nop
mov rsi, my_label
mov r15, 78
;nop
;nop

L1
add rax, r13

mov rax, 60
mov rdi, 0

syscall
;global _start
;
;section .text
;
;    nop
;    nop
;    nop
;
;    mov rax, rbx
;	 mov rsi, my_label
;
;    mov qword [rsi], rax
;
;    nop
;    nop
;    nop
;
;    mov rax, 60
;	 mov rdi, 0
;    nop
;	 syscall
;	 nop

my_label db "Eee. Heeellooo, ASM!"
