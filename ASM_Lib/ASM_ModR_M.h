//
// Created by tester on 19.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_ASM_MODR_M_H
#define BAMBLBI_TRANSLATOR_ASM_MODR_M_H

#include <cassert>
#include "zlib.h"

namespace mrm {     // ModeR/M
    enum mod {
        disp0  =    0b00,
        disp8  =    0b01,
        disp32 =    0b10,
        reg    =    0b11
    };

    enum r_m {
        _rax,
        _rcx,
        _rdx,
        _rbx,

        _SIB,
        desp32,

        _rsi,
        _rdi
    };
}

/*
             #====#====#====#====#====#====#====#====#
   ModR/M =  #   Mod   #  Reg/Opcode  #      R/M     #  <-- 1 byte
             #====#====#====#====#====#====#====#====#
                   2          3              3
*/
__uint8_t ModR_M (__uint8_t mod, __uint8_t reg2_opcode, __uint8_t reg1_memory) {
    assert (mod < 4);
    assert (reg2_opcode < 8);
    //assert (reg1_memory < 8);

    return (mod << 6) | reg2_opcode << 3 | reg1_memory;
}

#endif //BAMBLBI_TRANSLATOR_ASM_MODR_M_H
