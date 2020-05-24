ja 66145416       ; 0f87844cf103
jnbe 5614         ; 0f87ea15
jnc 1654          ; 0f837206
jne 86174654      ; 0f85baeb2205
jng 8416          ; 0f8edc20
jnge -64156       ; 0f8c6005ffff
jnl 6514          ; 0f8d6e19
jnle 641          ; 0f8f7d02
jno 625           ; 0f816d02
jnp 654           ; 0f8b8a02

;jmp 5796

;push qword [rsi + r14 + 17]
;
;pop qword [rsi + r14 + 17]
;pop qword [rsi + rbp + 17]
;pop rbx
;pop r15
;
;idiv al
;idiv r15
;L1 dd 0
;mul r14
;div r14
;imul rax, 48
;mov [ebp -24], rax
;
;sub rax, rdx
;sub [rax + rbx -7], rbx
;sub ah, al
;sub esi, [eax]
;
;imul rax, rbx
;imul rax, [rbx]
;imul r13, [rsi + rsi + 562]
;imul r13, [rsi + rsi + 562]
;
;mov bl, 150
;mov ah, 150
;mov ax, 150
;mov eax, 150
;mov rax, 150
;
;mov r13, [rsp + 56415614]
;mov rax, [rsi]              ; 488b06
;
;mov ah, bl                  ; 88dc
;mov eax, esi                ; 89f0
;mov [ebp + 14], edx         ; 6789550e
;
;mov rax, rbx                ; 4889d8
;mov r12, rsi                ; 4989f4
;mov r15, r15                ; 4d89ff
;
;mov [rax + 5], rcx          ; 48894805
;mov [r12 + r13 + 5], r8     ; 4d89442c05
;mov [rax + rbx], rdx        ; 48891418
;mov [rsi], rdi              ; 48893e
;
;mov [rbp + 78], rcx         ; 48894d4e
;mov [rsp + 15], rcx         ; 48894c240f

;section .rodata
;aaaaa db "Hello!", 0x0



























