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

        __cmd () :
            opcode (0),
            size (0)
        {};
        __cmd (__uint32_t opcode, __uint8_t size) :
                opcode (opcode),
                size (size)
        {}
    };

    enum _cmds {
        MOV,
        ADD, SUB,
        MUL, DIV, IMUL, IDIV,
        PUSH, POP,
        RET,

        JMP,
        JA,     JAE,    JB,     JBE,    JC,     JCXZ,   JECX,   JE,
        JG,     JGE,    JL,     JLE,    JNA,    JNAE,   JNB,    JNBE,
        JNC,    JNE,    JNG,    JNGE,   JNL,    JNLE,   JNO,    JNP,
        JNS,    JNZ,    JO,     JP,     JPE,    JPO,    JS,     JZ,

        __Quantity_Types_Commands
    };

    extern char _name_cmds [__Quantity_Types_Commands][max_len_name_cmd];

    // [MOV]----------------------------------------------------------------------------------------------------------------
    namespace mov {
        extern __cmd movrm8_r8;      // 88 /r	MOV r/m8,  r8	    Move r8 to r/m8.
        extern __cmd movrm16_r16;      // 89 /r	MOV r/m16, r16	    Move r16 to r/m16.
        extern __cmd movrm32_r32;      // 89 /r	MOV r/m32, r32	    Move r32 to r/m32.
        extern __cmd movrm64_r64;      // 89 /r	MOV r/m64, r64	    Move r64 to r/m64.

        extern __cmd movr8_rm8;     // 8A /r	MOV r8,  r/m8	    Move r/m8 to r8.
        extern __cmd movr16_rm16;      // 8B /r	MOV r16, r/m16	    Move r/m16 to r16.
        extern __cmd movr32_rm32;      // 8B /r	MOV r32, r/m32	    Move r/m32 to r32.
        extern __cmd movr64_rm64;      // 8B /r	MOV r64, r/m64	    Move r/m64 to r64.

        extern __cmd movrm8_sr;      // 8C /r	MOV r/m16, Sreg**	Move segment register to r/m16.
        extern __cmd movsr_rm8;      // 8E /r	MOV Sreg, r/m16**	Move r/m16 to segment register.

        extern __cmd movr8_moffs8 ;      // A0	    MOV AL, moffs8*	    Move byte at (seg:offset) to AL.
        extern __cmd movr16_moffs16;      // A1	    MOV AX, moffs16*	Move word at (seg:offset) to AX.
        extern __cmd movr32_moffs32;      // A1	    MOV EAX, moffs32*	Move dword at (seg:offset) to EAX.

        extern __cmd movmoffs8_r8;      // A2	    MOV moffs8*, AL	    Move AL to (seg:offset).
        extern __cmd movmoffs16_r16;      // A3	    MOV moffs16*, AX	Move AX to (seg:offset).
        extern __cmd movmoffs32_r32;      // A3	    MOV moffs32*, EAX	Move EAX to (seg:offset).

        extern __cmd movr8_i8;      // B0+ rb	MOV r8, imm8	    Move imm8 to r8.
        extern __cmd movr16_i16;      // B8+ rw	MOV r16, imm16	    Move imm16 to r16.
        extern __cmd movr32_i32;      // B8+ rd	MOV r32, imm32	    Move imm32 to r32.
        extern __cmd movr64_i64;      // B8+ rd	MOV r32, imm32	    Move imm32 to r32.

        extern __cmd movrm8_i8;      // C6 /0	MOV r/m8, imm8	    Move imm8 to r/m8.
        extern __cmd movrm16_i16;      // C7 /0	MOV r/m16, imm16	Move imm16 to r/m16.
        extern __cmd movrm32_i32;      // C7 /0	MOV r/m32, imm32	Move imm32 to r/m32.
        extern __cmd movrm64_i64;      // C7 /0	MOV r/m32, imm32	Move imm32 to r/m32.
    }
    // [ADD]----------------------------------------------------------------------------------------------------------------

// []---------------------------------------------------------------------------------------------------------------
// []---------------------------------------------------------------------------------------------------------------
// []---------------------------------------------------------------------------------------------------------------

}

#endif //BAMBLBI_TRANSLATOR_ASM_OPCODE_H
