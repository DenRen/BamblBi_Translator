#include <cstdio>
#include <cstdlib>
#include <cctype>
#include "main_lib.h"
#include "ASM_MC_new.h"
#include "ASM_commands_name.h"

int main () {

    const char path_asm[] = "../asm/test2.s";
    SourceCodeNasm code (path_asm);

    if (Translate (code))
        fprintf (stderr, "Fail\n");

    printf ("%x\n", mulrm8 | ah | 0b11000000);

    bprintf (mulrm8 | ah | 0b11000000, 8 * 3, true);
    return 0;
}

// 010010001 11101111 1100000
// 010010001 11101101 1100000





























