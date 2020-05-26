//
// Created by tester on 20.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_TRANSLATE_H
#define BAMBLBI_TRANSLATOR_TRANSLATE_H

#include "../SourceCodeNasm.h"
#include "ASM_Opcode.h"
#include "../ELF/elf_prog_header.h"

struct label_t {
    __word name;
    __uint32_t position;
    bool rel = false;
};

struct labels_t {
    __uint32_t total_size;
    __uint32_t active_size;

    label_t *label;

    labels_t (__uint32_t size);
    bool add (__word name, __uint32_t pos);
    __int64_t find (__word name);
};

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
    __int64_t val[3]  = {0, 0 ,0};
    int sparseness[3] = {0, 0, 0};
    //                REG1    REG2   Num
    bool val_on[3] = {false, false, false};

    bool label_on = false;
    label_t *label;
};

enum proces {
    cp, cpp
};

struct instuction_t {
    int proces      = 0;
    int command     = 0;
    int extra_cmd   = 0;
    int sparseness  = 0;
    int offset      = 0;
    int num_args    = 0;
    arg_t *args     = nullptr;

    __uint32_t cur_pos = 0;
    bool rel = false;

    void dump ();
};

const int num_extra_cmd = 4;
extern char extra_cmd[num_extra_cmd][10];

__word Translate (SourceCodeNasm &code, FILE *temp_file, __uint32_t cur_pos, __uint32_t  locate_prog, bool dump);

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

    bool DispLabel_On  = false;
    bool ImmLabel_On   = false;
    bool rel_label     = false;

    label_t *DispLabel = nullptr;
    label_t *ImmLabel  = nullptr;

    _cmd_t ();
    opcode::__cmd Opcode;
    __uint8_t getSize ();
    __word buildMC (__uint32_t cur_pos);
};

__word genCmd (opcode::__cmd command, instuction_t instr);

#endif //BAMBLBI_TRANSLATOR_TRANSLATE_H
