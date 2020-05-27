;nop
ja L1
nop
nop
mov rsi, my_label
mov r15, 78
;nop
;nop
call my_label
L1
add rax, r13
xor rax, rax
mov rax, 60
xor rdi, rdi

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
