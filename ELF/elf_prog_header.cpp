//
// Created by tester on 26.05.2020.
//

#include <cassert>
#include <cstdlib>
#include "elf_prog_header.h"
#include "../SourceCodeNasm.h"


elf::elf_header_t::elf_header_t () :
   EI_mag               (0x464c457f),           // EI_MAG = ELF
   EI_class             (2),                    // EI_CLASS = 64 BIT
   EI_data              (1),                    // EI_DATA = DATA2LSB (Little-Endian)
   EI_version           (1),                    // EI_VERSION = EV_CURRENT
   EI_OS_ABI            (0),                    // EI_OS/ABI = UNIX SYSTEM V ABI

   EI_OS_ABI_version    (0),                    // EI_OS/ABI VER = 0                // EmptyStuff

   E_type               (2),                    // E_TYPE = EXEC
   E_machine            (0x3e),                 // E_MACHINE = EM_X86_64 (AMD x86- 64 architecture)
   E_version            (1),                    // E_VERSION = EV_CURRENT

   Entry_offset         (0x400080),
   Prof_offset          (0x400000),
   Header_offset        (0),

   flags                (0),
   elf_header_size      (0x40),
   prog_header_size     (0x38),

   quant_prog_header    (1),
   sect_header_size     (0x40),
   quant_sect_header    (0),
   index_table          (0)

   /*__empty3             (0),
   __empty4             (0),
   __empty5             (0)*/
{}

void elf::add_elf_header (FILE *file) {
    elf::elf_header_t elf;
    __uint64_t empty = 0;

    fwrite (&elf.EI_mag           , 4, 1, file);
    fwrite (&elf.EI_class         , 1, 1, file);
    fwrite (&elf.EI_data          , 1, 1, file);
    fwrite (&elf.EI_version       , 1, 1, file);
    fwrite (&elf.EI_OS_ABI        , 1, 1, file);

    fwrite (&elf.EI_OS_ABI_version, 1, 1, file);
    fwrite (&empty,                 7, 1, file);

    fwrite (&elf.E_type           , 2, 1, file);
    fwrite (&elf.E_machine        , 2, 1, file);
    fwrite (&elf.E_version        , 4, 1, file);

    fwrite (&elf.Entry_offset     , 4, 1, file);
    fwrite (&empty,                 2, 1, file);

    fwrite (&elf.Prof_offset      , 4, 1, file);
    fwrite (&empty,                 6, 1, file);

    fwrite (&elf.Header_offset    , 8, 1, file);

    fwrite (&elf.flags            , 4, 1, file);
    fwrite (&elf.elf_header_size  , 2, 1, file);
    fwrite (&elf.prog_header_size , 2, 1, file);

    fwrite (&elf.quant_prog_header, 2, 1, file);
    fwrite (&elf.sect_header_size , 2, 1, file);
    fwrite (&elf.quant_sect_header, 2, 1, file);
    fwrite (&elf.index_table      , 2, 1, file);

}
elf::prog_header_t::prog_header_t (__uint64_t file_size, __uint64_t mem_size) :
        p_type          (1),
        p_flags         (7),
        p_offset        (0),

        virt_address    (0x400000),
        phys_address    (0x400000),

        file_size       (file_size),
        mem_size        (mem_size),
        align           (0x200000),

        _empty0         (0),
        _empty1         (0)
{}

void elf::add_prog_header (FILE *file, __uint64_t file_size, __uint64_t mem_size) {
    elf::prog_header_t prog (file_size, mem_size);
    __uint64_t empty = 0;

    fwrite (&prog.p_type      , 4, 1, file);
    fwrite (&prog.p_flags     , 4, 1, file);

    fwrite (&prog.p_offset    , 8, 1, file);

    fwrite (&prog.virt_address, 4, 1, file);
    fwrite (&empty,             4, 1, file);

    fwrite (&prog.phys_address, 4, 1, file);
    fwrite (&empty,             4, 1, file);

    fwrite (&prog.file_size   , 8, 1, file);
    fwrite (&prog.mem_size    , 8, 1, file);

    fwrite (&prog.align       , 4, 1, file);
    fwrite (&empty,             12, 1, file);
}

#define Insert(num, ...) { unsigned char bytes[] = {__VA_ARGS__};       \
		for (size_t i = 0; i < num; i++) buf[(*cur_pos)++] = bytes[i]; }

#define MultiInsert(num, byte) { for (size_t i = 0; i < num; ++i)       \
		buf[(*cur_pos)++] = byte; }


void elf::_add_elf_header (char *buf, __uint64_t *cur_pos) {
    Insert (4, 0x7F, 0x45, 0x4C, 0x46) // EI_MAG = ELF

    Insert (1, 0x02) // EI_CLASS = 64 BIT
    Insert (1, 0x01) // EI_DATA = DATA2LSB (Little-Endian)
    Insert (1, 0x01) // EI_VERSION = EV_CURRENT
    Insert (1, 0x00) // EI_OS/ABI = UNIX SYSTEM V ABI

    Insert (1, 0x00) // EI_OS/ABI VER = 0
    MultiInsert (7, 0x00) // EmptyStuff

    Insert (2, 0x02, 0x00) // E_TYPE = EXEC
    Insert (2, 0x3E, 0x00) // E_MACHINE = EM_X86_64 (AMD x86- 64 architecture)
    Insert (4, 0x01, 0x00, 0x00, 0x00) // E_VERSION = EV_CURRENT
    // Entry offset
    Insert (4, 0x80, 0x00, 0x40, 0x00)
    MultiInsert (4, 0x00) // Empty Stuff
    // Program header offset
    Insert (4, 0x40, 0x00, 0x00, 0x00)
    MultiInsert (4, 0x00)

    // Section header offset
    MultiInsert (8, 0x00)
    // Flags
    MultiInsert (4, 0x00)

    // ELF header size
    Insert (2, 0x40, 0x00)

    // Program header size
    Insert (2, 0x38, 0x00)

    // Program headers quantity (number)
    Insert (2, 0x01, 0x00)

    // Section header size
    Insert (2, 0x40, 0x00)

    // Section headers quantity (number)
    MultiInsert (2, 0x00)

    // Section headers index table
    MultiInsert (2, 0x00)
}

void elf::_add_prog_header (char *buf, __uint64_t *cur_pos) {
    Insert (4, 0x01, 0x00, 0x00, 0x00) // P_TYPE = Loadable program segment
    Insert (4, 0x07, 0x00, 0x00, 0x00) // P_FLAGS = Segment is readable, writable and executable
    MultiInsert (8, 0x00) // P_OFFSET
    // Virtual address
    Insert (4, 0x00, 0x00, 0x40, 0x00)
    MultiInsert (4, 0x00)
    // Physical address
    Insert (4, 0x00, 0x00, 0x40, 0x00)
    MultiInsert (4, 0x00)
    // code[64d + 32d] = code [40h + 20h]
    // File size
    MultiInsert (8, 0x00) // ????????, ????? ????? ???????? ?????? ?????????
    // Memory size
    MultiInsert (8, 0x00) // ????????, ????? ????? ???????? ?????? ?????????
    // code[64d + 48d] = code [40h + 30h]
    // Align
    Insert (4, 0x00, 0x00, 0x20, 0x00)
    MultiInsert (4, 0x00)
    MultiInsert (8, 0x00) // Empty Stuff
}

#define InsertSize(sz) { mc_elf.word[temp_cur_pos++] = (sz & 0x000000FF);          \
mc_elf.word[temp_cur_pos++] = (sz & 0x0000FF00) >> 8;                              \
mc_elf.word[temp_cur_pos++] = (sz & 0x00FF0000) >> 16;                             \
mc_elf.word[temp_cur_pos++] = (sz & 0xFF000000) >> 24; }

__word elf::CreateELF (__uint64_t size_prog) {

    __word mc_elf = {};
    mc_elf.word = (char *) calloc (256, sizeof (char));
    mc_elf.len = 256;
    __uint64_t cur_pos = 0;

    elf::_add_elf_header (mc_elf.word, &cur_pos);
    elf::_add_prog_header (mc_elf.word, &cur_pos);

    // File size
    __uint64_t temp_cur_pos = 0x40 + 0x20;
    InsertSize (size_prog)
    // Memory size
    temp_cur_pos = 0x40 + 0x28;
    InsertSize (size_prog)

    mc_elf.word = (char *) realloc (mc_elf.word, cur_pos);
    mc_elf.len = cur_pos;

    return mc_elf;
}