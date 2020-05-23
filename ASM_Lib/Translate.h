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
    arg_sreg,
    arg_mem,
    arg_imm,
    arg_label
};

struct arg_t {
    bool mem = false;
    __int32_t val[3]  = {0, 0 ,0};
    int sparseness[3] = {0, 0, 0};

    //                REG1    REG2   Num
    bool val_on[3] = {false, false, false};
};

enum proces {
    cp, cpp
};

struct instuction_t {
    int proces      = 0;
    int command     = 0;
    int extra_cmd   = 0;
    int sparseness  = 0;

    int num_args    = 0;
    arg_t *args     = nullptr;

    void dump ();
};

const int num_extra_cmd = 4;
extern char extra_cmd[num_extra_cmd][10];

int Translate (SourceCodeNasm &code);

char *tolower (char *str);

inline bool isnumber (char symb);

__word createComand (instuction_t instr);

struct  _cmd_t {
    __uint8_t LegPref  = 0;
    __uint8_t REXPref  = 0;
    __uint8_t ModR_M   = 0;
    __uint8_t SIB      = 0;
    __int32_t Disp     = 0;
    __int32_t Imm      = 0;

    __uint8_t sizeImm  = 0;    // In bytes
    __uint8_t sizeDisp = 0;    // In bytes

    bool LegPref_On    = false;
    bool REXPref_On    = false;
    bool ModR_M_On     = false;
    bool SIB_On        = false;
    bool Disp_On       = false;
    bool Imm_On        = false;

    opcode::__cmd Opcode;
    __uint8_t getSize ();
    __word buildMC ();
};

__word genCmd (opcode::__cmd command, instuction_t instr);

#endif //BAMBLBI_TRANSLATOR_TRANSLATE_H
