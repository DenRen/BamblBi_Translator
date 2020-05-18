//
// Created by tester on 15.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_MAIN_LIB_H
#define BAMBLBI_TRANSLATOR_MAIN_LIB_H

#include <cstdio>
#include <zconf.h>
#include "SourceCodeNasm.h"

void bprintf8  (__uint32_t num);
void bprintf32 (__uint32_t num);

char *readfile (const char *path, __uint32_t *size);                    // Max 4 Gb file
void writefile (const char *path, const char *data, __uint32_t size);   // Max 4 Gb file

long getSizeFile (FILE *file);

__uint32_t countSymb (char *str, char symb, __int64_t size = -1);
__line *SplitLines (char *lines, __uint32_t *num_lines, __int64_t size_buf = -1);

__line_words *getWordsFromLines (__line *lines, __uint32_t num_lines);
__word       *getWordsFromLine (char *line, __uint8_t *quantity_words);

#endif //BAMBLBI_TRANSLATOR_MAIN_LIB_H