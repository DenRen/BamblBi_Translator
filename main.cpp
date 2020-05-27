#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include "main_lib.h"
#include "ASM_Lib/Translate.h"



int main () {

    const char path_asm[] = "../asm/test.s";
    SourceCodeNasm code (path_asm, false);

    FILE* file_MC = fopen ("my_code", "wb");
    if (file_MC == nullptr) {
        printf ("Failed open file!");
        //return 0;
    }
    __word MC_asm = Translate (code, file_MC, 128, 0x400080, false);
    __word MC_elf = elf::CreateELF (MC_asm.len);

    if (MC_asm.word == nullptr)
        fprintf (stderr, "Fail\n");

    fwrite (MC_elf.word, MC_elf.len, 1, file_MC);
    fwrite (MC_asm.word + 128, MC_asm.len - MC_elf.len, 1, file_MC);

    free (MC_asm.word);
    free (MC_elf.word);

    fclose (file_MC);

    printf ("OK!\n");

    return 0;
}

// 010010001 11101111 1100000
// 010010001 11101101 1100000





























