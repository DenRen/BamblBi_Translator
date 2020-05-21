//
// Created by tester on 20.05.2020.
//

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "Translate.h"
#include "ASM_Registers.h"
#include "ASM_Prefixes.h"
#include "ASM_ModR_M.h"
#include "../main_lib.h"

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

int Translate (SourceCodeNasm code) {

    for (__uint32_t num_line = 0; num_line < code.number_lines; num_line++) {


        __word word = code.lines_code[num_line].words[0]; // Current word
        __uint8_t quant_words = code.lines_code[num_line].size;

        __word *words = code.lines_code[num_line].words;

        printf ("%2d: ", num_line);
        for (int i = 0; i < quant_words; i++)
            printf ("%s ", words[i].word);

        printf ("\t--> ");

        // Get id commands
        __uint8_t command = opcode::_cmds::__Quantity_Types_Commands;

        for (int i = 0; i < opcode::__Quantity_Types_Commands; i++)
            if (!strcmp (tolower (word.word), opcode::_name_cmds[i])) {
                command = i;
                break;
            }


        printf ("%s\n", opcode::_name_cmds[command]);

        arg_t *args = (arg_t *) calloc (quant_words - 1, sizeof (arg_t));

        if (command < opcode::__Quantity_Types_Commands) {  // If command

            __uint8_t i = 1;
            for (i = 1; i < quant_words; i++) {
                char *arg = code.lines_code[num_line].words[i].word;

                if (arg[0] == ';') {
                    i--;
                    break;
                }

                else if (isnumber (arg[0])) {

                    args[i - 1].type = arg_imm;
                    args[i - 1].arg = (__int64_t) arg;  // In special function it will be encoding

                } else if (arg[0] == '[')
                    printf ("Memory");

                else {
                    for (int j = reg::quant_reg - 1; j >= 0; j--)   // Arg register
                        if (!strcmp (arg, reg::_name_reg[j])) {
                            args[i - 1].type = arg_reg;
                            args[i - 1].arg = j;

                                 if (isnumber (arg[1])) args[i - 1].sparseness = 65;    // r8
                            else if (arg[0] == 'r')     args[i - 1].sparseness = 64;    // rax
                            else if (arg[0] == 'e')     args[i - 1].sparseness = 32;    // eax
                            else if (arg[1] == 'l')     args[i - 1].sparseness = 8;     // al
                            else if (arg[1] == 'h')     args[i - 1].sparseness = 8;     // ah
                            else                        args[i - 1].sparseness = 16;    // ax
                            break;
                        }

                }
            }

            __word MC_cmd = createComand (command, args, i - 1);
            free (MC_cmd.word);
        }

    }

    return 0;
}


__word createComand (__uint8_t command, arg_t *args, int quant_args) {
    switch (command) {
        case opcode::_cmds::MOV:
            assert (quant_args == 2);
            assert (args != nullptr && args + 1 != nullptr);

#define ARG(arg1, arg2) (args[0].type == arg1 && args[1].type == arg2)

            if (ARG (arg_mem, arg_reg) || ARG (arg_reg, arg_reg)) {
                _cmd_t cmd = {};

                if (args[0].sparseness == 8) {
                    cmd.Opcode = opcode::mov::movrm8_r8;

                } else if (args[0].sparseness == 16) {
                    cmd.Opcode = opcode::mov::movrm16_r16;

                    cmd.LegPref = _p66h;
                    cmd.LegPref_On = true;
                } else {
                    cmd.Opcode = opcode::mov::movrm64_r64;

                    cmd.REXPref_On = true;
                    cmd.REXPref = _REX (_w);

                    if (args[0].sparseness == 65) cmd.REXPref |= _REX (_b);

                    if (args[1].sparseness == 65) cmd.REXPref |= _REX (_r);
                }

                if (args[0].type == arg_reg) {
                    cmd.ModR_M = ModR_M (mrm::reg, reg::reg[args[1].arg], reg::reg[args[0].arg]);
                    cmd.ModR_M_On = true;
                } else {
                    // Memory
                }

                __word mc = cmd.buildMC (0, 0);
                printf ("%x\n", *(__uint32_t *) mc.word);
                return mc;
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
    return (LegPref != 0) +
           (REXPref != 0) +
           (Opcode.size ) +
           (ModR_M  != 0) +
           (SIB     != 0) +
           sizeDisp + sizeImm;
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
