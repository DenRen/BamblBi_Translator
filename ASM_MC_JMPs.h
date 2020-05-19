//
// Created by tester on 19.05.2020.
//

#ifndef BAMBLBI_TRANSLATOR_ASM_MC_JMPS_H
#define BAMBLBI_TRANSLATOR_ASM_MC_JMPS_H

namespace nasmmc {

/*
 jmp -128   | e97cffffff    // far
 jmp -127   | eb80          // short start
 ...
 jmp 0      | ebfe
 jmp 1      | ebff
 jmp 2      | eb00
 jmp 3      | eb01
 ...
 jmp 129    | eb7f          // short end
 jmp 130    | e97d000000    // far
 */

#define JMP_SHORT        0xeb00
#define JMP_FAR          0xe900000000

#define JE               0x0074fe
#define JNE              0x0075fe
#define JL               0x007cfe
#define JNGE JL
#define JLE              0x007efe
#define JNG JLE
#define JGE              0x007dfe
#define JNL JGE
#define JB               0x0072fe
#define JNAE JB
#define JBE              0x0076fe
#define JNA JBE
#define JA               0x0077fe
#define JNBE JA
#define JAE              0x0073fe
#define JJNB JAE

#define JZ               0x0074fe
#define JS               0x0078fe
#define JC               0x0072f3
#define JO               0x0070fe
#define JP               0x007afe

#define JECXZ            0x67e3
#define JRCXZ            0x00e3

}

#endif //BAMBLBI_TRANSLATOR_ASM_MC_JMPS_H
