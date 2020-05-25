//
// Created by tester on 24.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_DIRECTIVES_H
#define BAMBLBI_TRANSLATOR_DIRECTIVES_H

#include <zconf.h>

namespace drctv {
    const __uint8_t max_len_name_drct = 16;

    enum _drcts {
        DB, DW, DD, DQ,
        SECTION, GLOBAL,
        __Quantity_Types_Directives
    };

    extern char _name_directives[__Quantity_Types_Directives][max_len_name_drct];


}

#endif //BAMBLBI_TRANSLATOR_DIRECTIVES_H
