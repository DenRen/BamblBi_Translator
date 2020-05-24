//
// Created by tester on 20.05.2020.
//
//
// Created by tester on 19.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_ASM_OPCODE_H
#define BAMBLBI_TRANSLATOR_ASM_OPCODE_H


// To beuat
// TODO rewrite in 64
// TODO XOR, OR, AND, NOT, NEG, INC, DEC, NOP

// [MOV]----------------------------------------------------------------------------------------------------------------

//                                         Opcode	    Mnemonic	        Description

#include <zconf.h>
#include "ASM_Opcode.h"

namespace opcode {
    const __uint8_t max_len_name_cmd = 16;

    struct __cmd {                            // Filling with end

        __uint32_t opcode;
        __uint8_t size;
        bool ext;

        __cmd () :
            opcode (0),
            size   (0),
            ext    (false)
        {};

        __cmd (__uint32_t opcode, __uint8_t size, bool ext = false) :
                opcode (opcode),
                size (size),
                ext (ext)
        {}
    };

    enum _cmds {
        MOV,
        ADD, SUB,
        MUL, DIV, IMUL, IDIV,
        PUSH, POP,
        RET,

        JMP,
        JA,     JAE,    JB,     JBE,    JC,     JCXZ,   JECXZ,   JE,
        JG,     JGE,    JL,     JLE,    JNA,    JNAE,   JNB,    JNBE,
        JNC,    JNE,    JNG,    JNGE,   JNL,    JNLE,   JNO,    JNP,
        JNS,    JNZ,    JO,     JP,     JPE,    JPO,    JS,     JZ,

        __Quantity_Types_Commands
    };

    extern char _name_cmds [__Quantity_Types_Commands][max_len_name_cmd];

    // [MOV]----------------------------------------------------------------------------------------------------------------
    namespace mov {
        extern __cmd rm8_r8;      // 88 /r	MOV r/m8,  r8	    Move r8 to r/m8.
        extern __cmd rm16_r16;      // 89 /r	MOV r/m16, r16	    Move r16 to r/m16.
        extern __cmd rm32_r32;      // 89 /r	MOV r/m32, r32	    Move r32 to r/m32.
        extern __cmd rm64_r64;      // 89 /r	MOV r/m64, r64	    Move r64 to r/m64.

        extern __cmd r8_rm8;     // 8A /r	MOV r8,  r/m8	    Move r/m8 to r8.
        extern __cmd r16_rm16;      // 8B /r	MOV r16, r/m16	    Move r/m16 to r16.
        extern __cmd r32_rm32;      // 8B /r	MOV r32, r/m32	    Move r/m32 to r32.
        extern __cmd r64_rm64;      // 8B /r	MOV r64, r/m64	    Move r/m64 to r64.

        extern __cmd rm8_sr;      // 8C /r	MOV r/m16, Sreg**	Move segment register to r/m16.
        extern __cmd sr_rm8;      // 8E /r	MOV Sreg, r/m16**	Move r/m16 to segment register.

        extern __cmd r8_moffs8 ;      // A0	    MOV AL, moffs8*	    Move byte at (seg:offset) to AL.
        extern __cmd r16_moffs16;      // A1	    MOV AX, moffs16*	Move word at (seg:offset) to AX.
        extern __cmd r32_moffs32;      // A1	    MOV EAX, moffs32*	Move dword at (seg:offset) to EAX.

        extern __cmd moffs8_r8;      // A2	    MOV moffs8*, AL	    Move AL to (seg:offset).
        extern __cmd moffs16_r16;      // A3	    MOV moffs16*, AX	Move AX to (seg:offset).
        extern __cmd moffs32_r32;      // A3	    MOV moffs32*, EAX	Move EAX to (seg:offset).

        extern __cmd r8_i8;      // B0+ rb	MOV r8, imm8	    Move imm8 to r8.
        extern __cmd r16_i16;      // B8+ rw	MOV r16, imm16	    Move imm16 to r16.
        extern __cmd r32_i32;      // B8+ rd	MOV r32, imm32	    Move imm32 to r32.
        extern __cmd r64_i64;      // B8+ rd	MOV r32, imm32	    Move imm32 to r32.

        extern __cmd rm8_i8;      // C6 /0	MOV r/m8, imm8	    Move imm8 to r/m8.
        extern __cmd rm16_i16;      // C7 /0	MOV r/m16, imm16	Move imm16 to r/m16.
        extern __cmd rm32_i32;      // C7 /0	MOV r/m32, imm32	Move imm32 to r/m32.
        extern __cmd rm64_i64;      // C7 /0	MOV r/m32, imm32	Move imm32 to r/m32.
    }
    // [ADD]----------------------------------------------------------------------------------------------------------------
    namespace add {
        extern __cmd r8_i8;         // 04 ib	    ADD AL,    imm8	    Add imm8 to AL
        extern __cmd r16_i16;       // 05 iw	    ADD AX,    imm16	Add imm16 to AX
        extern __cmd r32_i32;       // 05 id	    ADD EAX,   imm32	Add imm32 to EAX
        extern __cmd r64_i64;       // 05 id	    ADD RAX,   imm64	Add imm32 to EAX

        extern __cmd rm8_i8;        // 80 /0 ib	    ADD r/m8,  imm8	    Add imm8 to r/m8
        extern __cmd rm16_i16;      // 81 /0 iw	    ADD r/m16, imm16	Add imm16 to r/m16
        extern __cmd rm32_i32;      // 81 /0 id	    ADD r/m32, imm32	Add imm32 to r/m32
        extern __cmd rm64_i64;      // 81 /0 id	    ADD r/m32, imm32	Add imm32 to r/m32

        extern __cmd rm16_i16_se;   // 83 /0 ib	    ADD r/m16, imm8	    Add sign-extended imm8 to r/m16
        extern __cmd rm32_i32_se;   // 83 /0 ib	    ADD r/m32, imm8	    Add sign-extended imm8 to r/m32
        extern __cmd rm64_i64_se;   // 83 /0 ib	    ADD r/m32, imm8	    Add sign-extended imm8 to r/m32

        extern __cmd rm8_r8;        // 00 /r	    ADD r/m8,  r8	    Add r8 to r/m8
        extern __cmd rm16_r16;      // 01 /r	    ADD r/m16, r16	    Add r16 to r/m16
        extern __cmd rm32_r32;      // 01 /r	    ADD r/m32, r32	    Add r32 to r/m32
        extern __cmd rm64_r64;      // 01 /r	    ADD r/m32, r32	    Add r32 to r/m32

        extern __cmd r8_rm8;        // 02 /r	    ADD r8,  r/m8	    Add r/m8 to r8
        extern __cmd r16_rm16;      // 03 /r	    ADD r16, r/m16	    Add r/m16 to r16
        extern __cmd r32_rm32;      // 03 /r	    ADD r32, r/m32	    Add r/m32 to r32
        extern __cmd r64_rm64;      // 03 /r	    ADD r32, r/m32	    Add r/m32 to r32
    }
    // [SUB]----------------------------------------------------------------------------------------------------------------
    namespace sub {
        extern __cmd r8_i8;         // 2C ib	    SUB AL,    imm8	    Subtract imm8  from AL
        extern __cmd r16_i16;       // 2D iw	    SUB AX,    imm16	Subtract imm16 from AX
        extern __cmd r32_i32;       // 2D id	    SUB EAX,   imm32	Subtract imm32 from EAX
        extern __cmd r64_i64;       // 2D id	    SUB EAX,   imm32	Subtract imm32 from EAX

        extern __cmd rm8_i8;        // 80 /5 ib	    SUB r/m8,  imm8	    Subtract imm8  from r/m8
        extern __cmd rm16_i16;      // 81 /5 iw	    SUB r/m16, imm16    Subtract imm16 from r/m16
        extern __cmd rm32_i32;      // 81 /5 id	    SUB r/m32, imm32    Subtract imm32 from r/m32
        extern __cmd rm64_i64;      // 81 /5 id	    SUB r/m32, imm32    Subtract imm32 from r/m32

        extern __cmd rm16_i16_se;   // 83 /5 ib	    SUB r/m16, imm8	    Subtract sign-extended imm8 from r/m16
        extern __cmd rm32_i32_se;   // 83 /5 ib	    SUB r/m32, imm8	    Subtract sign-extended imm8 from r/m32
        extern __cmd rm64_i64_se;   // 83 /5 ib	    SUB r/m32, imm8	    Subtract sign-extended imm8 from r/m32

        extern __cmd rm8_r8;        // 28 /r	    SUB r/m8,  r8	    Subtract r8  from r/m8
        extern __cmd rm16_r16;      // 29 /r	    SUB r/m16, r16	    Subtract r16 from r/m16
        extern __cmd rm32_r32;      // 29 /r	    SUB r/m32, r32	    Subtract r32 from r/m32
        extern __cmd rm64_r64;      // 29 /r	    SUB r/m32, r32	    Subtract r32 from r/m32

        extern __cmd r8_rm8;        // 2A /r	    SUB r8,    r/m8	    Subtract r/m8  from r8
        extern __cmd r16_rm16;      // 2B /r	    SUB r16,   r/m16	Subtract r/m16 from r16
        extern __cmd r32_rm32;      // 2B /r	    SUB r32,   r/m32	Subtract r/m32 from r32
        extern __cmd r64_rm64;      // 2B /r	    SUB r32,   r/m32	Subtract r/m32 from r32
    }
    // [MUL]----------------------------------------------------------------------------------------------------------------
    namespace mul {
        extern __cmd rm8;     // F6 /4	MUL r/m8	Unsigned multiply (AX = AL * r/m8).
        extern __cmd rm16;    // F7 /4	MUL r/m16	Unsigned multiply (DX:AX = AX * r/m16).
        extern __cmd rm32;    // F7 /4	MUL r/m32	Unsigned multiply (EDX:EAX = EAX * r/m32)
        extern __cmd rm64;    // F7 /4	MUL r/m32	Unsigned multiply (EDX:EAX = EAX * r/m32)
    }
    // [DIV]----------------------------------------------------------------------------------------------------------------
    namespace div {
        extern __cmd rm8;    // F6 /6	DIV r/m8	Unsigned divide AX by r/m8, with result stored in AL = Quotient, AH = Remainder
        extern __cmd rm16;   // F7 /6	DIV r/m16	Unsigned divide DX:AX by r/m16, with result stored in AX = Quotient, DX = Remainder
        extern __cmd rm32;   // F7 /6	DIV r/m32	Unsigned divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder
        extern __cmd rm64;   // F7 /6	DIV r/m32	Unsigned divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder
    }
    // [IMUL]----------------------------------------------------------------------------------------------------------------
    namespace imul {
        extern __cmd rm8;       // F6 /5	IMUL r/m8	            AX = AL * r/m byte
        extern __cmd rm16;      // F7 /5	IMUL r/m16	            DX:AX = AX * r/m word
        extern __cmd rm32;      // F7 /5	IMUL r/m32	            EDX:EAX = EAX * r/m doubleword
        extern __cmd rm64;      // F7 /5	IMUL r/m32	            EDX:EAX = EAX * r/m doubleword

        extern __cmd r_rm16;    // 0F AF /r	IMUL r16, r/m16	        word register = word register * r/m word
        extern __cmd r_rm32;    // 0F AF /r	IMUL r32, r/m32	        doubleword register = doubleword register * r/m doubleword
        extern __cmd r_rm64;    // 0F AF /r	IMUL r32, r/m32	        doubleword register = doubleword register * r/m doubleword

        extern __cmd r16_rm_i8; // 6B /r ib	IMUL r16, r/m16, imm8	word register = r/m16 * sign-extended immediate byte
        extern __cmd r32_rm_i8; // 6B /r ib	IMUL r32, r/m32, imm8	doubleword register = r/m32 * sign-extended immediate byte
        extern __cmd r64_rm_i8; // 6B /r ib	IMUL r32, r/m32, imm8	doubleword register = r/m32 * sign-extended immediate byte

        extern __cmd r16_i8;    // 6B /r ib	IMUL r16, r/m16, imm8	word register = r/m16 * sign-extended immediate byte
        extern __cmd r32_i8;    // 6B /r ib	IMUL r32, r/m32, imm8	doubleword register = r/m32 * sign-extended immediate byte
        extern __cmd r64_i8;    // 6B /r ib	IMUL r32, r/m32, imm8	doubleword register = r/m32 * sign-extended immediate byte

        extern __cmd r_rm_i16;  // 69 /r iw	IMUL r16, r/m16, imm16	word register = r/m16 * immediate word
        extern __cmd r_rm_i32;  // 69 /r id	IMUL r32, r/m32, imm32	doubleword register = r/m32 * immediate doubleword
        extern __cmd r_rm_i64;  // 69 /r id	IMUL r32, r/m32, imm32	doubleword register = r/m32 * immediate doubleword

        extern __cmd r_i16;     // 69 /r iw	IMUL r16, imm16	        word register = r/m16 * immediate word
        extern __cmd r_i32 ;    // 69 /r id	IMUL r32, imm32	        doubleword register = r/m32 * immediate doubleword
        extern __cmd r_i64;     // 69 /r id	IMUL r32, imm32	        doubleword register = r/m32 * immediate doubleword
    }
    // [IDIV]----------------------------------------------------------------------------------------------------------------
    namespace idiv {
        extern __cmd rm8 ;      // F6 /7	IDIV r/m8       Signed divide AX by r/m8, with result stored in AL = Quotient, AH = Remainder
        extern __cmd rm16;      // F7 /7	IDIV r/m16      Signed divide DX:AX by r/m16, with result stored in AX = Quotient, DX = Remainder
        extern __cmd rm32;      // F7 /7	IDIV r/m32      Signed divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder
        extern __cmd rm64;      // F7 /7	IDIV r/m32      Signed divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder
    }
    // [Jcc]----------------------------------------------------------------------------------------------------------------
    namespace jcc {
        extern __cmd ja_s;          // 77 cb	JA rel8	J           Jump short if above (CF=0 and ZF=0)
        extern __cmd jae_s;         // 73 cb	JAE rel8	        Jump short if above or equal (CF=0)
        extern __cmd jb_s;          // 72 cb	JB rel8	            Jump short if below (CF=1)
        extern __cmd jbe_s;         // 76 cb	JBE rel8	        Jump short if below or equal (CF=1 or ZF=1)
        extern __cmd jc_s;          // 72 cb	JC rel8	            Jump short if carry (CF=1)
        extern __cmd jcxz_s;        // E3 cb	JCXZ rel8	        Jump short if CX register is 0
        extern __cmd jecxz_s;       // E3 cb	JECXZ rel8	        Jump short if ECX register is 0
        extern __cmd je_s;          // 74 cb	JE rel8	            Jump short if equal (ZF=1)
        extern __cmd jg_s;          // 7F cb	JG rel8	            Jump short if greater (ZF=0 and SF=OF)
        extern __cmd jge_s;         // 7D cb	JGE rel8	        Jump short if greater or equal (SF=OF)
        extern __cmd jl_s;          // 7C cb	JL rel8	            Jump short if less (SF<>OF)
        extern __cmd jle_s;         // 7E cb	JLE rel8	        Jump short if less or equal (ZF=1 or SF<>OF)
        extern __cmd jna_s;         // 76 cb	JNA rel8	        Jump short if not above (CF=1 or ZF=1)
        extern __cmd jnae_s;        // 72 cb	JNAE rel8	        Jump short if not above or equal (CF=1)
        extern __cmd jnb_s;         // 73 cb	JNB rel8	        Jump short if not below (CF=0)
        extern __cmd jnbe_s;        // 77 cb	JNBE rel8	        Jump short if not below or equal (CF=0 and ZF=0)
        extern __cmd jnc_s;         // 73 cb	JNC rel8	        Jump short if not carry (CF=0).
        extern __cmd jne_s;         // 75 cb	JNE rel8	        Jump short if not equal (ZF=0)
        extern __cmd jng_s;         // 7E cb	JNG rel8	        Jump short if not greater (ZF=1 or SF<>OF)
        extern __cmd jnge_s;        // 7C cb	JNGE rel8	        Jump short if not greater or equal (SF<>OF)
        extern __cmd jnl_s;         // 7D cb	JNL rel8	        Jump short if not less (SF=OF)
        extern __cmd jnle_s;        // 7F cb	JNLE rel8	        Jump short if not less or equal (ZF=0 and SF=OF)
        extern __cmd jno_s;         // 71 cb	JNO rel8	        Jump short if not overflow (OF=0)
        extern __cmd jnp_s;         // 7B cb	JNP rel8	        Jump short if not parity (PF=0)
        extern __cmd jns_s;         // 79 cb	JNS rel8	        Jump short if not sign (SF=0)
        extern __cmd jnz_s;         // 75 cb	JNZ rel8	        Jump short if not zero (ZF=0)
        extern __cmd jo_s;          // 70 cb	JO rel8	            Jump short if overflow (OF=1)
        extern __cmd jp_s;          // 7A cb	JP rel8	            Jump short if parity (PF=1)
        extern __cmd jpe_s;         // 7A cb	JPE rel8	        Jump short if parity even (PF=1)
        extern __cmd jpo_s;         // 7B cb	JPO rel8	        Jump short if parity odd (PF=0)
        extern __cmd js_s;          // 78 cb	JS rel8	            Jump short if sign (SF=1).0
        extern __cmd jz_s;          // 74 cb	JZ rel8	            Jump short if zero (ZF = 1)

        extern __cmd ja_n;          // 0F 87 cw/cd	JA rel16/32	    Jump near if above (CF=0 and ZF=0).
        extern __cmd jae_n;         // 0F 83 cw/cd	JAE rel16/32	Jump near if above or equal (CF=0).
        extern __cmd jb_n;          // 0F 82 cw/cd	JB rel16/32	    Jump near if below (CF=1).
        extern __cmd jbe_n;         // 0F 86 cw/cd	JBE rel16/32	Jump near if below or equal (CF=1 or ZF=1).
        extern __cmd jc_n;          // 0F 82 cw/cd	JC rel16/32	    Jump near if carry (CF=1).
        extern __cmd je_n;          // 0F 84 cw/cd	JE rel16/32	    Jump near if equal (ZF=1).
        extern __cmd jz_n;          // 0F 84 cw/cd	JZ rel16/32	    Jump near if 0 (ZF=1).
        extern __cmd jg_n;          // 0F 8F cw/cd	JG rel16/32	    Jump near if greater (ZF=0 and SF=OF).
        extern __cmd jge_n;         // 0F 8D cw/cd	JGE rel16/32	Jump near if greater or equal (SF=OF).
        extern __cmd jl_n;          // 0F 8C cw/cd	JL rel16/32	    Jump near if less (SF<>OF).
        extern __cmd jle_n;         // 0F 8E cw/cd	JLE rel16/32	Jump near if less or equal (ZF=1 or SF<>OF).
        extern __cmd jna_n;         // 0F 86 cw/cd	JNA rel16/32	Jump near if not above (CF=1 or ZF=1).
        extern __cmd jnae_n;        // 0F 82 cw/cd	JNAE rel16/32	Jump near if not above or equal (CF=1).
        extern __cmd jnb_n;         // 0F 83 cw/cd	JNB rel16/32	Jump near if not below (CF=0).
        extern __cmd jnbe_n;        // 0F 87 cw/cd	JNBE rel16/32	Jump near if not below or equal (CF=0 and ZF=0).
        extern __cmd jnc_n;         // 0F 83 cw/cd	JNC rel16/32	Jump near if not carry (CF=0).
        extern __cmd jne_n;         // 0F 85 cw/cd	JNE rel16/32	Jump near if not equal (ZF=0).
        extern __cmd jng_n;         // 0F 8E cw/cd	JNG rel16/32	Jump near if not greater (ZF=1 or SF<>OF).
        extern __cmd jnge_n;        // 0F 8C cw/cd	JNGE rel16/32	Jump near if not greater or equal (SF<>OF).
        extern __cmd jnl_n;         // 0F 8D cw/cd	JNL rel16/32	Jump near if not less (SF=OF).
        extern __cmd jnle_n;        // 0F 8F cw/cd	JNLE rel16/32	Jump near if not less or equal (ZF=0 and SF=OF).
        extern __cmd jno_n;         // 0F 81 cw/cd	JNO rel16/32	Jump near if not overflow (OF=0).
        extern __cmd jnp_n;         // 0F 8B cw/cd	JNP rel16/32	Jump near if not parity (PF=0).
        extern __cmd jns_n;         // 0F 89 cw/cd	JNS rel16/32	Jump near if not sign (SF=0).
        extern __cmd jnz_n;         // 0F 85 cw/cd	JNZ rel16/32	Jump near if not zero (ZF=0).
        extern __cmd jo_n;          // 0F 80 cw/cd	JO rel16/32	Jump near if overflow (OF=1).
        extern __cmd jp_n;          // 0F 8A cw/cd	JP rel16/32	Jump near if parity (PF=1).
        extern __cmd jpe_n;         // 0F 8A cw/cd	JPE rel16/32	Jump near if parity even (PF=1).
        extern __cmd jpo_n;         // 0F 8B cw/cd	JPO rel16/32	Jump near if parity odd (PF=0).
        extern __cmd js_n;          // 0F 88 cw/cd	JS rel16/32	Jump near if sign (SF=1).

    }
    // [JMP]----------------------------------------------------------------------------------------------------------------
    namespace jmp {
        extern __cmd rel8;      // EB cb	JMP rel8	 Jump short, relative, displacement relative to next instruction.
        extern __cmd rel16;     // E9 cw	JMP rel16	 Jump near, relative, displacement relative to next instruction.
        extern __cmd rel32;     // E9 cd	JMP rel32	 Jump near, relative, displacement relative to next instruction.

        extern __cmd rm16;      // FF /4	JMP r/m16	 Jump near, absolute indirect, address given in r/m16.
        extern __cmd rm32;      // FF /4	JMP r/m32	 Jump near, absolute indirect, address given in r/m32.
        extern __cmd rm64;      // FF /4	JMP r/m32	 Jump near, absolute indirect, address given in r/m32.

        extern __cmd ptr16_16;  // EA cd	JMP ptr16:16 Jump far, absolute, address given in operand.
        extern __cmd ptr16_32;  // EA cp	JMP ptr16:32 Jump far, absolute, address given in operand.

        extern __cmd m16_16;    // FF /5	JMP m16:16	 Jump far, absolute indirect, address given in m16:16.
        extern __cmd m16_32;    // FF /5	JMP m16:32	 Jump far, absolute indirect, address given in m16:32.
    }
    // [RET]----------------------------------------------------------------------------------------------------------------
    namespace ret {
        extern __cmd ret_near;       // C3	    RET	Near return to calling procedure.
        extern __cmd ret_far;       // CB       RET	Far return to calling procedure.
        extern __cmd ret_ni16;       // C2 iw    RET imm16	Near return to calling procedure and pop imm16 bytes from stack.
        extern __cmd ret_nf16;       // CA iw    RET imm16	Far return to calling procedure and pop imm16 bytes from stack.
    }
    // [PUSH]---------------------------------------------------------------------------------------------------------------
    namespace push {
        extern __cmd rm8 ;  // FF /6	    Push r/m8
        extern __cmd rm16;  // FF /6	    Push r/m16
        extern __cmd rm32;  // FF /6	    Push r/m32
        extern __cmd rm64;  // FF /6	    Push r/m32

        extern __cmd r8;    // 50+rd	    Push r8
        extern __cmd r16;   // 50+rw	    Push r16
        extern __cmd r32;   // 50+rd	    Push r32
        extern __cmd r64;   // 50+rd	    Push r64

        extern __cmd i8;    // 6A	        Push imm8
        extern __cmd i16;   // 68	        Push imm16
        extern __cmd i32;   // 68	        Push imm32

        extern __cmd cs;    // 0E	        Push CS
        extern __cmd ss;    // 16	        Push SS
        extern __cmd ds;    // 1E	        Push DS
        extern __cmd es;    // 06	        Push ES
        extern __cmd fs;    // 0F A0	    Push FS
        extern __cmd gs;    // 0F A8	    Push GS
    }
    // [POP]---------------------------------------------------------------------------------------------------------------
    namespace pop {
        extern __cmd m16;    // 8F /0		Pop top of stack into m16; increment stack pointer.
        extern __cmd m32;    // 8F /0		Pop top of stack into m32; increment stack pointer.
        extern __cmd m64;    // 8F /0		Pop top of stack into m64; increment stack pointer.

        extern __cmd r16;    // 58+ rw    Pop top of stack into r16; increment stack pointer.
        extern __cmd r32;    // 58+ rd    Pop top of stack into r32; increment stack pointer.
        extern __cmd r64;    // 58+ rd    Pop top of stack into r32; increment stack pointer.

        extern __cmd ds;        // 1F	    Pop top of stack into DS; increment stack pointer.
        extern __cmd es;        // 07	    Pop top of stack into ES; increment stack pointer.
        extern __cmd ss;        // 17	    Pop top of stack into SS; increment stack pointer.
        extern __cmd fs;        // 0F A1	    Pop top of stack into FS; increment stack pointer.
        extern __cmd gs;        // 0F A9	    Pop top of stack into GS; increment stack pointer.
    }
// []---------------------------------------------------------------------------------------------------------------
// []---------------------------------------------------------------------------------------------------------------
// []---------------------------------------------------------------------------------------------------------------

}

#endif //BAMBLBI_TRANSLATOR_ASM_OPCODE_H
