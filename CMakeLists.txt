cmake_minimum_required(VERSION 3.14)
project(BamblBi_Translator)

set(CMAKE_CXX_STANDARD 17)

add_executable(BamblBi_Translator main.cpp SourceCodeNasm.cpp SourceCodeNasm.h main_lib.h main_lib.cpp)