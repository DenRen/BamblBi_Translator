//
// Created by tester on 19.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_ASM_COMMANDS_NAME_H
#define BAMBLBI_TRANSLATOR_ASM_COMMANDS_NAME_H

#define MAX_LEN_NASM_COMMANDS 32

namespace nasmnm {

    #define _nMOV       "mov"
    #define _nADD       "add"
    #define _nSUB       "sub"
    #define _nCMP       "cmp"
    #define _nTEST      "test"

    #define _nAND       "and"
    #define _nXOR       "xor"
    #define _nOR        "or"
    #define _nNOT       "not"

    #define _nMUL       "mul"
    #define _nDIV       "div"

    #define _nPUSH      "push"
    #define _nPOP       "pop"

    #define _nINC       "inc"
    #define _nDEC       "dec"

    #define _nJMP       "jmp"

    #define _nJE        "je"
    #define _nJNE       "jne"
    #define _nJL        "jl"
    #define _nJNGE      "jnge"
    #define _nJLE       "jle"
    #define _nJNG       "jng"
    #define _nJGE       "jge"
    #define _nJNL       "jnl"
    #define _nJB        "jb"
    #define _nJNAE      "jnae"
    #define _nJBE       "jbe"
    #define _nJNA       "jna"
    #define _nJA        "ja"
    #define _nJNBE      "jnbe"
    #define _nJAE       "jae"
    #define _nJJNB      "jjnb"

    #define _nJZ        "jz"
    #define _nJS        "js"
    #define _nJC        "jc"
    #define _nJO        "jo"
    #define _nJP        "jp"

    #define _nJECXZ     "jecxz"
    #define _nJRCXZ     "jrcxz"

    #define _nLOOP      "loop"
    #define _nLOOPE     "loope"
    #define _nLOOPNE    "loopne"
    #define _nLOOPZ     "loopz"
    #define _nLOOPNZ    "loopnz"

    #define _nCALL      "call"
    #define _nSYSCALL   "syscall"
    #define _nNOP       "nop"
    #define _nRET       "ret"

    #define _nrax       "rax"
    #define _nrbx       "rbx"
    #define _nrcx       "rcx"
    #define _nrdx       "rdx"
    #define _nrsi       "rsi"
    #define _nrdi       "rdi"
    #define _nrsp       "rsp"
    #define _nrbp       "rbp"

    #define _neax       "eax"
    #define _nebx       "ebx"
    #define _necx       "ecx"
    #define _nedx       "edx"
    #define _nesi       "esi"
    #define _nedi       "edi"
    #define _nesp       "esp"
    #define _nebp       "ebp"

    #define  _nax       "ax"
    #define  _nbx       "bx"
    #define  _ncx       "cx"
    #define  _ndx       "dx"
    #define  _nsi       "si"
    #define  _ndi       "di"
    #define  _nsp       "sp"
    #define  _nbp       "bp"

    char name_cmds[][MAX_LEN_NASM_COMMANDS] {
            _nMOV,
            _nADD,
            _nSUB,
            _nCMP,
            _nTEST,
            _nAND,
            _nXOR,
            _nOR,
            _nNOT,
            _nMUL,
            _nDIV,
            _nPUSH,
            _nPOP,
            _nINC,
            _nDEC,
            _nJMP,
            _nJE,
            _nJNE,
            _nJL,
            _nJNGE,
            _nJLE,
            _nJNG,
            _nJGE,
            _nJNL,
            _nJB,
            _nJNAE,
            _nJBE,
            _nJNA,
            _nJA,
            _nJNBE,
            _nJAE,
            _nJJNB,
            _nJZ,
            _nJS,
            _nJC,
            _nJO,
            _nJP,
            _nJECXZ,
            _nJRCXZ,
            _nLOOP,
            _nLOOPE,
            _nLOOPNE,
            _nLOOPZ,
            _nLOOPNZ,
            _nCALL,
            _nSYSCALL,
            _nNOP,
            _nRET,
            _nrax,
            _nrbx,
            _nrcx,
            _nrdx,
            _nrsi,
            _nrdi,
            _nrsp,
            _nrbp,
            _neax,
            _nebx,
            _necx,
            _nedx,
            _nesi,
            _nedi,
            _nesp,
            _nebp,
            _nax,
            _nbx,
            _ncx,
            _ndx,
            _nsi,
            _ndi,
            _nsp,
            _nbp
    };

    enum id_cmd {
        _id_MOV,
        _id_ADD,
        _id_SUB,
        _id_CMP,
        _id_TEST,
        _id_AND,
        _id_XOR,
        _id_OR,
        _id_NOT,
        _id_MUL,
        _id_DIV,
        _id_PUSH,
        _id_POP,
        _id_INC,
        _id_DEC,
        _id_JMP,
        _id_JE,
        _id_JNE,
        _id_JL,
        _id_JNGE,
        _id_JLE,
        _id_JNG,
        _id_JGE,
        _id_JNL,
        _id_JB,
        _id_JNAE,
        _id_JBE,
        _id_JNA,
        _id_JA,
        _id_JNBE,
        _id_JAE,
        _id_JJNB,
        _id_JZ,
        _id_JS,
        _id_JC,
        _id_JO,
        _id_JP,
        _id_JECXZ,
        _id_JRCXZ,
        _id_LOOP,
        _id_LOOPE,
        _id_LOOPNE,
        _id_LOOPZ,
        _id_LOOPNZ,
        _id_CALL,
        _id_SYSCALL,
        _id_NOP,
        _id_RET,
        _id_rax,
        _id_rbx,
        _id_rcx,
        _id_rdx,
        _id_rsi,
        _id_rdi,
        _id_rsp,
        _id_rbp,
        _id_eax,
        _id_ebx,
        _id_ecx,
        _id_edx,
        _id_esi,
        _id_edi,
        _id_esp,
        _id_ebp,
        _id_ax,
        _id_bx,
        _id_cx,
        _id_dx,
        _id_si,
        _id_di,
        _id_sp,
        _id_bp
    };

    #undef _nMOV
    #undef _nADD
    #undef _nSUB
    #undef _nCMP
    #undef _nTEST
    #undef _nAND
    #undef _nXOR
    #undef _nOR
    #undef _nNOT
    #undef _nMUL
    #undef _nDIV
    #undef _nPUSH
    #undef _nPOP
    #undef _nINC
    #undef _nDEC
    #undef _nJMP
    #undef _nJE
    #undef _nJNE
    #undef _nJL
    #undef _nJNGE
    #undef _nJLE
    #undef _nJNG
    #undef _nJGE
    #undef _nJNL
    #undef _nJB
    #undef _nJNAE
    #undef _nJBE
    #undef _nJNA
    #undef _nJA
    #undef _nJNBE
    #undef _nJAE
    #undef _nJJNB
    #undef _nJZ
    #undef _nJS
    #undef _nJC
    #undef _nJO
    #undef _nJP
    #undef _nJECXZ
    #undef _nJRCXZ
    #undef _nLOOP
    #undef _nLOOPE
    #undef _nLOOPNE
    #undef _nLOOPZ
    #undef _nLOOPNZ
    #undef _nCALL
    #undef _nSYSCALL
    #undef _nNOP
    #undef _nRET
    #undef _nrax
    #undef _nrbx
    #undef _nrcx
    #undef _nrdx
    #undef _nrsi
    #undef _nrdi
    #undef _nrsp
    #undef _nrbp
    #undef _neax
    #undef _nebx
    #undef _necx
    #undef _nedx
    #undef _nesi
    #undef _nedi
    #undef _nesp
    #undef _nebp
    #undef  _nax
    #undef  _nbx
    #undef  _ncx
    #undef  _ndx
    #undef  _nsi
    #undef  _ndi
    #undef  _nsp
    #undef  _nbp
}
#endif //BAMBLBI_TRANSLATOR_ASM_COMMANDS_NAME_H
