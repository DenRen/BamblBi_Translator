//
// Created by tester on 20.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_TRANSLATE_H
#define BAMBLBI_TRANSLATOR_TRANSLATE_H

#include "../SourceCodeNasm.h"
#include "ASM_Opcode.h"

enum type_arg {
    arg_empty,
    arg_reg,
    arg_exreg, // r8, r9, ...
    arg_sreg,
    arg_mem,
    arg_imm,
    arg_label
};

struct arg_t {
    int type;
    __int64_t arg;
    int sparseness;
};

int Translate (SourceCodeNasm code);

char *tolower (char *str);

inline bool isnumber (char symb);

__word createComand (__uint8_t command, arg_t *args, int quant_args);

struct  _cmd_t {
    __uint8_t   LegPref = 0;
    __uint8_t   REXPref = 0;
    __uint8_t   ModR_M  = 0;
    __uint8_t   SIB     = 0;
    __int32_t   Disp    = 0;
    __int32_t   Imm     = 0;

    bool LegPref_On = false;
    bool REXPref_On = false;
    bool ModR_M_On  = false;
    bool SIB_On     = false;
    bool Disp_On    = false;
    bool Imm_On     = false;

    opcode::__cmd Opcode;
    __uint8_t getSize (int sizeDisp = 0, int sizeImm = 0);
    __word buildMC (int sizeDisp = 0, int sizeImm = 0);
};

__word genCmd (opcode::__cmd command, arg_t *args, int quant_args);

#endif //BAMBLBI_TRANSLATOR_TRANSLATE_H
