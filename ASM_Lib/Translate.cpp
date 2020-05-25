//
// Created by tester on 20.05.2020.
//

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include "Translate.h"
#include "ASM_Registers.h"
#include "ASM_Prefixes.h"
#include "ASM_ModR_M.h"
#include "../main_lib.h"
#include "ASM_SIB.h"
#include "directives.h"

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

    if (pow <= 7)
        return 8;
    else if (pow < 15)
        return 16;
    else if (pow < 31)
        return 32;
    else
        return 64;
}

// Correct: mov [rax rcx -89], 164
int Translate (SourceCodeNasm &code, bool dump) {

    __word *MC = (__word *) calloc (code.size_buf, sizeof (__int8_t));
    __uint32_t cur_pos = 0;
    labels_t labels (4096);
    labels_t cell_empty_labels (8192);
    FILE *temp_file = fopen ("temp_file", "wb");

    for (__uint32_t num_line = 0; num_line < code.number_lines; num_line++) {

        __word  word  = code.lines_code[num_line].words[0]; // Current word
        __word *words = code.lines_code[num_line].words;
        __uint8_t quant_words = code.lines_code[num_line].size;

        if (dump) {
            for (int i = 0; i < quant_words; i++)
                printf ("%s ", words[i].word);

            printf ("\t--> ");
        }

        instuction_t instr = {};

        // Get id commands
        instr.command = opcode::_cmds::__Quantity_Types_Commands;   // Set max value

        for (int i = 0; i < opcode::__Quantity_Types_Commands; i++)
            //if (!strcmp (tolower (word.word), opcode::_name_cmds[i])) {
            if (!strcmp (word.word, opcode::_name_cmds[i])) {
                instr.proces = proces::cp;
                instr.command = i;
                break;
            }

        //printf ("%s\n", opcode::_name_cmds[instr.command]);

        // If command
        if (instr.command < opcode::__Quantity_Types_Commands) {  // If command

            if (quant_words - 1 < 3)
                instr.args = (arg_t *) calloc (3, sizeof (arg_t));
            else
                instr.args = (arg_t *) calloc (quant_words - 1, sizeof (arg_t));
            
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

                            break;
                        } else {
                            printf ("Syntax error!!!\n");
                            free (instr.args);

                            return -1;
                        }
                    }

                if (extra) {
                    extra = false;
                    continue;
                }

                // Comment
                if (arg[0] == ';')
                    break;
                // Number
                else if (isnumber (arg[0]) || arg[0] == '-') {

                    __int64_t number = str2num (arg, len);
                    //printf ("NUMBER: %ld\n", number);
                    _ARG.val_on[2] = true;
                    _ARG.val[2] = number;

                    int temp_spr = getSparseness (number);
                    if (_ARG.sparseness[2] < temp_spr)
                        _ARG.sparseness[2] = temp_spr;

                    if (_ARG.mem == false) {  // For example: mov rax, 156
                        instr.num_args++;
                        break;
                    }

                } else if (arg[0] == '[') {

                    _ARG.mem = true;

                } else if (arg[0] == ']') {

                    instr.num_args++;
                    num_value = 0;

                } else {
                    bool _registrer = false;
                    int j = 0;
                    for (j = reg::quant_reg - 1; j >= 0; j--)   // Arg register
                        if (!strncmp (arg, reg::_name_reg[j], len)) {
                            _registrer = true;
                            break;
                        }

                    if (_registrer) {

                        _ARG.val[num_value] = reg::reg[j];

                        if (isnumber (arg[1]))  _ARG.sparseness[num_value] = 65;    // r8
                        else if (arg[0] == 'r') _ARG.sparseness[num_value] = 64;    // rax
                        else if (arg[0] == 'e') _ARG.sparseness[num_value] = 32;    // eax
                        else if (arg[1] == 'l') _ARG.sparseness[num_value] = 8;     // al
                        else if (arg[1] == 'h') _ARG.sparseness[num_value] = 8;     // ah
                        else                    _ARG.sparseness[num_value] = 16;    // ax

                        _ARG.val_on[num_value] = true;
                        if (_ARG.mem)
                            num_value++;
                        else
                            instr.num_args++;

                    } else {
                        _ARG.val_on[2] = true;                          // Arg label
                        _ARG.val[2] = 0;

                        _ARG.sparseness[2] = 32;

                        cell_empty_labels.add (code.lines_code[num_line].words[i], -1);
                        _ARG.label = &cell_empty_labels.label[cell_empty_labels.active_size - 1];
                        _ARG.label_on = true;

                        if (_ARG.mem == false) {  // For example: mov rax, 156
                            instr.num_args++;
                            break;
                        }
                    }
                }
            }

            if (dump)
                instr.dump ();

            instr.cur_pos = cur_pos;
            __word MC_cmd = createComand (instr);

            if (MC_cmd.word != nullptr) {
                for (int i = 0; i < MC_cmd.len; i++)
                    printf ("%02x", (__uint8_t) MC_cmd.word[i]);
                printf ("\n");
                //printf ("%x\n", *(__uint32_t *) MC_cmd.word);

                fwrite (MC_cmd.word, MC_cmd.len, 1, temp_file);
                cur_pos += MC_cmd.len;

                free (MC_cmd.word);
            } else
                assert (false);


        }
        else {

            // Comment
            if (word.word[0] == ';')
                continue;

            if (!strcmp (word.word, drctv::_name_directives[drctv::SECTION]))   // Ignor sections
                continue;

            if (labels.add (word, cur_pos) == false) {
                fprintf (stderr, "Double label \"%s\"!!!\n", word.word);
                fflush (stdout);
                throw std::runtime_error ("Fatal pcc error!");
            }

            if (quant_words > 1) {
                word = words[1];
                
                int num_dirtv = -1;
                for (int i = 0; i < 4; i++)
                    if (!strncmp (drctv::_name_directives[i], word.word, word.len)) {
                        num_dirtv = i;
                        break;
                    }

                if (num_dirtv != -1) {

                    int multiplicity = -1;
                    switch (num_dirtv) {
                        case drctv::DB: multiplicity = 1;   break;
                        case drctv::DW: multiplicity = 2;   break;
                        case drctv::DD: multiplicity = 4;   break;
                        case drctv::DQ: multiplicity = 8;   break;
                    }
                    if (multiplicity == -1)
                        break;

                    for (int i = 2; i < quant_words; i++) {

                        if (words[i].word[0] == ';')
                            break;

                        if (words[i].word[0] == '\"') {             // STRING
                            fwrite (words[i].word + 1, words[i].len - 1, sizeof (char), temp_file);
                            fprintf (temp_file, "%c", '\0');

                            // Align
                            int align = words[i].len % multiplicity;
                            __uint64_t templ_zero = 0;

                            fwrite (&templ_zero, align, sizeof (char), temp_file);

                            cur_pos += words[i].len + align;
                        } else {                                    // NUMBER
                            __int64_t _number = str2num (words[i].word);
                            switch (multiplicity) {
                                case 2: {
                                    __int16_t num16 = _number;
                                    fwrite (&num16, 1, sizeof (__int16_t), temp_file);
                                    break;
                                }
                                case 4: {
                                    __int32_t num32 = _number;
                                    fwrite (&num32, 1, sizeof (__int32_t), temp_file);
                                    break;
                                }
                                case 8: {
                                    __int64_t num64 = _number;
                                    fwrite (&num64, 1, sizeof (__int64_t), temp_file);
                                    break;
                                }
                            }

                            cur_pos += multiplicity;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < labels.active_size; i++)
        printf ("%d) %s\n", labels.label[i].position, labels.label[i].name.word);
    fclose (temp_file);

    return 0;
    }


#define _first  instr.args[0]
#define _second instr.args[1]
#define _third  instr.args[2]

#define _MR ( _first.mem && !_second.mem && _second.val_on[0])
#define _MI ( _first.mem && !_second.mem && _second.val_on[2])

#define _RM (!_first.mem &&  _second.mem && _first.val_on[0])
#define _RR (!_first.mem && !_second.mem && _first.val_on[0] && _second.val_on[0])
#define _RI (!_first.mem && !_second.mem && _first.val_on[0] && _second.val_on[2])

#define _R_RM_I (!_first.mem && _first.val_on[0] && _third.val_on[2])
#define _R_or_M (instr.num_args == 1)

// Stupid contractions
#define _R  (!_first.mem && _first.val_on[0])
#define _M  ( _first.mem)
#define _I  (!_first.mem && _first.val_on[2])

#define GenerateCmd(spars8, spars64) {                                                      \
                                         if (_first.sparseness[0] == 8)                     \
                                            return genCmd (opcode:: spars8, instr);         \
                                         else                                               \
                                            return genCmd (opcode:: spars64, instr);        \
                                     }

__word GenShortCmd (__uint32_t command, instuction_t instr) {

    __word mc;
    if (_first.sparseness[0] == 65) {

        mc.len = 2;
        mc.word = (char *) calloc (mc.len, sizeof (__uint8_t));
        mc.word[0] = _REX (_b);
        mc.word[1] = command | _first.val[0];

    } else {

        mc.len = 1;
        mc.word = (char *) calloc (mc.len, sizeof (__uint8_t));
        mc.word[0] = command | _first.val[0];

    }

    return mc;
}

__word createComand (instuction_t instr) {
    switch (instr.command) {
        case opcode::_cmds::MOV:
            assert (instr.num_args <= 2);

            if (_MR || _RR)     GenerateCmd (mov::rm8_r8, mov::rm64_r64)
            else if (_RM) {
                arg_t temp_arg = _second;
                _second = _first;
                _first = temp_arg;

                                GenerateCmd (mov::r8_rm8, mov::r64_rm64)
            }
            else if (_RI)       GenerateCmd (mov::r8_i8,  mov::r64_i64)
            else if (_MI)       GenerateCmd (mov::rm8_i8, mov::rm64_i64)

            break;
        case opcode::_cmds::ADD:
            if (_MR || _RR)     GenerateCmd (add::rm8_r8, add::rm64_r64)
            else if (_RM) {
                arg_t temp_arg = _second;
                _second = _first;
                _first = temp_arg;

                                GenerateCmd (add::r8_rm8, add::r64_rm64)
            }
            else if (_RI)       GenerateCmd (add::r8_i8,  add::r64_i64)
            else if (_MI)       GenerateCmd (add::rm8_i8, add::rm64_i64)

            break;
        case opcode::_cmds::SUB:
            if (_MR || _RR)     GenerateCmd (sub::rm8_r8, sub::rm64_r64)
            else if (_RM) {
                arg_t temp_arg = _second;
                _second = _first;
                _first = temp_arg;

                                GenerateCmd (sub::r8_rm8, sub::r64_rm64)
            }
            else if (_RI)       GenerateCmd (sub::r8_i8,  sub::r64_i64)
            else if (_MI)       GenerateCmd (sub::rm8_i8, sub::rm64_i64)

            break;
        case opcode::_cmds::MUL:
                                GenerateCmd (mul::rm8,    mul::rm64)
            break;
        case opcode::_cmds::DIV:
                                GenerateCmd (div::rm8,    div::rm64)
            break;
        case opcode::_cmds::IMUL:
                 if (_R_RM_I)   {
                     arg_t temp_arg = _second;
                     _second = _first;
                     _first = temp_arg;
                     GenerateCmd (imul::r16_rm_i8, imul::r_rm_i64)
                 }
            else if (_R_or_M)   GenerateCmd (imul::rm8, imul::rm64)
            else {
                 if (_RI)       GenerateCmd (imul::r16_i8, imul::r_i64)
                 else if (_RM || _RR) {
                     arg_t temp_arg = _second;
                     _second = _first;
                     _first = temp_arg;
                                GenerateCmd (imul::r_rm16, imul::r_rm64)
                    }
                 }
            break;
        case opcode::_cmds::IDIV:
                                GenerateCmd (idiv::rm8, idiv::rm64)
            break;
        case opcode::_cmds::PUSH:
                     if (_R)    GenerateCmd (push::r8,  push::r64)
                else if (_M)    GenerateCmd (push::rm8, push::rm64)
            break;
        case opcode::_cmds::POP:
            if (_R)    return   GenShortCmd (opcode::pop::r64.opcode, instr);
            if (_M) {
               if (instr.extra_cmd == 3)
                                GenerateCmd (pop::m64, pop::m64)
               else
                   printf ("Error: operation size not specified!");
            }
            break;
        case opcode::_cmds::NOP:
                        return  GenShortCmd (opcode::nop.opcode, instr);
            break;
        case opcode::_cmds::RET:
                        return  GenShortCmd (opcode::ret::ret_near.opcode, instr);
            break;
        case opcode::_cmds::JMP:
            if (_R || _M)       GenerateCmd (jmp::rm16, jmp::rm64)
            if (_I) {
                if (_first.sparseness[2] < 32)
                    _first.sparseness[2] = 32;
                                _first.val[2] -= 4;
                                GenerateCmd (jmp::rel8, jmp::rel32)
            }
            break;
        default:                    // Jcc
            if (_I) {
                _first.val[2] -= 4;
                if (_first.sparseness[2] < 32)
                    _first.sparseness[2] = 32;
                switch (instr.command) {

#define GenCmd(_opcode)  return genCmd (opcode::jcc:: _opcode, instr);

                    case opcode::_cmds::JA:   GenCmd (ja_n)
                    case opcode::_cmds::JAE:  GenCmd (jae_n)
                    case opcode::_cmds::JB:   GenCmd (jb_n)
                    case opcode::_cmds::JBE:  GenCmd (jbe_n)
                    case opcode::_cmds::JC:   GenCmd (jc_n)
                    case opcode::_cmds::JE:   GenCmd (je_n)
                    case opcode::_cmds::JG:   GenCmd (jg_n)
                    case opcode::_cmds::JGE:  GenCmd (jge_n)
                    case opcode::_cmds::JL:   GenCmd (jl_n)
                    case opcode::_cmds::JLE:  GenCmd (jle_n)
                    case opcode::_cmds::JNA:  GenCmd (jna_n)
                    case opcode::_cmds::JNAE: GenCmd (jnae_n)
                    case opcode::_cmds::JNB:  GenCmd (jnb_n)
                    case opcode::_cmds::JNBE: GenCmd (jnbe_n)
                    case opcode::_cmds::JNC:  GenCmd (jnc_n)
                    case opcode::_cmds::JNE:  GenCmd (jne_n)
                    case opcode::_cmds::JNG:  GenCmd (jng_n)
                    case opcode::_cmds::JNGE: GenCmd (jnge_n)
                    case opcode::_cmds::JNL:  GenCmd (jnl_n)
                    case opcode::_cmds::JNLE: GenCmd (jnle_n)
                    case opcode::_cmds::JNO:  GenCmd (jno_n)
                    case opcode::_cmds::JNP:  GenCmd (jnp_n)
                    case opcode::_cmds::JNS:  GenCmd (jns_n)
                    case opcode::_cmds::JNZ:  GenCmd (jnz_n)
                    case opcode::_cmds::JO:   GenCmd (jo_n)
                    case opcode::_cmds::JP:   GenCmd (jp_n)
                    case opcode::_cmds::JPE:  GenCmd (jpe_n)
                    case opcode::_cmds::JPO:  GenCmd (jpo_n)
                    case opcode::_cmds::JS:   GenCmd (js_n)
                    case opcode::_cmds::JZ:   GenCmd (jz_n)

#undef GenCmd
                    default:
                        break;
                }
            }
            break;
    }

    printf ("Syntax error!!! Error translate this code. Abort!");
    __word empty_word;
    empty_word.word = nullptr;
    empty_word.len  = -1;

    return empty_word;
}

__uint8_t _cmd_t::getSize () {
    return (LegPref_On)                 +
           (REXPref_On)                 +
           (ModR_M_On )                 +
           (SIB_On    )                 +
           (Disp_On   ) * sizeDisp      +
           (Imm_On    ) * sizeImm       +
           (true)       * Opcode.size;
}

__word _cmd_t::buildMC (__uint32_t cur_pos) {
    assert (sizeDisp <= 4);
    assert (sizeImm  <= 8);

    __word mc;
    int temp_size = getSize ();
    mc.word = (char *) calloc (getSize (), sizeof (__uint8_t));
    mc.len = temp_size;

    int id = 0;
    if (LegPref_On)
        mc.word[id++] = LegPref;

    if (REXPref_On)
        mc.word[id++] = REXPref;

    if (Opcode.size + Opcode.ext == 4)
        mc.word[id++] = (Opcode.opcode & 0xff000000) >> 6 * 4;

    if (Opcode.size + Opcode.ext == 3)
        mc.word[id++] = (Opcode.opcode & 0x00ff0000) >> 4 * 4;

    if (Opcode.size + Opcode.ext == 2)
        mc.word[id++] = (Opcode.opcode & 0x0000ff00) >> 2 * 4;

    mc.word[id++] = (Opcode.opcode & 0x000000ff);
    if (Opcode.ext) id--;

    if (ModR_M_On)
        mc.word[id++] |= ModR_M;

    if (SIB_On)
        mc.word[id++] |= SIB;

    if (Disp_On) {
        if (sizeDisp == 1)
            *(__int8_t *)  &mc.word[id] |= (__int8_t) Disp;
        else if (sizeDisp == 2)
            *(__int16_t *) &mc.word[id] |= (__int16_t) Disp;
        else
            *(__int32_t *) &mc.word[id] |= (__int32_t) Disp;

        if (DispLabel_On) DispLabel->position = id + cur_pos;

        id += sizeDisp;
    }

    if (Imm_On) {
        if (sizeImm == 1)
            *(__int8_t *)  &mc.word[id] |= (__int8_t)  Imm;
        else if (sizeImm == 2)
            *(__int16_t *) &mc.word[id] |= (__int16_t) Imm;
        else
            *(__int32_t *) &mc.word[id] |= (__int32_t) Imm;

        if (ImmLabel_On) ImmLabel->position = id + cur_pos;

        id += sizeImm;
    }
/*
    for (int i = 0; i < temp_size / 2; i++) {
        char temp = mc.word[i];
        mc.word[i] = mc.word[temp_size - 1 - i];
        mc.word[temp_size - 1 - i] = temp;
    }
*/
    return mc;
}

__word genCmd (opcode::__cmd command, instuction_t instr) {
    // TODO byte, word, dword, qword
    // Second arg not memory!!!

    _cmd_t cmd = {};

    cmd.Opcode = command;

    if (instr.args != nullptr) {

        // Legacy and REX prefixes
        if (_first.sparseness[0] == 16) {

            cmd.LegPref = _p66h;
            cmd.LegPref_On = true;

        } else if (_first.sparseness[0] == 32 && _first.mem) {

            cmd.LegPref = _p67h;
            cmd.LegPref_On = true;

        } else if (_first.sparseness[0] > 32) {

            cmd.REXPref_On = true;
            cmd.REXPref = _REX (_w);

            if (_first.sparseness[0]  == 65) cmd.REXPref |= _REX (_b);
            if (_first.sparseness[1]  == 65) cmd.REXPref |= _REX (_x);
            if (_second.sparseness[0] == 65) cmd.REXPref |= _REX (_r);

        }

        for (int i = 0; i < 3; i++) {
            _first.sparseness[i]  /= 8;
            _second.sparseness[i] /= 8;
            _third.sparseness[i]  /= 8;
        }
        // Early building strategy

        cmd.ModR_M = ModR_M (0, _second.val[0], _first.val[0]);
        cmd.SIB = _SIB (sib::scl1, _first.val[1], _first.val[0]);

        // Only one of them can exist. Nonexistents equal by zero
        cmd.Imm     = _second.val[2]        + _third.val[2];
        cmd.sizeImm = _second.sparseness[2] + _third.sparseness[2];

        cmd.sizeImm = fmax (cmd.sizeImm, _first.sparseness[0]);             // Because x86_64

        cmd.Disp     = _first.val[2];
        if (_first.sparseness[2] > 4)
            throw std::runtime_error (" warning: dword data exceeds bounds!");

             if (_first.sparseness[2] == 1) cmd.sizeDisp = 1;               // Because
        else if (_first.sparseness[2]  > 1) cmd.sizeDisp = 4;               // x86_64

        if (_first.val_on[0]) cmd.ModR_M_On = true;                         // Enable or Ignore ModR/M
        if (_second.val_on[2] || _third.val_on[2]) cmd.Imm_On = true;       // Enable or Ignore Imm

        if (_first.mem == false) {                                          // Reg or Imm

            cmd.ModR_M |= ModR_M (mrm::reg);

            cmd.Imm     += _first.val[2];
            cmd.sizeImm += _first.sparseness[2];

            if (_first.val_on[2] || _second.val_on[2] || _third.val_on[2]) cmd.Imm_On = true;

        } else {                                                            // Memroy
            // Enable or Ignore SIB
            // We know that mod != 11
            if ((_first.val_on[0] && _first.val[1]) ||                                  // [ reg reg ... ] ||
                (_first.val[0] == reg::_reg::rsp || _first.val[1] == reg::_reg::rsp))   // [ rsp ... ... ] ||
            {                                                                           // [ ... rsp ... ]

                cmd.SIB_On = true;

                if (_first.val[1] == reg::_reg::rsp)
                    cmd.SIB = _SIB (sib::scl1, _first.val[0], _first.val[1]);

                cmd.ModR_M &= ModR_M (0b11, 0b111, 0b000);      // R/M -> 0
                cmd.ModR_M += 0b100;                            // Enable SIB
            }

            if (_second.val_on[2] || _third.val_on[2]) cmd.Imm_On = true;   // Enable or Ignore Imm

            if (_first.val_on[2]) cmd.Disp_On = true;                       // Enable or Ignore Disp

            if (_first.val_on[2]) {                                         // Enable or Ignore ModR/M

                if (_first.sparseness[2] == 1) cmd.ModR_M |= ModR_M (mrm::disp8);
                else                           cmd.ModR_M |= ModR_M (mrm::disp32);

            } else if (_first.val[0] == reg::_reg::rbp || _first.val[1] == reg::_reg::rbp) {

                cmd.ModR_M |= ModR_M (mrm::disp8);

                cmd.Disp_On = true;
                cmd.Disp = 0;

            }

            if (_first.val_on[1] == false)  {
                cmd.SIB &= 0b11000111;
                cmd.SIB += 0b00100000;
            }

            // Enable labels. For example mov [rax + r12 + my_label_0], my_label_1
            if (instr.num_args < 3) {
                if (_first.label_on) {
                    cmd.DispLabel_On = true;
                    cmd.DispLabel = _first.label;
                }
                if (_second.label_on) {
                    cmd.ImmLabel_On = true;
                    cmd.ImmLabel = _second.label;
                    cmd.sizeImm = 4;
                }
            } else {
                if (_second.label_on) {
                    cmd.DispLabel_On = true;
                    cmd.DispLabel = _second.label;
                }
                if (_third.label_on) {
                    cmd.ImmLabel_On = true;
                    cmd.ImmLabel = _third.label;
                    cmd.sizeImm = 4;
                }
            }

        }

        return cmd.buildMC (instr.cur_pos);
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
        printf ("val:    %ld\t%ld\t%ld\n", args[i].val[0], args[i].val[1], args[i].val[2]);
        printf ("sprs:   %d\t%d\t%d\n", args[i].sparseness[0], args[i].sparseness[1], args[i].sparseness[2]);
        printf ("val_on: %d\t%d\t%d\n", args[i].val_on[0], args[i].val_on[1], args[i].val_on[2]);
        printf ("lbl_on: %d\t", args[i].label_on);
        if (args[i].label != nullptr) fwrite (args[i].label->name.word, args[i].label->name.len, 1, stdout);
        printf ("\n");

    }

    printf ("\n");
}

labels_t::labels_t (__uint32_t size) :
    label ((label_t *) calloc (size, sizeof (label_t))),
    total_size (size),
    active_size (0)
{
    assert (size > 0);
}

bool labels_t::add (__word name, __uint32_t pos) {
    assert (active_size <= total_size);

    if (find (name) >= 0)
        return false;

    label[active_size].position = pos;
    label[active_size++].name = name;

    return true;
}

__int64_t labels_t::find (__word name) {

    char *_name = name.word;

    for (__uint32_t i = 0; i < active_size; i++)
        if (!strncmp (_name, label[i].name.word, name.len))
            return i;

    return -1;
}

_cmd_t::_cmd_t () :
        LegPref     (0),
        REXPref     (0),
        ModR_M      (0),
        SIB         (0),
        Disp        (0),
        Imm         (0),
        sizeImm     (0),
        sizeDisp    (0),
        LegPref_On  (false),
        REXPref_On  (false),
        ModR_M_On   (false),
        SIB_On      (false),
        Disp_On     (false),
        Imm_On      (false)
{

}
#undef _RI
#undef _RR
#undef _RM
#undef _MI
#undef _MR

#undef _third
#undef _second
#undef _first