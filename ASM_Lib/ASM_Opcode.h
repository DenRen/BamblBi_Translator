//
// Created by tester on 19.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_ASM_OPCODE_H
#define BAMBLBI_TRANSLATOR_ASM_OPCODE_H

// TODO rewrite in 64

// [MOV]----------------------------------------------------------------------------------------------------------------

//                                         Opcode	    Mnemonic	        Description
#define movrm8_r8           0x88            // 88 /r	MOV r/m8,  r8	    Move r8 to r/m8.
#define movrm16_r16         0x89            // 89 /r	MOV r/m16, r16	    Move r16 to r/m16.
#define movrm32_r32         movrm16_r16     // 89 /r	MOV r/m32, r32	    Move r32 to r/m32.
#define movrm64_r64         movrm16_r16     // 89 /r	MOV r/m64, r64	    Move r64 to r/m64.

#define movr8_rm8           0x8a            // 8A /r	MOV r8,  r/m8	    Move r/m8 to r8.
#define movr16_rm16         0x8b            // 8B /r	MOV r16, r/m16	    Move r/m16 to r16.
#define movr32_rm32         movr16_rm16     // 8B /r	MOV r32, r/m32	    Move r/m32 to r32.
#define movr64_rm64         movr16_rm16     // 8B /r	MOV r64, r/m64	    Move r/m64 to r64.

#define movrm8_sr           0x8c            // 8C /r	MOV r/m16, Sreg**	Move segment register to r/m16.
#define movsr_rm8           0x8e            // 8E /r	MOV Sreg, r/m16**	Move r/m16 to segment register.

#define movr8_moffs8        0xa0            // A0	    MOV AL, moffs8*	    Move byte at (seg:offset) to AL.
#define movr16_moffs16      0xa1            // A1	    MOV AX, moffs16*	Move word at (seg:offset) to AX.
#define movr32_moffs32      0xa1            // A1	    MOV EAX, moffs32*	Move dword at (seg:offset) to EAX.

#define movmoffs8_r8        0xa2            // A2	    MOV moffs8*, AL	    Move AL to (seg:offset).
#define movmoffs16_r16      0xa3            // A3	    MOV moffs16*, AX	Move AX to (seg:offset).
#define movmoffs32_r32      0xa3            // A3	    MOV moffs32*, EAX	Move EAX to (seg:offset).

#define movr8_i8            0x88            // B0+ rb	MOV r8, imm8	    Move imm8 to r8.
#define movr16_i16          0x89            // B8+ rw	MOV r16, imm16	    Move imm16 to r16.
#define movr32_i32          movrm16_r16     // B8+ rd	MOV r32, imm32	    Move imm32 to r32.
#define movr64_i64          movrm16_r16     // B8+ rd	MOV r32, imm32	    Move imm32 to r32.

#define movrm8_i8           0x8a            // C6 /0	MOV r/m8, imm8	    Move imm8 to r/m8.
#define movrm16_i16         0x8b            // C7 /0	MOV r/m16, imm16	Move imm16 to r/m16.
#define movrm32_i32         movr16_rm16     // C7 /0	MOV r/m32, imm32	Move imm32 to r/m32.
#define movrm64_i64         movr16_rm16     // C7 /0	MOV r/m32, imm32	Move imm32 to r/m32.

// [ADD]----------------------------------------------------------------------------------------------------------------

#define addr8_i8            0x04      // 04 ib	    ADD AL,    imm8	    Add imm8 to AL
#define addr16_i16          0x05      // 05 iw	    ADD AX,    imm16	Add imm16 to AX
#define addr32_i32          0x05      // 05 id	    ADD EAX,   imm32	Add imm32 to EAX
#define addr64_i64          0x05      // 05 id	    ADD RAX,   imm64	Add imm32 to EAX

#define addrm8_i8           0x80      // 80 /0 ib	ADD r/m8,  imm8	    Add imm8 to r/m8
#define addrm16_i16         0x81      // 81 /0 iw	ADD r/m16, imm16	Add imm16 to r/m16
#define addrm32_i32         0x81      // 81 /0 id	ADD r/m32, imm32	Add imm32 to r/m32
#define addrm64_i64         0x81      // 81 /0 id	ADD r/m32, imm32	Add imm32 to r/m32

#define addrm16_i16_se      0x83      // 83 /0 ib	ADD r/m16, imm8	    Add sign-extended imm8 to r/m16
#define addrm32_i32_se      0x83      // 83 /0 ib	ADD r/m32, imm8	    Add sign-extended imm8 to r/m32
#define addrm64_i64_se      0x83      // 83 /0 ib	ADD r/m32, imm8	    Add sign-extended imm8 to r/m32

#define addrm8_r8           0x00      // 00 /r	    ADD r/m8,  r8	    Add r8 to r/m8
#define addrm16_r16         0x01      // 01 /r	    ADD r/m16, r16	    Add r16 to r/m16
#define addrm32_r32         0x01      // 01 /r	    ADD r/m32, r32	    Add r32 to r/m32
#define addrm64_r64         0x01      // 01 /r	    ADD r/m32, r32	    Add r32 to r/m32

#define addr8_r8            0x02      // 02 /r	    ADD r8,  r/m8	    Add r/m8 to r8
#define addr16_r16          0x03      // 03 /r	    ADD r16, r/m16	    Add r/m16 to r16
#define addr32_r32          0x03      // 03 /r	    ADD r32, r/m32	    Add r/m32 to r32
#define addr64_r64          0x03      // 03 /r	    ADD r32, r/m32	    Add r/m32 to r32

// [SUB]----------------------------------------------------------------------------------------------------------------

#define subr8_i8            0x2c      // 2C ib	    SUB AL,    imm8	    Subtract imm8  from AL
#define subr16_i16          0x2d      // 2D iw	    SUB AX,    imm16	Subtract imm16 from AX
#define subr32_i32          0x2d      // 2D id	    SUB EAX,   imm32	Subtract imm32 from EAX
#define subr64_i64          0x2d      // 2D id	    SUB EAX,   imm32	Subtract imm32 from EAX

#define subrm8_i8           0x8028    // 80 /5 ib	SUB r/m8,  imm8	    Subtract imm8  from r/m8
#define subrm16_i16         0x8128    // 81 /5 iw	SUB r/m16, imm16	Subtract imm16 from r/m16
#define subrm32_i32         0x8128    // 81 /5 id	SUB r/m32, imm32	Subtract imm32 from r/m32
#define subrm64_i64         0x8128    // 81 /5 id	SUB r/m32, imm32	Subtract imm32 from r/m32

#define subrm16_i16_se      0x8328    // 83 /5 ib	SUB r/m16, imm8	    Subtract sign-extended imm8 from r/m16
#define subrm32_i32_se      0x8328    // 83 /5 ib	SUB r/m32, imm8	    Subtract sign-extended imm8 from r/m32
#define subrm64_i64_se      0x8328    // 83 /5 ib	SUB r/m32, imm8	    Subtract sign-extended imm8 from r/m32

#define subrm8_r8           0x00      // 28 /r	    SUB r/m8,  r8	    Subtract r8  from r/m8
#define subrm16_r16         0x01      // 29 /r	    SUB r/m16, r16	    Subtract r16 from r/m16
#define subrm32_r32         0x01      // 29 /r	    SUB r/m32, r32	    Subtract r32 from r/m32
#define subrm64_r64         0x01      // 29 /r	    SUB r/m32, r32	    Subtract r32 from r/m32

#define subr8_r8            0x2a      // 2A /r	    SUB r8,    r/m8	    Subtract r/m8  from r8
#define subr16_r16          0x2b      // 2B /r	    SUB r16,   r/m16	Subtract r/m16 from r16
#define subr32_r32          0x2b      // 2B /r	    SUB r32,   r/m32	Subtract r/m32 from r32
#define subr64_r64          0x2b      // 2B /r	    SUB r32,   r/m32	Subtract r/m32 from r32

// [MUL]----------------------------------------------------------------------------------------------------------------

#define mulrm8              0xf620    // F6 /4	MUL r/m8	Unsigned multiply (AX = AL * r/m8).
#define mulrm16             0xf720    // F7 /4	MUL r/m16	Unsigned multiply (DX:AX = AX * r/m16).
#define mulrm32             0xf720    // F7 /4	MUL r/m32	Unsigned multiply (EDX:EAX = EAX * r/m32)
#define mulrm64             0xf720    // F7 /4	MUL r/m32	Unsigned multiply (EDX:EAX = EAX * r/m32)


// [DIV]----------------------------------------------------------------------------------------------------------------

#define divrm8              0xf630    // F6 /6	DIV r/m8	Unsigned divide AX by r/m8, with result stored in AL = Quotient, AH = Remainder
#define divrm16             0xf730    // F7 /6	DIV r/m16	Unsigned divide DX:AX by r/m16, with result stored in AX = Quotient, DX = Remainder
#define divrm32             0xf730    // F7 /6	DIV r/m32	Unsigned divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder
#define divrm64             0xf730    // F7 /6	DIV r/m32	Unsigned divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder

// [IMUL]----------------------------------------------------------------------------------------------------------------

#define imulrm8             0xf628      // F6 /5	IMUL r/m8	            AX = AL * r/m byte
#define imulrm16            0xf728      // F7 /5	IMUL r/m16	            DX:AX = AX * r/m word
#define imulrm32            0xf728      // F7 /5	IMUL r/m32	            EDX:EAX = EAX * r/m doubleword
#define imulrm64            0xf728      // F7 /5	IMUL r/m32	            EDX:EAX = EAX * r/m doubleword

#define imulr_rm16          0x0faf      // 0F AF /r	IMUL r16, r/m16	        word register = word register * r/m word
#define imulr_rm32          0x0faf      // 0F AF /r	IMUL r32, r/m32	        doubleword register = doubleword register * r/m doubleword
#define imulr_rm64          0x0faf      // 0F AF /r	IMUL r32, r/m32	        doubleword register = doubleword register * r/m doubleword

#define imulr16_i8          0x6b        // 6B /r ib	IMUL r16, r/m16, imm8	word register = r/m16 * sign-extended immediate byte
#define imulr32_i8          0x6b        // 6B /r ib	IMUL r32, r/m32, imm8	doubleword register = r/m32 * sign-extended immediate byte
#define imulr64_i8          0x6b        // 6B /r ib	IMUL r32, r/m32, imm8	doubleword register = r/m32 * sign-extended immediate byte

#define imulr_rm_i16        0x69        // 69 /r iw	IMUL r16, r/m16, imm16	word register = r/m16 * immediate word
#define imulr_rm_i32        0x69        // 69 /r id	IMUL r32, r/m32, imm32	doubleword register = r/m32 * immediate doubleword
#define imulr_rm_i64        0x69        // 69 /r id	IMUL r32, r/m32, imm32	doubleword register = r/m32 * immediate doubleword

#define imulr_i16           0x69        // 69 /r iw	IMUL r16, imm16	        word register = r/m16 * immediate word
#define imulr_i32           0x69        // 69 /r id	IMUL r32, imm32	        doubleword register = r/m32 * immediate doubleword
#define imulr_i64           0x69        // 69 /r id	IMUL r32, imm32	        doubleword register = r/m32 * immediate doubleword

// [IDIV]----------------------------------------------------------------------------------------------------------------

#define idivrm8             0xf638      // F6 /7	IDIV r/m8       Signed divide AX by r/m8, with result stored in AL = Quotient, AH = Remainder
#define idivrm16            0xf738      // F7 /7	IDIV r/m16      Signed divide DX:AX by r/m16, with result stored in AX = Quotient, DX = Remainder
#define idivrm32            0xf738      // F7 /7	IDIV r/m32      Signed divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder
#define idivrm64            0xf738      // F7 /7	IDIV r/m32      Signed divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder

// TODO XOR, OR, AND, NOT, NEG, INC, DEC

// [Jcc]----------------------------------------------------------------------------------------------------------------

#define ja_s        0x77        // 77 cb	JA rel8	J   ump short if above (CF=0 and ZF=0)
#define jae_s       0x73        // 73 cb	JAE rel8	Jump short if above or equal (CF=0)
#define jb_s        0x72        // 72 cb	JB rel8	    Jump short if below (CF=1)
#define jbe_s       0x76        // 76 cb	JBE rel8	Jump short if below or equal (CF=1 or ZF=1)
#define jc_s        0x72        // 72 cb	JC rel8	    Jump short if carry (CF=1)
#define jcxz_s      0xe3        // E3 cb	JCXZ rel8	Jump short if CX register is 0
#define jecxz_s     0xe3        // E3 cb	JECXZ rel8	Jump short if ECX register is 0
#define je_s        0x74        // 74 cb	JE rel8	    Jump short if equal (ZF=1)
#define jg_s        0x7f        // 7F cb	JG rel8	    Jump short if greater (ZF=0 and SF=OF)
#define jge_s       0x7d        // 7D cb	JGE rel8	Jump short if greater or equal (SF=OF)
#define jl_s        0x7c        // 7C cb	JL rel8	    Jump short if less (SF<>OF)
#define jle_s       0x7e        // 7E cb	JLE rel8	Jump short if less or equal (ZF=1 or SF<>OF)
#define jna_s       0x76        // 76 cb	JNA rel8	Jump short if not above (CF=1 or ZF=1)
#define jnae_s      0x72        // 72 cb	JNAE rel8	Jump short if not above or equal (CF=1)
#define jnb_s       0x73        // 73 cb	JNB rel8	Jump short if not below (CF=0)
#define jnbe_s      0x77        // 77 cb	JNBE rel8	Jump short if not below or equal (CF=0 and ZF=0)
#define jnc_s       0x73        // 73 cb	JNC rel8	Jump short if not carry (CF=0).
#define jne_s       0x75        // 75 cb	JNE rel8	Jump short if not equal (ZF=0)
#define jng_s       0x7e        // 7E cb	JNG rel8	Jump short if not greater (ZF=1 or SF<>OF)
#define jnge_s      0x7c        // 7C cb	JNGE rel8	Jump short if not greater or equal (SF<>OF)
#define jnl_s       0x7d        // 7D cb	JNL rel8	Jump short if not less (SF=OF)
#define jnle_s      0x7f        // 7F cb	JNLE rel8	Jump short if not less or equal (ZF=0 and SF=OF)
#define jno_s       0x71        // 71 cb	JNO rel8	Jump short if not overflow (OF=0)
#define jnp_s       0x7b        // 7B cb	JNP rel8	Jump short if not parity (PF=0)
#define jns_s       0x79        // 79 cb	JNS rel8	Jump short if not sign (SF=0)
#define jnz_s       0x75        // 75 cb	JNZ rel8	Jump short if not zero (ZF=0)
#define jo_s        0x70        // 70 cb	JO rel8	    Jump short if overflow (OF=1)
#define jp_s        0x7a        // 7A cb	JP rel8	    Jump short if parity (PF=1)
#define jpe_s       0x7a        // 7A cb	JPE rel8	Jump short if parity even (PF=1)
#define jpo_s       0x7b        // 7B cb	JPO rel8	Jump short if parity odd (PF=0)
#define js_s        0x78        // 78 cb	JS rel8	    Jump short if sign (SF=1).0
#define jz_s        0x74        // 74 cb	JZ rel8	    Jump short if zero (ZF = 1)

#define ja_n        0x0f87      // 0F 87 cw/cd	JA rel16/32	    Jump near if above (CF=0 and ZF=0)
#define jae         0x0f83      // 0F 83 cw/cd	JAE rel16/32	Jump near if above or equal (CF=0)
#define jb_n        0x0f82      // 0F 82 cw/cd	JB rel16/32	    Jump near if below (CF=1)
#define jbe_n       0x0f86      // 0F 86 cw/cd	JBE rel16/32	Jump near if below or equal (CF=1 or ZF=1)
#define jc_n        0x0f82      // 0F 82 cw/cd	JC rel16/32	    Jump near if carry (CF=1)
#define jcxz_n      0x0f84      // 0F 84 cw/cd	JE rel16/32	    Jump near if equal (ZF=1)
#define jecxz_n     0x0f84      // 0F 84 cw/cd	JZ rel16/32	    Jump near if 0 (ZF=1)
#define je_n        0x0f8f      // 0F 8F cw/cd	JG rel16/32	    Jump near if greater (ZF=0 and SF=OF)
#define jg_n        0x0f8d      // 0F 8D cw/cd	JGE rel16/32	Jump near if greater or equal (SF=OF)
#define jge_n       0x0f8c      // 0F 8C cw/cd	JL rel16/32	    Jump near if less (SF<>OF)
#define jl_n        0x0f8e      // 0F 8E cw/cd	JLE rel16/32	Jump near if less or equal (ZF=1 or SF<>OF)
#define jle_n       0x0f86      // 0F 86 cw/cd	JNA rel16/32	Jump near if not above (CF=1 or ZF=1)
#define jna_n       0x0f82      // 0F 82 cw/cd	JNAE rel16/32	Jump near if not above or equal (CF=1)
#define jnae_n      0x0f83      // 0F 83 cw/cd	JNB rel16/32	Jump near if not below (CF=0)
#define jnb_n       0x0f87      // 0F 87 cw/cd	JNBE rel16/32	Jump near if not below or equal (CF=0 and ZF=0)
#define jnbe_n      0x0f83      // 0F 83 cw/cd	JNC rel16/32	Jump near if not carry (CF=0)
#define jnc_n       0x0f85      // 0F 85 cw/cd	JNE rel16/32	Jump near if not equal (ZF=0)
#define jne_n       0x0f8e      // 0F 8E cw/cd	JNG rel16/32	Jump near if not greater (ZF=1 or SF<>OF)
#define jng_n       0x0f8c      // 0F 8C cw/cd	JNGE rel16/32	Jump near if not greater or equal (SF<>OF)
#define jnge_n      0x0f8d      // 0F 8D cw/cd	JNL rel16/32	Jump near if not less (SF=OF)
#define jnl_n       0x0f8f      // 0F 8F cw/cd	JNLE rel16/32	Jump near if not less or equal (ZF=0 and SF=OF)
#define jnle_n      0x0f81      // 0F 81 cw/cd	JNO rel16/32	Jump near if not overflow (OF=0)
#define jno_n       0x0f8b      // 0F 8B cw/cd	JNP rel16/32	Jump near if not parity (PF=0)
#define jnp_n       0x0f89      // 0F 89 cw/cd	JNS rel16/32	Jump near if not sign (SF=0)
#define jns_n       0x0f85      // 0F 85 cw/cd	JNZ rel16/32	Jump near if not zero (ZF=0)
#define jnz_n       0x0f80      // 0F 80 cw/cd	JO rel16/32	    Jump near if overflow (OF=1)
#define jo_n        0x0f8a      // 0F 8A cw/cd	JP rel16/32	    Jump near if parity (PF=1)
#define jp_n        0x0f8a      // 0F 8A cw/cd	JPE rel16/32	Jump near if parity even (PF=1)
#define jpe_n       0x0f8b      // 0F 8B cw/cd	JPO rel16/32	Jump near if parity odd (PF=0)
#define jpo_n       0x0f88      // 0F 88 cw/cd	JS rel16/32	    Jump near if sign (SF=1)
#define js_n        0x0f84      // 0F 84 cw/cd	JZ rel16/32	    Jump near if 0 (ZF=1)

// [JMP]----------------------------------------------------------------------------------------------------------------

#define jmp_rel8	    0xeb       // EB cb	JMP rel8	Jump short, relative, displacement relative to next instruction.
#define jmp_rel16	    0xe9       // E9 cw	JMP rel16	Jump near, relative, displacement relative to next instruction.
#define jmp_rel32	    0xe9       // E9 cd	JMP rel32	Jump near, relative, displacement relative to next instruction.
#define jmp_rm16	    0xff20     // FF /4	JMP r/m16	Jump near, absolute indirect, address given in r/m16.
#define jmp_rm32	    0xff20     // FF /4	JMP r/m32	Jump near, absolute indirect, address given in r/m32.
#define jmp_ptr16_16    0xea       // EA cd	JMP ptr16:16	Jump far, absolute, address given in operand.
#define jmp_ptr16_32    0xea       // EA cp	JMP ptr16:32	Jump far, absolute, address given in operand.
#define jmp_m16_16	    0xff28     // FF /5	JMP m16:16	Jump far, absolute indirect, address given in m16:16.
#define jmp_m16_32	    0xff28     // FF /5	JMP m16:32	Jump far, absolute indirect, address given in m16:32.


// [RET]----------------------------------------------------------------------------------------------------------------

#define ret_near        0xc3       // C3	    RET	Near return to calling procedure.
#define ret_far 0xcb    CB	       // RET	    Far return to calling procedure.
#define ret_ni16 0xc2   C2 iw	   // RET imm16	Near return to calling procedure and pop imm16 bytes from stack.
#define ret_nf16 0xca   CA iw	   // RET imm16	Far return to calling procedure and pop imm16 bytes from stack.

// [PUSH]---------------------------------------------------------------------------------------------------------------

#define push_rm16       0xff30     // FF /6	    Push r/m16
#define push_rm32       0xff30     // FF /6	    Push r/m32
#define push_r16        0x50       // 50+rw	    Push r16
#define push_r32        0x50       // 50+rd	    Push r32
#define push_i8         0x6a       // 6A	    Push imm8
#define push_i16        0x68       // 68	    Push imm16
#define push_i32        0x68       // 68	    Push imm32
#define push_cs         0x0e       // 0E	    Push CS
#define push_ss         0x16       // 16	    Push SS
#define push_ds         0x1e       // 1E	    Push DS
#define push_es         0x06       // 06	    Push ES
#define push_fs         0x0f       // 0F A0	    Push FS
#define push_gs         0x0f       // 0F A8	    Push GS

// [PUSH]---------------------------------------------------------------------------------------------------------------

#define pop_m16         0x8f       // 8F /0		Pop top of stack into m16; increment stack pointer.
#define pop_m32         0x8f       // 8F /0		Pop top of stack into m32; increment stack pointer.
#define pop_m64         0x8f       // 8F /0		Pop top of stack into m64; increment stack pointer.

#define pop_r16         0x58       // 58+ rw    Pop top of stack into r16; increment stack pointer.
#define pop_r32         0x58       // 58+ rd    Pop top of stack into r32; increment stack pointer.
#define pop_r64         0x58       // 58+ rd    Pop top of stack into r32; increment stack pointer.

#define pop_ds          0x1f       // 1F	    Pop top of stack into DS; increment stack pointer.
#define pop_es          0x07       // 07	    Pop top of stack into ES; increment stack pointer.
#define pop_ss          0x17       // 17	    Pop top of stack into SS; increment stack pointer.
#define pop_fs          0x0fa1     // 0F A1	    Pop top of stack into FS; increment stack pointer.
#define pop_gs          0x0fa9     // 0F A9	    Pop top of stack into GS; increment stack pointer.

// [PUSH]---------------------------------------------------------------------------------------------------------------
// [PUSH]---------------------------------------------------------------------------------------------------------------
// [PUSH]---------------------------------------------------------------------------------------------------------------

#endif //BAMBLBI_TRANSLATOR_ASM_OPCODE_H
