//
// Created by tester on 20.05.2020.
//


// To beuat
// TODO rewrite in 64
// TODO XOR, OR, AND, NOT, NEG, INC, DEC, NOP

// [MOV]----------------------------------------------------------------------------------------------------------------
//
// Created by tester on 21.05.2020.
//

#include "ASM_Opcode.h"

namespace opcode {
    char _name_cmds[__Quantity_Types_Commands][max_len_name_cmd] = {
    "mov",
    "add",  "sub",
    "mul",  "div", "imul", "idiv",
    "push", "pop",
    "ret",

    "jmp",
    "ja",     "jae",    "jb",     "jbe",    "jc",     "jcxz",   "jecx",   "je",
    "jg",     "jge",    "jl",     "jle",    "jna",    "jnae",   "jnb",    "jnbe",
    "jnc",    "jne",    "jng",    "jnge",   "jnl",    "jnle",   "jno",    "jnp",
    "jns",    "jnz",    "jo",     "jp",     "jpe",    "jpo",    "js",     "jz"

};

    // [MOV]------------------------------------------------------------------------------------------------------------
    namespace mov {
    __cmd rm8_r8   (0x88, 1);        // 88 /r	MOV r/m8,  r8	    Move r8 to r/m8.
    __cmd rm16_r16 (0x89, 1);        // 89 /r	MOV r/m16, r16	    Move r16 to r/m16.
    __cmd rm32_r32 (0x89, 1);        // 89 /r	MOV r/m32, r32	    Move r32 to r/m32.
    __cmd rm64_r64 (0x89, 1);        // 89 /r	MOV r/m64, r64	    Move r64 to r/m64.

    __cmd r8_rm8 (0x8a, 1);          // 8A /r	MOV r8,  r/m8	    Move r/m8 to r8.
    __cmd r16_rm16 (0x8b, 1);        // 8B /r	MOV r16, r/m16	    Move r/m16 to r16.
    __cmd r32_rm32 (0x8b, 1);        // 8B /r	MOV r32, r/m32	    Move r/m32 to r32.
    __cmd r64_rm64 (0x8b, 1);        // 8B /r	MOV r64, r/m64	    Move r/m64 to r64.

    __cmd rm8_sr (0x8c, 1);          // 8C /r	MOV r/m16, Sreg**	Move segment register to r/m16.
    __cmd sr_rm8 (0x8e, 1);          // 8E /r	MOV Sreg, r/m16**	Move r/m16 to segment register.

    __cmd r8_moffs8 (0xa0, 1);      // A0	    MOV AL, moffs8*	    Move byte at (seg:offset) to AL.
    __cmd r16_moffs16 (0xa1, 1);      // A1	    MOV AX, moffs16*	Move word at (seg:offset) to AX.
    __cmd r32_moffs32 (0xa1, 1);      // A1	    MOV EAX, moffs32*	Move dword at (seg:offset) to EAX.

    __cmd moffs8_r8   (0xa2, 1);      // A2	    MOV moffs8*, AL	    Move AL to (seg:offset).
    __cmd moffs16_r16 (0xa3, 1);      // A3	    MOV moffs16*, AX	Move AX to (seg:offset).
    __cmd moffs32_r32 (0xa3, 1);      // A3	    MOV moffs32*, EAX	Move EAX to (seg:offset).

    __cmd r8_i8   (0xb0, 1);      // B0+ rb	MOV r8, imm8	    Move imm8 to r8.
    __cmd r16_i16 (0xb8, 1);      // B8+ rw	MOV r16, imm16	    Move imm16 to r16.
    __cmd r32_i32 (0xb8, 1);      // B8+ rd	MOV r32, imm32	    Move imm32 to r32.
    __cmd r64_i64 (0xb8, 1);      // B8+ rd	MOV r32, imm32	    Move imm32 to r32.

    __cmd rm8_i8   (0xc6, 1);      // C6 /0	MOV r/m8, imm8	    Move imm8 to r/m8.
    __cmd rm16_i16 (0xc7, 1);      // C7 /0	MOV r/m16, imm16	Move imm16 to r/m16.
    __cmd rm32_i32 (0xc7, 1);      // C7 /0	MOV r/m32, imm32	Move imm32 to r/m32.
    __cmd rm64_i64 (0xc7, 1);      // C7 /0	MOV r/m32, imm32	Move imm32 to r/m32.
}
    // [ADD]------------------------------------------------------------------------------------------------------------
    namespace add {
        __cmd r8_i8 (0x04, 1);          // 04 ib	    ADD AL,    imm8	    Add imm8 to AL
        __cmd r16_i16 (0x05, 1);        // 05 iw	    ADD AX,    imm16	Add imm16 to AX
        __cmd r32_i32 (0x05, 1);        // 05 id	    ADD EAX,   imm32	Add imm32 to EAX
        __cmd r64_i64 (0x05, 1);        // 05 id	    ADD RAX,   imm64	Add imm32 to EAX

        __cmd rm8_i8 (0x80, 1);         // 80 /0 ib	    ADD r/m8,  imm8	    Add imm8 to r/m8
        __cmd rm16_i16 (0x81, 1);       // 81 /0 iw	    ADD r/m16, imm16	Add imm16 to r/m16
        __cmd rm32_i32 (0x81, 1);       // 81 /0 id	    ADD r/m32, imm32	Add imm32 to r/m32
        __cmd rm64_i64 (0x81, 1);       // 81 /0 id	    ADD r/m32, imm32	Add imm32 to r/m32

        __cmd rm16_i16_se (0x83, 1);    // 83 /0 ib	    ADD r/m16, imm8	    Add sign-extended imm8 to r/m16
        __cmd rm32_i32_se (0x83, 1);    // 83 /0 ib	    ADD r/m32, imm8	    Add sign-extended imm8 to r/m32
        __cmd rm64_i64_se (0x83, 1);    // 83 /0 ib	    ADD r/m32, imm8	    Add sign-extended imm8 to r/m32

        __cmd rm8_r8 (0x00, 1);         // 00 /r	    ADD r/m8,  r8	    Add r8 to r/m8
        __cmd rm16_r16 (0x01, 1);       // 01 /r	    ADD r/m16, r16	    Add r16 to r/m16
        __cmd rm32_r32 (0x01, 1);       // 01 /r	    ADD r/m32, r32	    Add r32 to r/m32
        __cmd rm64_r64 (0x01, 1);       // 01 /r	    ADD r/m32, r32	    Add r32 to r/m32

        __cmd r8_rm8 (0x02, 1);          // 02 /r	    ADD r8,  r/m8	    Add r/m8 to r8
        __cmd r16_rm16 (0x03, 1);        // 03 /r	    ADD r16, r/m16	    Add r/m16 to r16
        __cmd r32_rm32 (0x03, 1);        // 03 /r	    ADD r32, r/m32	    Add r/m32 to r32
        __cmd r64_rm64 (0x03, 1);        // 03 /r	    ADD r32, r/m32	    Add r/m32 to r32
    }
    // [SUB]------------------------------------------------------------------------------------------------------------
    namespace sub {
        __cmd r8_i8 (0x2c, 1);          // 2C ib	    SUB AL,    imm8	    Subtract imm8  from AL
        __cmd r16_i16 (0x2d, 1);        // 2D iw	    SUB AX,    imm16	Subtract imm16 from AX
        __cmd r32_i32 (0x2d, 1);        // 2D id	    SUB EAX,   imm32	Subtract imm32 from EAX
        __cmd r64_i64 (0x2d, 1);        // 2D id	    SUB EAX,   imm32	Subtract imm32 from EAX

        __cmd rm8_i8   (0x8028, 1, 1);     // 80 /5 ib	    SUB r/m8,  imm8	    Subtract imm8  from r/m8
        __cmd rm16_i16 (0x8128, 1, 1);     // 81 /5 iw	    SUB r/m16, imm16    Subtract imm16 from r/m16
        __cmd rm32_i32 (0x8128, 1, 1);     // 81 /5 id	    SUB r/m32, imm32    Subtract imm32 from r/m32
        __cmd rm64_i64 (0x8128, 1, 1);     // 81 /5 id	    SUB r/m32, imm32    Subtract imm32 from r/m32

        __cmd rm16_i16_se (0x8328, 1, 1);  // 83 /5 ib	    SUB r/m16, imm8	    Subtract sign-extended imm8 from r/m16
        __cmd rm32_i32_se (0x8328, 1, 1);  // 83 /5 ib	    SUB r/m32, imm8	    Subtract sign-extended imm8 from r/m32
        __cmd rm64_i64_se (0x8328, 1, 1);  // 83 /5 ib	    SUB r/m32, imm8	    Subtract sign-extended imm8 from r/m32

        __cmd rm8_r8   (0x28, 1);       // 28 /r	    SUB r/m8,  r8	    Subtract r8  from r/m8
        __cmd rm16_r16 (0x29, 1);       // 29 /r	    SUB r/m16, r16	    Subtract r16 from r/m16
        __cmd rm32_r32 (0x29, 1);       // 29 /r	    SUB r/m32, r32	    Subtract r32 from r/m32
        __cmd rm64_r64 (0x29, 1);       // 29 /r	    SUB r/m32, r32	    Subtract r32 from r/m32

        __cmd r8_rm8   (0x2a, 1);       // 2A /r	    SUB r8,    r/m8	    Subtract r/m8  from r8
        __cmd r16_rm16 (0x2b, 1);       // 2B /r	    SUB r16,   r/m16	Subtract r/m16 from r16
        __cmd r32_rm32 (0x2b, 1);       // 2B /r	    SUB r32,   r/m32	Subtract r/m32 from r32
        __cmd r64_rm64 (0x2b, 1);       // 2B /r	    SUB r32,   r/m32	Subtract r/m32 from r32
    }
    // [MUL]------------------------------------------------------------------------------------------------------------
    namespace mul {
        __cmd rm8  (0xf620, 1, 1);  // F6 /4	MUL r/m8	Unsigned multiply (AX = AL * r/m8).
        __cmd rm16 (0xf720, 1, 1);  // F7 /4	MUL r/m16	Unsigned multiply (DX:AX = AX * r/m16).
        __cmd rm32 (0xf720, 1, 1);  // F7 /4	MUL r/m32	Unsigned multiply (EDX:EAX = EAX * r/m32)
        __cmd rm64 (0xf720, 1, 1);  // F7 /4	MUL r/m32	Unsigned multiply (EDX:EAX = EAX * r/m32)
    }
    // [DIV]------------------------------------------------------------------------------------------------------------
    namespace div {
        __cmd rm8  (0xf630, 1, 1);  // F6 /6	DIV r/m8	Unsigned divide AX by r/m8, with result stored in AL = Quotient, AH = Remainder
        __cmd rm16 (0xf730, 1, 1);  // F7 /6	DIV r/m16	Unsigned divide DX:AX by r/m16, with result stored in AX = Quotient, DX = Remainder
        __cmd rm32 (0xf730, 1, 1);  // F7 /6	DIV r/m32	Unsigned divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder
        __cmd rm64 (0xf730, 1, 1);  // F7 /6	DIV r/m32	Unsigned divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder
    }
    // [IMUL]-----------------------------------------------------------------------------------------------------------
    namespace imul {
        __cmd rm8  (0xf628, 1, 1);  // F6 /5	IMUL r/m8	            AX = AL * r/m byte
        __cmd rm16 (0xf728, 1, 1);  // F7 /5	IMUL r/m16	            DX:AX = AX * r/m word
        __cmd rm32 (0xf728, 1, 1);  // F7 /5	IMUL r/m32	            EDX:EAX = EAX * r/m doubleword
        __cmd rm64 (0xf728, 1, 1);  // F7 /5	IMUL r/m32	            EDX:EAX = EAX * r/m doubleword

        __cmd r_rm16 (0x0faf, 2);   // 0F AF /r	IMUL r16, r/m16	        word register = word register * r/m word
        __cmd r_rm32 (0x0faf, 2);   // 0F AF /r	IMUL r32, r/m32	        doubleword register = doubleword register * r/m doubleword
        __cmd r_rm64 (0x0faf, 2);   // 0F AF /r	IMUL r32, r/m32	        doubleword register = doubleword register * r/m doubleword

        __cmd r16_rm_i8 (0x6b, 1);  // 6B /r ib	IMUL r16, r/m16, imm8	word register = r/m16 * sign-extended immediate byte
        __cmd r32_rm_i8 (0x6b, 1);  // 6B /r ib	IMUL r32, r/m32, imm8	doubleword register = r/m32 * sign-extended immediate byte
        __cmd r64_rm_i8 (0x6b, 1);  // 6B /r ib	IMUL r32, r/m32, imm8	doubleword register = r/m32 * sign-extended immediate byte

        __cmd r16_i8    (0x6b, 1);  // 6B /r ib	IMUL r16, r/m16, imm8	word register = r/m16 * sign-extended immediate byte
        __cmd r32_i8    (0x6b, 1);  // 6B /r ib	IMUL r32, r/m32, imm8	doubleword register = r/m32 * sign-extended immediate byte
        __cmd r64_i8    (0x6b, 1);  // 6B /r ib	IMUL r32, r/m32, imm8	doubleword register = r/m32 * sign-extended immediate byte

        __cmd r_rm_i16 (0x69, 1);   // 69 /r iw	IMUL r16, r/m16, imm16	word register = r/m16 * immediate word
        __cmd r_rm_i32 (0x69, 1);   // 69 /r id	IMUL r32, r/m32, imm32	doubleword register = r/m32 * immediate doubleword
        __cmd r_rm_i64 (0x69, 1);   // 69 /r id	IMUL r32, r/m32, imm32	doubleword register = r/m32 * immediate doubleword

        __cmd r_i16 (0x69, 1);      // 69 /r iw	IMUL r16, imm16	        word register = r/m16 * immediate word
        __cmd r_i32 (0x69, 1);      // 69 /r id	IMUL r32, imm32	        doubleword register = r/m32 * immediate doubleword
        __cmd r_i64 (0x69, 1);      // 69 /r id	IMUL r32, imm32	        doubleword register = r/m32 * immediate doubleword

        /*
             6B /r ib	IMUL r32,r/m32,imm8	    doubleword register = r/m32 * sign-extended immediate byte
             6B /r ib	IMUL r16,r/m16,imm8	    word register = r/m16 * sign-extended immediate byte..

             6B /r ib	IMUL r16,imm8	word register = word register * sign-extended immediate byte.
            6B /r ib	IMUL r32,imm8	doubleword register = doubleword register * signextended immediate byte.

            69 /r iw	IMUL r16,r/m16,imm16	word register = r/m16 * immediate word.
            69 /r id	IMUL r32,r/m32,imm32	doubleword register = r/m32 * immediate doubleword.
            69 /r iw	IMUL r16,imm16	        word register = r/m16 * immediate word.
            69 /r id	IMUL r32,imm32	        doubleword register = r/m32 * immediate doubleword.
        */
    }
    // [IDIV]----------------------------------------------------------------------------------------------------------------
    namespace idiv {
        __cmd rm8  (0xf638, 1, 1);  // F6 /7	IDIV r/m8       Signed divide AX by r/m8, with result stored in AL = Quotient, AH = Remainder
        __cmd rm16 (0xf738, 1, 1);  // F7 /7	IDIV r/m16      Signed divide DX:AX by r/m16, with result stored in AX = Quotient, DX = Remainder
        __cmd rm32 (0xf738, 1, 1);  // F7 /7	IDIV r/m32      Signed divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder
        __cmd rm64 (0xf738, 1, 1);  // F7 /7	IDIV r/m32      Signed divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder
    }
    // [Jcc]----------------------------------------------------------------------------------------------------------------
    namespace jcc {
        __cmd ja_s    (0x77, 1);    // 77 cb	JA rel8	            Jump short if above (CF=0 and ZF=0)
        __cmd jae_s   (0x73, 1);    // 73 cb	JAE rel8	        Jump short if above or equal (CF=0)
        __cmd jb_s    (0x72, 1);    // 72 cb	JB rel8	            Jump short if below (CF=1)
        __cmd jbe_s   (0x76, 1);    // 76 cb	JBE rel8	        Jump short if below or equal (CF=1 or ZF=1)
        __cmd jc_s    (0x72, 1);    // 72 cb	JC rel8	            Jump short if carry (CF=1)
        __cmd jcxz_s  (0xe3, 1);    // E3 cb	JCXZ rel8	        Jump short if CX register is 0
        __cmd jecxz_s (0xe3, 1);    // E3 cb	JECXZ rel8	        Jump short if ECX register is 0
        __cmd je_s    (0x74, 1);    // 74 cb	JE rel8	            Jump short if equal (ZF=1)
        __cmd jg_s    (0x7f, 1);    // 7F cb	JG rel8	            Jump short if greater (ZF=0 and SF=OF)
        __cmd jge_s   (0x7d, 1);    // 7D cb	JGE rel8	        Jump short if greater or equal (SF=OF)
        __cmd jl_s    (0x7c, 1);    // 7C cb	JL rel8	            Jump short if less (SF<>OF)
        __cmd jle_s   (0x7e, 1);    // 7E cb	JLE rel8	        Jump short if less or equal (ZF=1 or SF<>OF)
        __cmd jna_s   (0x76, 1);    // 76 cb	JNA rel8	        Jump short if not above (CF=1 or ZF=1)
        __cmd jnae_s  (0x72, 1);    // 72 cb	JNAE rel8	        Jump short if not above or equal (CF=1)
        __cmd jnb_s   (0x73, 1);    // 73 cb	JNB rel8	        Jump short if not below (CF=0)
        __cmd jnbe_s  (0x77, 1);    // 77 cb	JNBE rel8	        Jump short if not below or equal (CF=0 and ZF=0)
        __cmd jnc_s   (0x73, 1);    // 73 cb	JNC rel8	        Jump short if not carry (CF=0).
        __cmd jne_s   (0x75, 1);    // 75 cb	JNE rel8	        Jump short if not equal (ZF=0)
        __cmd jng_s   (0x7e, 1);    // 7E cb	JNG rel8	        Jump short if not greater (ZF=1 or SF<>OF)
        __cmd jnge_s  (0x7c, 1);    // 7C cb	JNGE rel8	        Jump short if not greater or equal (SF<>OF)
        __cmd jnl_s   (0x7d, 1);    // 7D cb	JNL rel8	        Jump short if not less (SF=OF)
        __cmd jnle_s  (0x7f, 1);    // 7F cb	JNLE rel8	        Jump short if not less or equal (ZF=0 and SF=OF)
        __cmd jno_s   (0x71, 1);    // 71 cb	JNO rel8	        Jump short if not overflow (OF=0)
        __cmd jnp_s   (0x7b, 1);    // 7B cb	JNP rel8	        Jump short if not parity (PF=0)
        __cmd jns_s   (0x79, 1);    // 79 cb	JNS rel8	        Jump short if not sign (SF=0)
        __cmd jnz_s   (0x75, 1);    // 75 cb	JNZ rel8	        Jump short if not zero (ZF=0)
        __cmd jo_s    (0x70, 1);    // 70 cb	JO rel8	            Jump short if overflow (OF=1)
        __cmd jp_s    (0x7a, 1);    // 7A cb	JP rel8	            Jump short if parity (PF=1)
        __cmd jpe_s   (0x7a, 1);    // 7A cb	JPE rel8	        Jump short if parity even (PF=1)
        __cmd jpo_s   (0x7b, 1);    // 7B cb	JPO rel8	        Jump short if parity odd (PF=0)
        __cmd js_s    (0x78, 1);    // 78 cb	JS rel8	            Jump short if sign (SF=1).0
        __cmd jz_s    (0x74, 1);    // 74 cb	JZ rel8	            Jump short if zero (ZF = 1)

        __cmd ja_n  (0x0f87, 2);    // 0F 87 cw/cd	JA rel16/32	    Jump near if above (CF=0 and ZF=0)
        __cmd jae_n (0x0f83, 2);    // 0F 83 cw/cd	JAE rel16/32	Jump near if above or equal (CF=0)
        __cmd jb_n  (0x0f82, 2);    // 0F 82 cw/cd	JB rel16/32	    Jump near if below (CF=1)
        __cmd jbe_n (0x0f86, 2);    // 0F 86 cw/cd	JBE rel16/32	Jump near if below or equal (CF=1 or ZF=1)
        __cmd jc_n  (0x0f82, 2);    // 0F 82 cw/cd	JC rel16/32	    Jump near if carry (CF=1)
        __cmd je_n  (0x0f84, 2);    // 0F 84 cw/cd	JE rel16/32	    Jump near if equal (ZF=1)
        __cmd jg_n  (0x0f8f, 2);    // 0F 8F cw/cd	JG rel16/32	    Jump near if greater (ZF=0 and SF=OF)
        __cmd jge_n (0x0f8d, 2);    // 0F 8D cw/cd	JGE rel16/32	Jump near if greater or equal (SF=OF)
        __cmd jl_n  (0x0f8c, 2);    // 0F 8C cw/cd	JL rel16/32	    Jump near if less (SF<>OF)
        __cmd jle_n (0x0f8e, 2);    // 0F 8E cw/cd	JLE rel16/32	Jump near if less or equal (ZF=1 or SF<>OF)
        __cmd jna_n (0x0f86, 2);    // 0F 86 cw/cd	JNA rel16/32	Jump near if not above (CF=1 or ZF=1)
        __cmd jnae_n(0x0f82, 2);    // 0F 82 cw/cd	JNAE rel16/32	Jump near if not above or equal (CF=1)
        __cmd jnb_n (0x0f83, 2);    // 0F 83 cw/cd	JNB rel16/32	Jump near if not below (CF=0)
        __cmd jnbe_n(0x0f87, 2);    // 0F 87 cw/cd	JNBE rel16/32	Jump near if not below or equal (CF=0 and ZF=0)
        __cmd jnc_n (0x0f83, 2);    // 0F 83 cw/cd	JNC rel16/32	Jump near if not carry (CF=0)
        __cmd jne_n (0x0f85, 2);    // 0F 85 cw/cd	JNE rel16/32	Jump near if not equal (ZF=0)
        __cmd jng_n (0x0f8e, 2);    // 0F 8E cw/cd	JNG rel16/32	Jump near if not greater (ZF=1 or SF<>OF)
        __cmd jnge_n(0x0f8c, 2);    // 0F 8C cw/cd	JNGE rel16/32	Jump near if not greater or equal (SF<>OF)
        __cmd jnl_n (0x0f8d, 2);    // 0F 8D cw/cd	JNL rel16/32	Jump near if not less (SF=OF)
        __cmd jnle_n (0x0f8f, 2);   // 0F 8F cw/cd	JNLE rel16/32	Jump near if not less or equal (ZF=0 and SF=OF)
        __cmd jno_n (0x0f81, 2);    // 0F 81 cw/cd	JNO rel16/32	Jump near if not overflow (OF=0)
        __cmd jnp_n (0x0f8b, 2);    // 0F 8B cw/cd	JNP rel16/32	Jump near if not parity (PF=0)
        __cmd jns_n (0x0f89, 2);    // 0F 89 cw/cd	JNS rel16/32	Jump near if not sign (SF=0)
        __cmd jnz_n (0x0f85, 2);    // 0F 85 cw/cd	JNZ rel16/32	Jump near if not zero (ZF=0)
        __cmd jo_n  (0x0f80, 2);    // 0F 80 cw/cd	JO rel16/32	    Jump near if overflow (OF=1)
        __cmd jp_n  (0x0f8a, 2);    // 0F 8A cw/cd	JP rel16/32	    Jump near if parity (PF=1)
        __cmd jpe_n (0x0f8a, 2);    // 0F 8A cw/cd	JPE rel16/32	Jump near if parity even (PF=1)
        __cmd jpo_n (0x0f8b, 2);    // 0F 8B cw/cd	JPO rel16/32	Jump near if parity odd (PF=0)
        __cmd js_n  (0x0f88, 2);    // 0F 88 cw/cd	JS rel16/32	    Jump near if sign (SF=1)
        __cmd jz_n  (0x0f84, 2);    // 0F 84 cw/cd	JZ rel16/32	    Jump near if 0 (ZF=1)
    }
    // [JMP]----------------------------------------------------------------------------------------------------------------
    namespace jmp {
        __cmd rel8     (0xeb, 1);       // EB cb	JMP rel8	 Jump short, relative, displacement relative to next instruction
        __cmd rel16    (0xe9, 1);       // E9 cw	JMP rel16	 Jump near, relative, displacement relative to next instruction
        __cmd rel32    (0xe9, 1);       // E9 cd	JMP rel32	 Jump near, relative, displacement relative to next instruction

        __cmd rm16     (0xff20, 1, 1);  // FF /4	JMP r/m16	 Jump near, absolute indirect, address given in r/m16
        __cmd rm32     (0xff20, 1, 1);  // FF /4	JMP r/m32	 Jump near, absolute indirect, address given in r/m32
        __cmd rm64     (0xff20, 1, 1);  // FF /4	JMP r/m32	 Jump near, absolute indirect, address given in r/m32

        __cmd ptr16_16 (0xea, 1);       // EA cd  UUJMP ptr16:16 Jump far, absolute, address given in operand
        __cmd ptr16_32 (0xea, 1);       // EA cp  UUJMP ptr16:32 Jump far, absolute, address given in operand

        __cmd m16_16   (0xff28, 1, 1);  // FF /5  UUJMP m16:16	 Jump far, absolute indirect, address given in m16:16
        __cmd m16_32   (0xff28, 1, 1);  // FF /5  UUJMP m16:32	 Jump far, absolute indirect, address given in m16:32
    }
    // [RET]----------------------------------------------------------------------------------------------------------------
    namespace ret {
        __cmd ret_near (0xc3, 1);       // C3	    RET	Near return to calling procedure.
        __cmd ret_far  (0xcb, 1);       // CB       RET	Far return to calling procedure.
        __cmd ret_ni16 (0xc2, 1);       // C2 iw    RET imm16	Near return to calling procedure and pop imm16 bytes from stack.
        __cmd ret_nf16 (0xca, 1);       // CA iw    RET imm16	Far return to calling procedure and pop imm16 bytes from stack.
    }
    // [PUSH]---------------------------------------------------------------------------------------------------------------
    namespace push {
        __cmd rm8  (0xff30, 1, 1); // FF /6    Push r/m16
        __cmd rm16 (0xff30, 1, 1); // FF /6    Push r/m16
        __cmd rm32 (0xff30, 1, 1); // FF /6    Push r/m32
        __cmd rm64 (0xff30, 1, 1); // FF /6    Push r/m32

        __cmd r8  (0x50, 1);       // 50+rw    Push r8
        __cmd r16 (0x50, 1);       // 50+rw    Push r16
        __cmd r32 (0x50, 1);       // 50+rd    Push r32
        __cmd r64 (0x50, 1);       // 50+rd    Push r64

        __cmd i8  (0x6a, 1);       // 6A	    Push imm8
        __cmd i16 (0x68, 1);       // 68	    Push imm16
        __cmd i32 (0x68, 1);       // 68	    Push imm32

        __cmd cs  (0x0e, 1);       // 0E	    Push CS
        __cmd ss  (0x16, 1);       // 16	    Push SS
        __cmd ds  (0x1e, 1);       // 1E	    Push DS
        __cmd es  (0x06, 1);       // 06	    Push ES
        __cmd fs  (0x0fa0, 1);     // 0F A0    Push FS
        __cmd gs  (0x0fa8, 1);     // 0F A8    Push GS
    }
    // [POP]---------------------------------------------------------------------------------------------------------------
    namespace pop {
        __cmd m16 (0x8f, 1);    // 8F /0	  UUPop top of stack into m16; increment stack pointer.
        __cmd m32 (0x8f, 1);    // 8F /0	  UUPop top of stack into m32; increment stack pointer.
        __cmd m64 (0x8f, 1);    // 8F /0	  UUPop top of stack into m64; increment stack pointer.

        __cmd r64 (0x58, 1);    // 58+ rd       Pop top of stack into r32; increment stack pointer.

        __cmd ds (0x1f, 1);     // 1F	      UUPop top of stack into DS; increment stack pointer.
        __cmd es (0x07, 1);     // 07	      UUPop top of stack into ES; increment stack pointer.
        __cmd ss (0x17, 1);     // 17	      UUPop top of stack into SS; increment stack pointer.
        __cmd fs (0x0fa1, 2);   // 0F A1	  UUPop top of stack into FS; increment stack pointer.
        __cmd gs (0x0fa9, 2);   // 0F A9	  UUPop top of stack into GS; increment stack pointer.
    }
}
