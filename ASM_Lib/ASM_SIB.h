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

__uint8_t _sib (__uint8_t Scale, reg Index, reg Base) {
    assert (Scale < 4);
    assert (Index < 8);
    assert (Base  < 8);

    return (Scale << 6) | (Index << 3) | Base;
}

#endif //BAMBLBI_TRANSLATOR_ASM_SIB_H

