//
// Created by tester on 19.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_ASM_OPCODE_H
#define BAMBLBI_TRANSLATOR_ASM_OPCODE_H

// TODO ????????? ?? 64

// [MOV]----------------------------------------------------------------------------------------------------------------

//                                         Opcode	Mnemonic	        Description
#define movrm8_r8       0x88            // 88 /r	MOV r/m8,  r8	    Move r8 to r/m8.
#define movrm16_r16     0x89            // 89 /r	MOV r/m16, r16	    Move r16 to r/m16.
#define movrm32_r32     movrm16_r16     // 89 /r	MOV r/m32, r32	    Move r32 to r/m32.
#define movrm64_r64     movrm16_r16     // 89 /r	MOV r/m64, r64	    Move r64 to r/m64.

#define movr8_rm8       0x8a            // 8A /r	MOV r8,  r/m8	    Move r/m8 to r8.
#define movr16_rm16     0x8b            // 8B /r	MOV r16, r/m16	    Move r/m16 to r16.
#define movr32_rm32     movr16_rm16     // 8B /r	MOV r32, r/m32	    Move r/m32 to r32.
#define movr64_rm64     movr16_rm16     // 8B /r	MOV r64, r/m64	    Move r/m64 to r64.

#define movrm8_sr       0x8c            // 8C /r	MOV r/m16, Sreg**	Move segment register to r/m16.
#define movsr_rm8       0x8e            // 8E /r	MOV Sreg, r/m16**	Move r/m16 to segment register.

#define movr8_moffs8    0xa0            // A0	    MOV AL, moffs8*	    Move byte at (seg:offset) to AL.
#define movr16_moffs16  0xa1            // A1	    MOV AX, moffs16*	Move word at (seg:offset) to AX.
#define movr32_moffs32  0xa1            // A1	    MOV EAX, moffs32*	Move dword at (seg:offset) to EAX.

#define movmoffs8_r8    0xa2            // A2	    MOV moffs8*, AL	    Move AL to (seg:offset).
#define movmoffs16_r16  0xa3            // A3	    MOV moffs16*, AX	Move AX to (seg:offset).
#define movmoffs32_r32  0xa3            // A3	    MOV moffs32*, EAX	Move EAX to (seg:offset).

#define movr8_i8       0x88            // B0+ rb	MOV r8, imm8	    Move imm8 to r8.
#define movr16_i16     0x89            // B8+ rw	MOV r16, imm16	    Move imm16 to r16.
#define movr32_i32     movrm16_r16     // B8+ rd	MOV r32, imm32	    Move imm32 to r32.
#define movr64_i64     movrm16_r16     // B8+ rd	MOV r32, imm32	    Move imm32 to r32.

#define movrm8_i8      0x8a            // C6 /0	    MOV r/m8, imm8	    Move imm8 to r/m8.
#define movrm16_i16    0x8b            // C7 /0	    MOV r/m16, imm16	Move imm16 to r/m16.
#define movrm32_i32    movr16_rm16     // C7 /0	    MOV r/m32, imm32	Move imm32 to r/m32.
#define movrm64_i64    movr16_rm16     // C7 /0	    MOV r/m32, imm32	Move imm32 to r/m32.

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

// []----------------------------------------------------------------------------------------------------------------


#endif //BAMBLBI_TRANSLATOR_ASM_OPCODE_H
