#include <cstdio>
#include <cstdlib>
#include <cctype>
#include "main_lib.h"
#include "ASM_MC_new.h"
#include "ASM_commands_name.h"

int main () {

    const char path_asm[] = "../asm/test2.s";
    SourceCodeNasm code (path_asm);

    /*
    for (int i = 0; i < code.number_lines; i++) {
        __word *words = code.lines_code[i].words;
        for (int j = 0; j < code.lines_code[i].size; j++)
            printf ("%s", words[j].word);

        printf ("\n");
    }*/
    /*
#define FUNC(arg) NOT(arg)

    printf ("%x\n", FUNC (rax));
    printf ("%x\n", FUNC (rbx));
    printf ("%x\n", FUNC (rcx));
    printf ("%x\n", FUNC (rdx));
    printf ("%x\n", FUNC (rsi));
    printf ("%x\n", FUNC (rdi));
    printf ("%x\n", FUNC (rsp));
    printf ("%x\n", FUNC (rbp));

    printf ("\n");
return 0;
#define FUNC2(argl, argr) AND (argl, argr)

    printf ("%x\n", FUNC2(rax, rax));
    printf ("%x\n", FUNC2(rax, rbx));
    printf ("%x\n", FUNC2(rax, rcx));
    printf ("%x\n", FUNC2(rax, rdx));
    printf ("%x\n", FUNC2(rax, rsi));
    printf ("%x\n", FUNC2(rax, rdi));
    printf ("%x\n", FUNC2(rax, rsp));
    printf ("%x\n", FUNC2(rax, rbp));

    printf ("%x\n", FUNC2(rsi, rsi));
*/

    printf ("%x\n", _REX (0b0100));
    printf ("%x\n", _w | 0b01000000);
    bprintf32 (0x4c2b08);

    return 0;
}































