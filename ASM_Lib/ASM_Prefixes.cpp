//
// Created by tester on 19.05.2020.
//

#include "ASM_Prefixes.h"

#define __REX   0b01000000

#define _REX1(type)                       __REX | (_w * (_w == type)) \
                                                | (_r * (_r == type)) \
                                                | (_x * (_x == type)) \
                                                | (_b * (_b == type))

#define _REX2(type1, type2)               __REX | (_w * (_w == type1 || _w == type2)) \
                                                | (_r * (_r == type1 || _r == type2)) \
                                                | (_x * (_x == type1 || _x == type2)) \
                                                | (_b * (_b == type1 || _b == type2))

#define _REX3(type1, type2, type3)        __REX | (_w * (_w == type1 || _w == type2 || _w == type3)) \
                                                | (_r * (_r == type1 || _r == type2 || _r == type3)) \
                                                | (_x * (_x == type1 || _x == type2 || _x == type3)) \
                                                | (_b * (_b == type1 || _b == type2 || _b == type3))

#define _REX4(type1, type2, type3, type4) __REX | (_w * (_w == type1 || _w == type2 || _w == type3 || _w == type4)) \
                                                | (_r * (_r == type1 || _r == type2 || _r == type3 || _r == type4)) \
                                                | (_x * (_x == type1 || _x == type2 || _x == type3 || _x == type4)) \
                                                | (_b * (_b == type1 || _b == type2 || _b == type3 || _b == type4))

__uint8_t _REX (__uint8_t type1, __uint8_t type2, __uint8_t type3, __uint8_t type4) {
    return _REX4 (type1, type2, type3, type4);
}

#undef _REX4
#undef _REX3
#undef _REX3
#undef _REX1
#undef __REX