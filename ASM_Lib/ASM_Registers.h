//
// Created by tester on 19.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_ASM_REGISTERS_H
#define BAMBLBI_TRANSLATOR_ASM_REGISTERS_H

// General purpose registers

enum reg {

    ax = 0b000,
    cx = 0b001,
    dx = 0b010,
    bx = 0b011,
    sp = 0b100,
    bp = 0b101,
    si = 0b110,
    di = 0b111,

    al = ax,
    cl = cx,
    dl = dx,
    bl = bx,
    ah = sp,
    ch = bp,
    dh = si,
    bh = di,

    // Segment registers

    es = ax,
    cs = cx,
    ss = dx,
    ds = bx,
    fs = sp,
    gs = bp,

    // General purpose registers x32, x64

    eax = ax,
    ecx = cx,
    edx = dx,
    ebx = bx,
    esp = sp,
    ebp = bp,
    esi = si,
    edi = di,

    rax = ax,
    rcx = cx,
    rdx = dx,
    rbx = bx,
    rsp = sp,
    rbp = bp,
    rsi = si,
    rdi = di,

    r8  = ax,
    r9  = cx,
    r10 = dx,
    r11 = bx,
    r12 = sp,
    r13 = bp,
    r14 = si,
    r15 = di

};

#endif //BAMBLBI_TRANSLATOR_ASM_REGISTERS_H
