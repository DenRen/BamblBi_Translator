%ifndef MY_STD_MACRO_
%define MY_STD_MACRO_

endl 	equ 0x0		; End of line
brkl	equ 0xA		; Line break
finl 	equ 0xA 	; Line break and end of line

%macro strlen 0
	cld
	mov al, 0
	xor rcx, rcx
	dec rcx
	repnz scasb
	sub rcx, 0xFFFFFFFFFFFFFFFF
	neg rcx
	dec rcx
%endmacro

%macro prog_start 0
	
	xor rax, rax	
	xor rdi, rdi
	inc al			; RAX = 1	; write64
	inc dil			; RDI = 1	; stdout
	
	mov   rsi, msg_s_p_			
	movsx rdx, byte [len_s_p_]  
	
	syscall		; Print message about of finish program

%endmacro

%macro prog_finish 0
			
	xor rax, rax	
	xor rdi, rdi
	inc al			; RAX = 1	; write64
	inc di			; RDI = 1	; stdout
	
	mov   rsi, msg_f_p_			
	movsx rdx, byte [len_f_p_]
	
	syscall			; Print message about of finish program
	
	mov rax, 0x3C
	xor rdi, rdi	; RBX = 0	; Exit
		
	syscall			; Finish program	
	
%endmacro

msg_s_p_ db "The program started", finl				; Start program message
len_s_p_ db $ - msg_s_p_ 
msg_f_p_ db "The program ended without errors", finl; Finish program message
len_f_p_ db $ - msg_f_p_

%endif
