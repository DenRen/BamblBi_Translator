//
// Created by tester on 26.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_ELF_PROG_HEADER_H
#define BAMBLBI_TRANSLATOR_ELF_PROG_HEADER_H

#include <zlib.h>
#include <cstdio>
#include "../SourceCodeNasm.h"


#define InsertSize(sz) { code[code_idx++] = (sz & 0x000000FF);          \
code[code_idx++] = (sz & 0x0000FF00) >> 8;                              \
code[code_idx++] = (sz & 0x00FF0000) >> 16;                             \
code[code_idx++] = (sz & 0xFF000000) >> 24; }

namespace elf {

    __word CreateELF (__uint64_t size_prog);

    void _add_elf_header (char *buf, __uint64_t *cur_pos);
    void _add_prog_header (char *buf, __uint64_t *cur_pos);

    void add_elf_header (FILE *file);
    void add_prog_header (FILE *file, __uint64_t file_size, __uint64_t mem_size);
    struct elf_header_t {

        __uint32_t EI_mag;
        __uint8_t EI_class;
        __uint8_t EI_data;
        __uint8_t EI_version;
        __uint8_t EI_OS_ABI;

        __uint8_t EI_OS_ABI_version;

        __uint16_t E_type;
        __uint16_t E_machine;
        __uint32_t E_version;

        __uint32_t Entry_offset;
        __uint8_t __empty3 = 0;
        __uint32_t Prof_offset;
        //__uint32_t __empty4;
        __uint64_t Header_offset;
        //__uint32_t __empty5;

        __uint32_t flags;
        __uint16_t elf_header_size;
        __uint16_t prog_header_size;

        __uint16_t quant_prog_header;
        __uint16_t sect_header_size;
        __uint16_t quant_sect_header;
        __uint16_t index_table;

        elf_header_t ();
    };

    struct prog_header_t {

        __uint32_t p_type;
        __uint32_t p_flags;
        __uint64_t p_offset;

        __uint32_t virt_address;
        __uint32_t phys_address;

        __uint64_t file_size;
        __uint64_t mem_size;

        __uint32_t align;

        __uint32_t _empty0;
        __uint64_t _empty1;

        prog_header_t (__uint64_t file_size, __uint64_t  mem_size);

    };
}



#endif //BAMBLBI_TRANSLATOR_ELF_PROG_HEADER_H
