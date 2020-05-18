#include <cstdio>
#include <cstdlib>
#include <cctype>
#include "main_lib.h"

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

    

    return 0;
}