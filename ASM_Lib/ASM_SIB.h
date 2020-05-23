//
// Created by tester on 19.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_ASM_SIB_H
#define BAMBLBI_TRANSLATOR_ASM_SIB_H


#include <cstdint>
#include <cassert>
#include "ASM_Registers.h"

/*
          #====#====#====#====#====#====#====#====#
   SIB =  #  Scale  #    Index     #     Base     #  <-- 1 byte
          #====#====#====#====#====#====#====#====#
                   2            3              3

   Effective Address:
        EA = Disp + Base + Index * Scale;

 */

namespace sib {

    enum {
        scl1,       // 00 -> Scale == 1
        scl2,       // 01 -> Scale == 2
        scl4,       // 10 -> Scale == 4
        scl8        // 11 -> Scale == 8
    };

}

__uint8_t _SIB (__uint8_t Scale, __uint8_t Index, __uint8_t Base) {
    assert (Scale < 4);
    assert (Index < 8);
    assert (Base  < 8);

    return (Scale << 6) | (Index << 3) | Base;
}

#endif //BAMBLBI_TRANSLATOR_ASM_SIB_H

