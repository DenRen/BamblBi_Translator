cmake_minimum_required(VERSION 3.14)
project(BamblBi_Translator)

set(CMAKE_CXX_STANDARD 17)

add_executable(BamblBi_Translator main.cpp SourceCodeNasm.cpp SourceCodeNasm.h main_lib.h main_lib.cpp ASM_commands_name.h ASM_MC_new.h ASM_Lib/ASM_Registers.h ASM_Lib/ASM_Prefixes.h ASM_Lib/ASM_ModR_M.h ASM_Lib/ASM_Opcode.h ASM_Lib/ASM_SIB.h ASM_Lib/ASM_Prefixes.cpp)