//
// Created by tester on 15.05.2020.
//
#include <stdexcept>
#include <cassert>
#include <cstring>
#include "main_lib.h"

char *readfile (const char *path, __uint32_t *size) {
    if (path == nullptr)
        throw std::runtime_error ("Empty path");

    FILE *file = nullptr;
    if ((file = fopen (path, "rb")) == nullptr)
        throw std::runtime_error ("Failed to open file");

    *size = getSizeFile (file);
    // Checking on empty pointer not needed here,
    // because previous does it

    char *buf = nullptr;
    if ((buf = (char *) calloc (*size, sizeof (char))) == nullptr)
        throw std::runtime_error ("Failed to create buffer");

    if (fread (buf, sizeof (char), *size, file) != *size)
        throw std::runtime_error ("Failed to read in buffer");

    fclose (file);

    return buf;
}

void writefile (const char *path, const char *data, __uint32_t size) {
    FILE *file = fopen (path, "wb");
    if (data == nullptr || size <= 0 || file == nullptr) {
        fclose (file);
        throw std::runtime_error ("Empty args in function");
    }

    if (fwrite (data, sizeof (char), size, file) != size) {
        fclose (file);
        throw std::runtime_error ("Failed to write data in file");
    }

    fclose (file);
}

long getSizeFile (FILE *file) {
    if (file == nullptr)
        return -1;

    __uint32_t size = 0;
    fseek (file, 0, SEEK_END);
    size = ftell (file);
    fseek (file, 0, SEEK_SET);

    return size;
}

__uint32_t countSymb (char *str, char symb, __int64_t size) {
    assert (size != 0);
    assert (size >= -1);

    __uint32_t counter = 0;

    if (size == -1) {
        str--;
        while ((str = strchr (++str, symb)) != nullptr)
            counter++;

    } else {
        char *old_str = str;

        while (*str != '\0' && (str = (char *) memchr (str, symb, size)) != nullptr) {
            counter++;
            size -= old_str - str;
            old_str = str++;
        }
    }

    return counter;
}

__line *SplitLines (char *lines, __uint32_t *num_lines, __int64_t size_buf) {

    // ????????? ??????. ????? ??????, ?????????? ????? ?? ?????? realloc - ??
    __uint32_t countLineBreak = countSymb (lines, '\n', size_buf);
    __line *prim_buf = (__line *) calloc (countLineBreak, sizeof (__line));

    __uint32_t _num_lines = 0;

    do {
        while (isspace (*lines))                // ?????????? ???????
            lines++;
        if (*lines == '\0') break;              // ?????? ????????? ??????

        prim_buf[_num_lines].string = lines;    // ????????? ?????? ???????

        while (*lines != '\n' && *lines != '\0')
            lines++;
                                                // ???????? ????? ???????
        prim_buf[_num_lines].size = lines - prim_buf[_num_lines].string;

        _num_lines++;

        if (*lines == '\0') break;              // ?????? ????????? ??????

        *lines++ = '\0';                        // ????? ?? ???????

    } while (true);

    // ??????? ?????? ???? ?? ?????? ??? '\n'
    assert (countLineBreak >= _num_lines);

    // ?????? ????? ?????? realloc (prim_buf, sizeof (__line) * _num_lines);
    // ??-?? ????, ??? realloc ?? ????? ??????????, ? ?????? ?????? ??????
    prim_buf = (__line *) realloc (prim_buf, sizeof (__line) * _num_lines);

    *num_lines = _num_lines;
    return prim_buf;
}
#define MAX_WORDS_IN_LINE 256

__line_words *getWordsFromLines (__line *lines, __uint32_t num_lines) {
    // Max words in line: 256 (Check struct __line_words::size in SourceCodeNasm.h)
    __line_words * lines_code = (__line_words *) calloc (num_lines, sizeof (__line_words));

    if (lines_code == nullptr)
       throw std::runtime_error ("Failed to create lines+code array");

    for (__uint32_t i = 0; i < num_lines; i++)
        lines_code[i].words = getWordsFromLine (lines[i].string, &lines_code[i].size);

    return lines_code;
}

__word *getWordsFromLine (char *line, __uint8_t *quantity_words) {
    char *cur_word = line;

    __int8_t num_words = 0;
    __word *words = (__word *) calloc (MAX_WORDS_IN_LINE, sizeof (__word));

    bool word_on = false, string_on = false;

    while (*cur_word != '\0') {
        // TODO \"
        if (*cur_word == '\"') {

            if (string_on == true) {

                string_on = false;

                *cur_word++ = '\0';
                words[num_words].len = cur_word - words[num_words].word;
                num_words++;

                words[num_words].word = cur_word;

            } else {
                if (word_on == false) {

                    string_on = true;
                    words[num_words].word = cur_word++;

                } else {

                    word_on = false;
                    string_on = true;

                    *cur_word++ = '\0';
                    words[num_words].len = cur_word - words[num_words].word;
                    num_words++;

                    words[num_words].word = cur_word;

                }
            }
        } else if (isspace (*cur_word) || *cur_word == ',') {
            if (word_on) {
                word_on = false;

                *cur_word = '\0';
                words[num_words].len = cur_word - words[num_words].word;
                num_words++;

            }
                cur_word++;

        } else {

            if (word_on == false && string_on == false) {

                words[num_words].word = cur_word;
                word_on = true;

            }

            cur_word++;
        }
    }

    if (word_on) {

        words[num_words].len = cur_word - words[num_words].word;
        num_words++;

    } else if (string_on) {
        printf ("%s\n There is no second quotation mark!\n", line);
        throw std::runtime_error ("Syntax Error !!!");
    }


    *quantity_words = num_words;

    return (__word *) realloc (words, num_words * sizeof (__word));
}

#undef MAX_WORDS_IN_LINE
