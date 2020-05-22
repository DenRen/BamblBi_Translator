//
// Created by tester on 15.05.2020.
//

#include <cstdlib>
#include "SourceCodeNasm.h"
#include "main_lib.h"

SourceCodeNasm::SourceCodeNasm (const char *path_nasm_file) :
    lines_code (nullptr),
    buf_asm_code (nullptr)
{
    __uint32_t size_buf = 0;
    buf_asm_code = readfile (path_nasm_file, &size_buf);    // Read file i buffer

    number_lines = 0;                                       // Splits into lines
    __line *lines = SplitLines (buf_asm_code, &number_lines, size_buf);

    lines_code = getWordsFromLines (lines, number_lines);   // Words from lines


    free (lines);

}

SourceCodeNasm::~SourceCodeNasm () {
    for (int i = 0; i < number_lines - 1; i++) {
        __word *t = lines_code[i].words;
        free (lines_code[i].words);
    }

    if (lines_code[number_lines - 1].words != nullptr)
        free (lines_code[number_lines - 1].words);

    free (lines_code);
    free (buf_asm_code);
}