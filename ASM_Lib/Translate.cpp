//
// Created by tester on 20.05.2020.
//

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include "Translate.h"
#include "ASM_Registers.h"
#include "ASM_Prefixes.h"
#include "ASM_ModR_M.h"
#include "../main_lib.h"
#include "ASM_SIB.h"

char extra_cmd[num_extra_cmd][10] = {
        "byte", "word", "dword", "qword"
};

inline bool isnumber (char symb) {
    return symb >= '0' && symb <= '9';
}

char *tolower (char *str) {
    int len = strlen (str);

    for (int i = 0; i < len; i++)
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] -= 'A' - 'a';

    return str;
}

int getSparseness (__int32_t number) {
    int pow = ceil (log2 (abs (number)));

    if (pow < 7)
        return 8;
    else if (pow < 15)
        return 16;
    else if (pow < 31)
        return 32;
    else
        return 64;
}

// Correct: mov [rax rcx -89], 164
int Translate (SourceCodeNasm &code) {

    for (__uint32_t num_line = 0; num_line < code.number_lines; num_line++) {

        __word  word  = code.lines_code[num_line].words[0]; // Current word
        __word *words = code.lines_code[num_line].words;
        __uint8_t quant_words = code.lines_code[num_line].size;


        printf ("%2d: ", num_line);
        for (int i = 0; i < quant_words; i++)
            printf ("%s ", words[i].word);

        printf ("\t--> ");

        instuction_t instr = {};

        // Get id commands
        instr.command = opcode::_cmds::__Quantity_Types_Commands;   // Set max value

        for (int i = 0; i < opcode::__Quantity_Types_Commands; i++)
            if (!strcmp (tolower (word.word), opcode::_name_cmds[i])) {
                instr.proces = proces::cp;
                instr.command = i;
                break;
            }


        printf ("%s\n", opcode::_name_cmds[instr.command]);

        instr.args = (arg_t *) calloc (quant_words - 1, sizeof (arg_t));

        if (instr.command < opcode::__Quantity_Types_Commands) {  // If command

            bool memory = false;
            bool extra  = false;

#define _ARG instr.args[instr.num_args]

            int num_value = 0;
            for (__uint8_t i = 1; i < quant_words; i++) {

                // Get word and lenght
                char *arg = code.lines_code[num_line].words[i].word;
                int   len = code.lines_code[num_line].words[i].len;

                // Check on extra command
                for (int j = 0 ; j < num_extra_cmd; j++)
                    if (!strcmp (arg, extra_cmd[j])) {
                        if (extra == false) {
                            extra = true;
                            instr.extra_cmd = j;

                            continue;
                        } else {
                            printf ("Syntax error!!!\n");
                            free (instr.args);

                            return -1;
                        }
                    }

                // Comment
                if (arg[0] == ';')
                    break;
                // Number
                else if (isnumber (arg[0])) {

                    __int32_t number = str2num (arg, len);

                    _ARG.val[2] = true;
                    _ARG.val[2] = number;

                    int temp_spr = getSparseness (number);
                    if (_ARG.sparseness[2] < temp_spr)
                        _ARG.sparseness[2] = temp_spr;

                    if (_ARG.mem == false)  // For example: mov rax, 156
                        break;

                } else if (arg[0] == '[') {

                    _ARG.mem = true;

                } else if (arg[0] == ']') {

                    instr.num_args++;
                    num_value = 0;

                } else {
                    for (int j = reg::quant_reg - 1; j >= 0; j--)   // Arg register
                        if (!strncmp (arg, reg::_name_reg[j], len)) {

                            _ARG.val[num_value] = j;

                                 if (isnumber (arg[1])) _ARG.sparseness[num_value] = 65;    // r8
                            else if (arg[0] == 'r')     _ARG.sparseness[num_value] = 64;    // rax
                            else if (arg[0] == 'e')     _ARG.sparseness[num_value] = 32;    // eax
                            else if (arg[1] == 'l')     _ARG.sparseness[num_value] = 8;     // al
                            else if (arg[1] == 'h')     _ARG.sparseness[num_value] = 8;     // ah
                            else                        _ARG.sparseness[num_value] = 16;    // ax

                            _ARG.val_on[0] = true;
                            if (_ARG.mem)
                                num_value++;
                            else
                                instr.num_args++;

                            break;
                        }
                }
            }

            instr.dump ();

            __word MC_cmd = createComand (instr);

            if (MC_cmd.word != nullptr) {
                printf ("%x\n", *(__uint32_t *) MC_cmd.word);
                free (MC_cmd.word);
            }
        }
    }

    return 0;
}

#define _first  instr.args[0]
#define _second instr.args[1]
#define _third  instr.args[2]

#define _MR (_first.mem && _second.val_on[0])
#define _RR (!_first.mem && _first.val_on[0] && _second.val_on[0])

__word createComand (instuction_t instr) {
    switch (instr.command) {
        case opcode::_cmds::MOV:
            assert (instr.num_args <= 2);

            if (_MR || _RR) {
                if (instr.sparseness == 8)
                    return genCmd (opcode::mov::movrm8_r8, instr);
                else
                    return genCmd (opcode::mov::movrm64_r64, instr);
            } else if (_RR || _MR) {
                if (instr.sparseness == 8)
                    return genCmd (opcode::mov::movr8_rm8, instr);
                else
                    return genCmd (opcode::mov::movr64_rm64, instr);
            }

            break;
        case opcode::_cmds::ADD:

            break;
        case opcode::_cmds::SUB:

            break;
        case opcode::_cmds::MUL:
            break;
        case opcode::_cmds::IMUL:
            break;
        case opcode::_cmds::IDIV:
            break;
        case opcode::_cmds::PUSH:
            break;
        case opcode::_cmds::POP:
            break;
        case opcode::_cmds::JMP:
            break;

        default:                    // Jcc
            break;
    }
}

__uint8_t _cmd_t::getSize (int sizeDisp, int sizeImm) {
    return (LegPref_On) * LegPref       +
           (REXPref_On) * REXPref       +
           (ModR_M_On ) * ModR_M        +
           (SIB_On    ) * SIB           +
           (Disp_On   ) * Disp          +
           (Imm_On    ) * Imm           +
           (true)       * Opcode.size;
}

__word _cmd_t::buildMC (int sizeDisp, int sizeImm) {
    assert (sizeDisp <= 4);
    assert (sizeImm  <= 4);

    __word mc;
    int temp_size = getSize (sizeDisp, sizeImm);
    mc.word = (char *) calloc (getSize (sizeDisp, sizeImm), sizeof (__uint8_t));

    __uint64_t *ytemp = (__uint64_t *) calloc (1, 8);
    *ytemp = 0x4889d8;

    int id = 0;
    if (LegPref_On)
        mc.word[id++] = LegPref;


    if (REXPref_On)
        mc.word[id++] = REXPref;

    if (Opcode.size == 3)
        mc.word[id++] = (Opcode.opcode & 0xff0000) >> 4 * 4;

    if (Opcode.size == 2)
        mc.word[id++] = (Opcode.opcode & 0x00ff00) >> 2 * 4;

    mc.word[id++] = (Opcode.opcode & 0x0000ff);

    if (ModR_M_On)
        mc.word[id++] = ModR_M;

    if (Disp_On) {
        if (sizeDisp == 1)
            *(__int8_t *) &mc.word[id] = (__int8_t) Disp;
        else if (sizeDisp == 2)
            *(__int16_t *) &mc.word[id] = (__int16_t) Disp;
        else
            *(__int32_t *) &mc.word[id] = (__int32_t) Disp;

        id += sizeDisp;
    }

    if (Imm_On) {
        if (sizeImm == 1)
            *(__int8_t *)  &mc.word[id] = (__int8_t)  Imm;
        else if (sizeImm == 2)
            *(__int16_t *) &mc.word[id] = (__int16_t) Imm;
        else
            *(__int32_t *) &mc.word[id] = (__int32_t) Imm;

        id += sizeImm;
    }

    for (int i = 0; i < temp_size / 2; i++) {
        char temp = mc.word[i];
        mc.word[i] = mc.word[temp_size - 1 - i];
        mc.word[temp_size - 1 - i] = temp;
    }

    return mc;
}

__word genCmd (opcode::__cmd command, instuction_t instr) {

    // Second arg not memory!!!

    _cmd_t cmd = {};

    cmd.Opcode = command;

    if (instr.args != nullptr) {

        // Legacy and REX prefixes
        if (_first.sparseness[0] == 16) {

            cmd.LegPref = _p66h;
            cmd.LegPref_On = true;

        } else if (_first.sparseness[0] > 16) {

            cmd.REXPref_On = true;
            cmd.REXPref = _REX (_w);

            if (_first.sparseness[0] == 65) cmd.REXPref |= _REX (_b);

            if (instr.num_args > 1)

                if (_second.sparseness[0] == 65) cmd.REXPref |= _REX (_r);

        }

        // ModR/M & SIB & Imm
        if (_first.mem == false) {

            if (_first.val_on[0]) {                     // First: register
                if (instr.num_args == 1)                // inc rax

                    cmd.ModR_M = ModR_M (mrm::reg, 0, reg::reg[_first.val[0]]);

                else if (instr.num_args == 2)           // mov rax, rbx; mov rax, 231

                    if (_second.val_on[0])              // Second: register

                        cmd.ModR_M = ModR_M (mrm::reg, reg::reg[_second.val[0]], reg::reg[_first.val[0]]);

                    else {                              // Imm

                        cmd.ModR_M = ModR_M (mrm::reg, 0, reg::reg[_first.val[0]]);
                        cmd.Imm = _second.val[2];
                        cmd.sizeImm = _second.sparseness[2];
                        cmd.Imm_On = true;

                    }
                else if (instr.num_args == 3) {     // mul rdx, rax, 4

                    cmd.ModR_M = ModR_M (mrm::reg, reg::reg[_second.val[0]], reg::reg[_first.val[0]]);
                    cmd.Imm = _third.val[2];
                    cmd.sizeImm = _second.sparseness[2];
                    cmd.Imm_On = true;

                }
                else
                    assert (0);

                cmd.ModR_M_On = true;
            } else {                                        // First Imm

                cmd.Imm = _first.val[2];
                cmd.sizeImm = _first.sparseness[2];
                cmd.Imm_On = true;

            }

        } else {                                            // First memory
            int mod = 0;

            if (_first.val_on[0] && _first.val_on[1]) {     // [ reg reg ...

                if (_first.val_on[2]) {                     // [ reg reg number]

                    cmd.Disp = _first.val[2];
                    cmd.Disp_On = true;
                    cmd.sizeDisp = _first.sparseness[2];

                    if (_first.sparseness[2] == 8)  mod = mrm::mod::disp8;
                    else                            mod = mrm::mod::disp32;

                } else                              mod = mrm::mod::disp0;  // [ reg reg ]

                cmd.ModR_M = ModR_M (mod, _second.val[0], _first.val[0]);
                cmd.ModR_M_On = true;

                cmd.SIB = _SIB (0, _first.val[0], _first.val[1]);
                cmd.SIB_On = true;

            } else if (_first.val_on[0]) {              // [ reg ...

                if (_first.val[0] != reg::sp) {         // sp == esp == rsp

                    if (_first.val_on[2]) {             // [ reg num ]

                        if (_first.sparseness[2] == 8) mod = mrm::mod::disp8;
                        else                           mod = mrm::mod::disp32;

                        cmd.Disp = _first.val[2];
                        cmd.sizeDisp = _first.sparseness[2];
                        cmd.Disp_On = true;

                        cmd.ModR_M = ModR_M (mod, 0, _first.val[0]);
                        cmd.ModR_M_On = true;

                    } else {                            // [ reg ]

                        if (_first.val[2] != reg::bp)

                            mod = mrm::mod::disp0;

                        else {

                            mod = mrm::mod::disp8;
                            cmd.Disp = 0;
                            cmd.Disp_On = true;

                        }

                        cmd.ModR_M = ModR_M (mod, 0, _first.val[0]);
                        cmd.ModR_M_On = true;
                    }
                }
            }
        }
/*
        //
        if (quant_args == 2) {
            if (args[0].type == arg_reg || args[1].type == arg_reg) {
                cmd.ModR_M = ModR_M (mrm::reg, reg::reg[args[1].arg], reg::reg[args[0].arg]);
                cmd.ModR_M_On = true;
            }
        }
*/
        /*
        if else {
            // Memory
        }*/

        return cmd.buildMC (0, 0);
    }

    return {0, nullptr};
}

void instuction_t::dump () {
    printf ("\n"
            "proces:      %d\n"
            "command:     %d\n"
            "extra_cmd:   %d\n"
            "sparseness:  %d\n"
            "num_args:    %d\n",
            proces, command,
            extra_cmd, sparseness,
            num_args);

    for (int i = 0; i < num_args; i++) {

        printf ("\n%d) mem = %d\n\n", i, args[i].mem);
        printf ("val:    %d\t%d\t%d\n", args[i].val[0], args[i].val[1], args[i].val[2]);
        printf ("sprs:   %d\t%d\t%d\n", args[i].sparseness[0], args[i].sparseness[1], args[i].sparseness[2]);
        printf ("val_on: %d\t%d\t%d\n", args[i].val_on[0], args[i].val_on[1], args[i].val_on[2]);

    }

    printf ("\n");
}