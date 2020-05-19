//
// Created by tester on 18.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_ASM_MC_H
#define BAMBLBI_TRANSLATOR_ASM_MC_H

/*
 mov rax, rbx 48 89 d8
 mov rdi, rax 48 89 c7

 11000000 mov rax, rax  ||  11000011 mov rbx, rax    ||     rax 000
 11011000 mov rax, rbx  ||  11011011 mov rbx, rbx    ||     rbx 011
 11001000 mov rax, rcx  ||  11001011 mov rbx, rcx    ||     rcx 001
 11010000 mov rax, rdx  ||  11010011 mov rbx, rdx    ||     rdx 010
 11110000 mov rax, rsi  ||  11110011 mov rbx, rsi    ||     rsi 110
 11111000 mov rax, rdi  ||  11111011 mov rbx, rdi    ||     rdi 111
 11100000 mov rax, rsp  ||  11100011 mov rbx, rsp    ||     rsp 100
 11101000 mov rax, rbp  ||  11101011 mov rbx, rbp    ||     rbp 101

 000 0b
 000 0b
 000 0b
 000 0b
 000 0b
 000 0b
 000 0b
 000 0b
 000 0b
 000 0b

 11100000
 11100011
 11100001
 11100010

 */
namespace nasmmc {

    /*
             11011000
             00000011
             00011000

    100010 01 11 011000   // mov rax,   rbx
    100010 11 00 000011   // mov rax,  [rbx]
    100010 01 00 011000   // mov [rax], rbx

    100010 11 01 000011   // mov rax, [rbx + 1]      // short
    100010 11 10 000011   // mov rax, [rbx + 128]    // far



    000000 01 11 011000   // add rax,   rbx
    000000 11 00 000011   // add rax,  [rbx]
    000000 01 00 011000   // add [rax], rbx

    001110 01 11 011000
    001110 11 00 000011
    001110 01 00 011000
    */

    // TODO IMUL
    //                             vv <- Registers
    #define MOV(regL, regR)  0x008900 | 0b11000000 | (0xff & regR << 3) | regL
    #define ADD(regL, regR)  0x000100 | 0b11000000 | (0xff & regR << 3) | regL
    #define SUB(regL, regR)  0x002900 | 0b11000000 | (0xff & regR << 3) | regL
    #define CMP(regL, regR)  0x003900 | 0b11000000 | (0xff & regR << 3) | regL
    #define TEST(regL, regR) 0x008500 | 0b11000000 | (0xff & regR << 3) | regL

    #define AND(regL, regR)  0x002100 | 0b11000000 | (0xff & regR << 3) | regL
    #define XOR(regL, regR)  0x003100 | 0b11000000 | (0xff & regR << 3) | regL
    #define OR(regL, regR)   0x000900 | 0b11000000 | (0xff & regR << 3) | regL
    #define NOT(reg)         0x00f700 | 0b11010000 | (0x0f & reg)

    #define MUL(reg)         0x00f700 | 0b11100000 | reg
    #define DIV(reg)         0x00f700 | 0b11110000 | reg

    #define PUSH(reg)        0x50     | 0b00000000 | (0x0f & reg)
    #define POP(reg)         0x50     | 0b00001000 | (0x0f & reg)

    #define INC(reg)         0x00ffc0 | 0b11000000 | reg
    #define DEC(reg)         0x00ffc0 | 0b11001000 | reg

    #include "ASM_MC_JMPs.h"

    #define LOOP             0xe2
    #define LOOPE            0xe1
    #define LOOPNE           0xe0
    #define LOOPZ            LOOPE
    #define LOOPNZ           LOOPNE

    #define CALL             0xe800000000   // == call 5, len command 5
    #define SYSCALL          0x0f05
    #define NOP              0x90
    #define RET              0xc3

    #define INC32(reg)       0x40     | 0b00000000 | (0x0f & reg)
    #define DEC32(reg)       0x40     | 0b00001000 | (0x0f & reg)

    #define rax 0x480000 | 0b000000
    #define rbx 0x480000 | 0b000011
    #define rcx 0x480000 | 0b000001
    #define rdx 0x480000 | 0b000010
    #define rsi 0x480000 | 0b000110
    #define rdi 0x480000 | 0b000111
    #define rsp 0x480000 | 0b000100
    #define rbp 0x480000 | 0b000101

    #define eax 0x000000 | 0b000000
    #define ebx 0x000000 | 0b000011
    #define ecx 0x000000 | 0b000001
    #define edx 0x000000 | 0b000010
    #define esi 0x000000 | 0b000110
    #define edi 0x000000 | 0b000111
    #define esp 0x000000 | 0b000100
    #define ebp 0x000000 | 0b000101

    // Above function only for 32 or 64 bits registers

    #define  ax 0x660000 | 0b000000
    #define  bx 0x660000 | 0b000011
    #define  cx 0x660000 | 0b000001
    #define  dx 0x660000 | 0b000010
    #define  si 0x660000 | 0b000110
    #define  di 0x660000 | 0b000111
    #define  sp 0x660000 | 0b000100
    #define  bp 0x660000 | 0b000101


    // TODO x16 asm ????? ?????????? ? ?????????????? ?????
    // For .l and .h please use command with underline _
    // For example: _mov ah, al
    //              _mul cl

    #define al 0x48 | 0b0000000
    #define bl 0x48 | 0b0000011
    #define cl 0x48 | 0b0000001
    #define dl 0x48 | 0b0000010

    #define ah 0x48 | 0b1000000
    #define bh 0x48 | 0b1000011
    #define ch 0x48 | 0b1000001
    #define dh 0x48 | 0b1000010

}

#endif //BAMBLBI_TRANSLATOR_ASM_MC_H
