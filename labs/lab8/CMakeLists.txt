cmake_minimum_required(VERSION 3.2)
project(Lab8 C CXX ASM)

enable_language(ASM_NASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fcf-protection=none -Og -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fcf-protection=none -Og -fno-omit-frame-pointer")
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -g -O0")

file(GLOB LAB_ASM_FILES "*.s")
file(GLOB LAB_CPP_FILES "*.cpp")

set_source_files_properties(${LAB_ASM_FILES} PROPERTIES LANGUAGE ASM_NASM)

add_executable(lab8 ${LAB_ASM_FILES} ${LAB_CPP_FILES})
