sub rax, rdx
sub [rax + rbx + 7], rbx
sub ah, al
sub esi, [eax]

imul rax, rbx
imul rax,  [rbx]

mov bl, 150
mov ah, 150
mov ax, 150
mov eax, 150
mov rax, 150

mov r13, [rsp + 56415614]
mov rax, [rsi]              ; 488b06

mov ah, bl                  ; 88dc
mov eax, esi                ; 89f0
mov [ebp + 14], edx         ; 6789550e

mov rax, rbx                ; 4889d8
mov r12, rsi                ; 4989f4
mov r15, r15                ; 4d89ff

mov [rax + 5], rcx          ; 48894805
mov [r12 + r13 + 5], r8     ; 4d89442c05
mov [rax + rbx], rdx        ; 48891418
mov [rsi], rdi              ; 48893e

mov [rbp + 78], rcx         ; 48894d4e
mov [rsp + 15], rcx         ; 48894c240f





























