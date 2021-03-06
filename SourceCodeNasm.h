//
// Created by tester on 15.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_SOURCECODENASM_H
#define BAMBLBI_TRANSLATOR_SOURCECODENASM_H

#include "zlib.h"

struct __word {
    __int32_t len;
    char *word;

    bool conv2num ();
};

struct __line {
    __uint32_t size;
    char *string;
};

struct __line_words {   // Array from words
    __uint8_t size;
    __word *words;
};

class SourceCodeNasm {
public:

    char *buf_asm_code;
    __uint32_t size_buf;

    __line_words *lines_code;
    __uint32_t number_lines;

    explicit SourceCodeNasm (const char *path_nasm_file, bool dump = false);
    ~SourceCodeNasm ();
};


#endif //BAMBLBI_TRANSLATOR_SOURCECODENASM_H
