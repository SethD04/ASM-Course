cmake_minimum_required(VERSION 3.2)
project(CRT C CXX ASM_NASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdlib -g -fcf-protection=none -Og -fno-omit-frame-pointer")
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -g -O0")

# Specify the object format for NASM (e.g., elf64 for 64-bit, elf32 for 32-bit)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)

# Enable the ASM_NASM language
enable_language(ASM_NASM)

file(GLOB LAB_ASM_FILES "*.s")
file(GLOB LAB_CPP_FILES "*.c")

set_source_files_properties(${LAB_ASM_FILES} PROPERTIES LANGUAGE ASM_NASM)

add_executable(lab14 ${LAB_ASM_FILES} ${LAB_CPP_FILES})
