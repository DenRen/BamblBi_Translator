//
// Created by tester on 19.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_ASM_PREFIXES_H
#define BAMBLBI_TRANSLATOR_ASM_PREFIXES_H

// [Legacy prefixes]----------------------------------------------------------------------------------------------------

// Group 1
#include <stdint.h>

#define lock    0xF0
#define repne   0xF2
#define repnz   0xF3

// Group 2
#define _pCS    0x2E
#define _pSS    0x36
#define _pDS    0x3E
#define _pES    0x26
#define _pFS    0x64
#define _pGS    0x65

// Group 3
#define _p66h    0x66

//Group 4
#define _p67h   0x67

// [REX Prefix]---------------------------------------------------------------------------------------------------------

#define _w  0b1000
#define _r  0b0100
#define _x  0b0010
#define _b  0b0001


__uint8_t _REX (__uint8_t type1, __uint8_t type2 = 0, __uint8_t type3 = 0, __uint8_t type4 = 0);

#endif //BAMBLBI_TRANSLATOR_ASM_PREFIXES_H
