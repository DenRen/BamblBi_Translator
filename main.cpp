#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include "main_lib.h"
#include "ASM_Lib/Translate.h"



int main () {

    const char path_asm[] = "../asm/test.s";
    SourceCodeNasm code (path_asm);

    if (Translate (code))
        fprintf (stderr, "Fail\n");

    return 0;
}

// 010010001 11101111 1100000
// 010010001 11101101 1100000





























