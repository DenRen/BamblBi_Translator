;───────────────────────────────────┬────────────────┐
;Input: rax                         │    printf_d_   │  
;Destr: rax rdx r10 rsi rdi         └────────────────┘
 
printf_d_:
size_num_d equ 24  		; Size must be a multiple of 8 

	enter size_num_d, 0	
	
	std
	
	mov rdi, rbp
	sub rdi, 16 
	mov rsi, rdi
	mov r10, 10
	
prt_div_:
	xor rdx, rdx
	div r10
	xchg dl, al
	add al, '0'
	stosb
	mov al, dl
	
	cmp rax, 0
	jnz prt_div_
	
	cld

	mov rdx, rsi
	sub rdx, rdi
	mov rsi, rdi
	inc rsi
			
	xor rax, rax
	xor rdi, rdi
	inc al
	inc dil
	
	mov r10, rcx        ; Save RCX  
    syscall
    mov rcx, r10
	
	leave	
	ret

;───────────────────────────────────┬────────────────┐
;Input: rax                         │    printf_x_   │  
;Destr: rax rdx r10 r11 rsi rdi     └────────────────┘

printf_x_:
size_num_x equ size_num / 2  	; Size must be a multiple of 8 

	enter size_num_x, 0	
	
	std
	
	mov rdx, rbp
	sub rdx, size_num_x
	mov rdi, rbp
	;sub rdi, 8

	mov r11, 8
prt_x_l_:

	shl r10, 8
	mov r10b, 0b00001111 
	and r10b, al
	add r10b, '0'
	cmp r10b, '0' + 9
	jna not_symb_	
	add r10b, 'A' - ('0' + 10)
not_symb_:
	shr rax, 1 * 4 
	
	dec r11
	cmp r11, 0
	jne prt_x_l_	
	
	xchg r10, rax
	stosq 
	mov  rax, r10
		
	add r11, 8
	cmp rdi, rdx
	jne prt_x_l_ 
	
	xor rax, rax
	xor rdi, rdi

	inc al		; RAX = 1
	inc dil		; RDI = 1
	
	mov rsi, rdx
	add rsi, r11
	mov rdx, size_num_x
	
	mov r10, rcx        ; Save RCX  
    syscall
    mov rcx, r10	 	

prt_x_f_:
	cld	
	
	leave
	ret

;───────────────────────────────────┬────────────────┐
;Input: rax                         │    printf_o_   │  
;Destr: rax rdx r10 r11 rsi rdi     └────────────────┘

;Что быстрее mov r10b, 0b00000111 или or r10b, 0b00000111  (Изначально r10b == 0)
printf_o_:
size_num_o equ  ((size_num / 8) / 3 + 1) * 8 	; Size must be a multiple of 8 

	enter size_num_o, 0	
	
	std
	
	mov rdx, rbp
	sub rdx, size_num_o
	mov rdi, rbp
	;sub rdi, 8

	mov r11, 8
prt_o_l_:

	shl r10, 8
	mov r10b, 0b00000111 
	and r10b, al
	add r10b, '0'	
	
	shr rax, 1 * 3
	
	dec r11
	cmp r11, 0
	jne prt_o_l_	
	
	xchg r10, rax
	stosq 
	mov  rax, r10
		
	add r11, 8
	cmp rdi, rdx
	jne prt_o_l_ 
	
	xor rax, rax
	xor rdi, rdi

	inc al		; RAX = 1
	inc dil		; RDI = 1
	
	mov rsi, rdx
	add rsi, r11
	mov rdx, size_num_o
	
	mov r10, rcx        ; Save RCX  
    syscall
    mov rcx, r10
	 	

prt_o_f_:
	cld	
	
	leave
	ret

; Спросить по поводоу того, почему enter 4 * 8, 0 выделяет 5 * 8 байт, а не 4 * 8

;───────────────────────────────────┬────────────────┐
;Input: rax                         │    printf_b_   │  
;Destr: rax rdx r10 r11 rsi rdi     └────────────────┘

size_num equ 4 * 8
printf_b_: 
	enter size_num, 0
	
	std
	
	mov rdx, rbp
	sub rdx, size_num
	mov rdi, rbp
	;sub rdi, 8

	mov r11, 8
prt_b_l_:

	shl r10, 8
	bt ax, 0	
	jnc _dont_inc 
	inc r10b
_dont_inc:
	add r10b, '0'	
	
	shr rax, 1
	
	dec r11
	cmp r11, 0
	jne prt_b_l_	
	
	xchg r10, rax
	stosq 
	mov  rax, r10
		
	add r11, 8
	cmp rdi, rdx
	jne prt_b_l_ 

	
	xor rax, rax
	xor rdi, rdi

	inc al		; RAX = 1
	inc dil		; RDI = 1
	
	mov rsi, rdx
	add rsi, r11
	mov rdx, size_num
	
	mov r10, rcx        ; Save RCX  
    syscall
    mov rcx, r10
	 	

prt_b_f_:
	cld	
	
	leave
	ret

;───────────────────────────────────┬────────────────┐
;Input: rax                         │    printf_c_   │  
;Destr: rax rdx r10 rsi rdi         └────────────────┘

printf_c_:

	push rax
	mov rsi, rsp
	add rsp, 8

	xor rax, rax
	xor rdi, rdi
	xor rdx, rdx
	inc al
	inc dil
	inc dl
	
	mov r10, rcx
	syscall
	mov rcx, r10
	
	ret

;───────────────────────────────────┬────────────────┐
;Input: rax                         │    printf_s_   │  
;Destr: rax rdx r10 rsi rdi         └────────────────┘

printf_s_:
	
	mov r10, rcx
	
	mov rsi, rax
	mov rdi, rax
	
	strlen
	
	mov rdx, rcx
		
	xor rax, rax
    xor rdi, rdi
    inc al
    inc dil
	
	syscall
		
	mov rcx, r10
	
	ret

; r9l = '\0', r9h = '%' 
; rcx - size buffer
; Dtr: rax rbx rcx rdx rsi r8 r9w r10 

;───────────────────────────────────┬────────────────┐
;Input: stack                       │    printf__    │  
;Destr: rax rbx rcx rdx rsi rdi     └────────────────┘
;		r8  r9  r10 r11 r12 r13 r14
printf__:
	
	mov r14, 8					; I will be use r14 how counter for arg pointer
 	
	mov rsi, [rsp + r14]	; rsi == string 
	add r14, 8
	mov rbx, rsi

;%use altreg
	xor rcx, rcx
	xor rdx, rdx
	xor r9, r9

scan_prf_:
	
	lodsq
	mov r8, rax			; Save data
		
	mov rcx, 8	
byte_processing:
	mov al, r8b
	shr r8,  8

	cmp al, 0			; r8b ?== '\0'
	je finish_printf_
												; Сравнение с регистром или с '%'?
		cmp r9, 0
		jne check_spec_symb
			
		cmp al, '%'	
		jne inc_rdx_
		
		mov r9, 1			; Have percent
		jmp short inc_rdx_

check_spec_symb:
		;if next symb != spec, that rdx++
		;else dec rdx; print_buf; print_spec; r9 = 0
		
		cmp al, 'b'
			je call_P_b
		cmp	al, 'o'
			je call_P_o
		cmp al, 'x'
			je call_P_x
		cmp al, 'd'
			je call_P_d
		cmp al, 'c'
			je call_P_c
		cmp al, 's'
			je call_P_s
		
		xor r9, r9 
		jmp short inc_rdx_

inc_rdx_:
	inc rdx
fin_loop_b_p_:
	LOOP byte_processing
	
	jmp scan_prf_
			
end_proc_spec_symb:
	mov rsi, r12
	mov rdi, r13
	xor r9, r9
	xor rdx, rdx
	jmp short fin_loop_b_p_		

;----------------------------------------------
; 									    switch
;----------------------------------------------
%macro prep_for_call_prtf_ 0
	dec rdx
	call print_buf_
	add rbx, 2
	mov rax, [rsp + r14]
	add r14, 8
	mov r12, rsi
	mov r13, rdi
%endmacro

call_P_b:
			prep_for_call_prtf_
			call printf_b_		
			jmp end_proc_spec_symb

call_P_o:
			prep_for_call_prtf_
            call printf_o_
            jmp end_proc_spec_symb

call_P_x:
			prep_for_call_prtf_
            call printf_x_
			jmp end_proc_spec_symb

call_P_d:
           	prep_for_call_prtf_ 
            call printf_d_
            jmp end_proc_spec_symb

call_P_c:
            prep_for_call_prtf_
            call printf_c_
            jmp end_proc_spec_symb

call_P_s:
            prep_for_call_prtf_
            call printf_s_
            jmp end_proc_spec_symb		
;-----------------------------------------------
	
finish_printf_:
			
	call print_buf_

	ret	
;%endmacro
; Dtr: rax, rdi, rdx = 0, r10, r11, rbx = rsi  

print_buf_:
	cmp rdx, 0
	je fin_p_b_ 
	
	xor rax, rax
	xor rdi, rdi
	inc rax
	inc rdi
	
	mov r10, rcx
	xchg rbx, rsi

	syscall
	
	xchg rsi, rbx
	add rbx, rdx

	mov rcx, r10
	
	xor rdx, rdx
		
fin_p_b_:
	ret
