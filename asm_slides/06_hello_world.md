# Introduction to x86 and x86_64 Assembly Language

## Creating Our Own NASM Assembly Program

## Immediate Operand Sizes

**Decimal:**

```nasm
100
100d    ; explicitly decimal - d suffix
0100    ; still dec
```

**Hex:**

```nasm
0c8h    ; h suffix, leading zero required otherwise it's taken as var
0xc8    ; 0x prefix
0hc8    ; NASM is cool with 0h
```

**Octal:**

```nasm
300q            ; octal - q suffix
0q310           ; 0q prefix
```

**Binary:**

```nasm
110010100b      ; b suffix
0b11001_0100    ; 0b prefix, underscores are allowed
```

## dx Instruction

* dx (x being replaced with size) is a pseudo-instruciton that declares size x that will be in memory when the program runs

### Sizes

* **db** = byte (1 bytes) or RESB
* **dw** = word (2 bytes) or RESW
* **dd** = dword (4 bytes) or RESD
* **dq** = qword (8 bytes) or RESQ
* **dt** = tword (10 bytes) or REST
* **do** = oword (16 bytes), RESO, DDQ, RESDQ
* **dy** = yword (32 bytes) or RESY
* **dz** = zword (64 bytes) or RESZ

### Reserve and Initialize Data

```nasm
db    0x40                          ; the byte 0x40 
db    0x40,0x41,0x42                ; three bytes in succession
db    'A',0x42                      ; char consts okay
db    'hello', 0x73, '$', 0x00      ; as are string consts
dw    0x1234                        ; 0x34 0x12
dw    'a'                           ; 0x61 0x00 (it's just a number)
dw    'ab'                          ; 0x61 0x62 (character constant)
dw    'abc'                         ; 0x61 0x62 0x63 0x00 (string)
dd    0x12345678                    ; 0x78 0x56 0x34 0x12
dd    1.234567e20                   ; floating-point constant
dq    0x123456789abcdef0            ; eight byte constant
dq    1.234567e20                   ; double-precision float
dt    1.234567e20                   ; extended-precision float
```

#### You can also just reserve space without initializing it

```nasm
buff        resb    255     ; reserve 255 bytes
var1        resw    1       ; reserve a word
```

## Structure of a NASM program

* **Directives:**
  * There are two types of directives: *user-level* and *primitive*.
  * Directives setup things such as processor mode, defining sections, labels, externs, etc.
  * **BITS** : The `BITS` directives specifies the processor operating mode the code is designed to run on.
    * EX: `BITS 16, BITS 32, BITS 64`
  * **EXTERN** : Similar to C keyword `extern`. Declares a symbol which is not defined in the module being assembled, but is assumed to be defined in some other module and needs to be refered to by this one.
  * **GLOBAL** : Other end of `EXTERN`. Allows another module to extern the symbol.
  * **SECTION** : Changes which section of the output file the code you write will be assembled into.
* **Sections**
  * Also called `SEGMENT`
  * Standard sections include:
    * `.text` : This is the actual code
    * `.data` : This is your data that's initialized to something other than zero at program startup
    * `.bss`  : Stores info about memory that needs to be zeroed at program startup. Like empty space and such.
    * Many more sections...

### Example

Let's create a hello world program!

* First, let's create our directives:

```nasm
bits 64
global _start

...
```

* Second, let's add our sections:

```nasm
bits 64
global _start

section .data

section .text
```

* Third, let's add our labels, we created a global _start:

```nasm
bits 64
global _start

section .data

section .text

_start:
```

* Next, let's create our data

```nasm
bits 64
global _start

section .data
    msg db      "hello, world!", 0xa ; 0xa = nl

section .text

_start:
...
```

* After we have our data created, let's populate code

```nasm
bits 64
global _start

section .data
    msg db      "hello, world!", 0xa

section .text

_start:

    mov rax, 1          ; 1 for sys_write 
    mov rdi, 1          ; 1 for fd 
    mov rsi, msg        ; move message into rsi
    mov rdx, 14         ; length of string
    syscall
    mov rax, 60         ; sys exit
    mov rdi, 0          ; error code (none) 
    syscall
```

## Using a C Library

* Remember the C Runtime we discussed? Remember how we said the C program does not actually start at `main`, but instead at `_start`, eventually calling `main`? If we keep that in mind, creating a NASM file that can use a C Library is easy.
* Instead of `_start`, we are going to use `global main`.
* We can extern any C Library functions we need, ex. `extern puts`
* Everything else is the same.

```nasm
bits 64
global      main
extern      puts

section .text
main:
    sub rsp, 8
    mov rdi, message
    call puts
    add rsp, 8
    ret

message:
    db      "Test!", 0
```

## Building/Compiling/Running

* **Without C Library:**
  * The only thing we need to do is compile nasm code into an object, then use the GNU linker to convert the object file into a executable.
  * Parameters depend on OS and processor mode
    * Linux 64-bit:
      * Compile: `nasm -f elf64 file.s` or you can specify output `nasm -f elf64 file.s file.o`
      * Link: `ld file.o` or specify output with -o
      * Run: `./a.out`
    * Linux 32-bit:
      * Compile with elf32
    * Windows:
      * Compile with win32 or win64
      * Link with either link.exe or `ld` if you have MinGW installed
* **With C Library:**
  * The instructions are the same for compiling the nasm file into an object. But from there, we must use gcc to link the object with the C library. Linux 64bit example:

    `nasm -f elf64 file.s && gcc -no-pie file.o && ./a.out`

  * The command above is really three seperate commands seperated by `&&` signs... you can run each command individually if you desire.
  * First we compile:
    * `nasm -f elf64 file.s`
  * file.o is then ouputted...
  * Then we take file.o and compile/link it with gcc:
    * `gcc -no-pie file.o`
  * Due to not specifying a output, the file `a.out` is created.
  * Lastly, we can run the program:
    * `./a.out`

## Quick Calling Conventions Review

### Linux x86_64

* Parameters are passed left to right into the following registers first, in order:
  * Int and pointers: `rdi, rsi, rdx, rcx, r8, r9`
  * For floating-point (float, double): `xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7`
* Additional is pushed on stack and are to be cleaned by the **caller** after the call

## Mixing C/C++ an Assembly Language

Now that we know all of the above, mixing C and ASM shouldn't be so hard.

* **CPP File**

```c
// A very simple program
#include <stdio.h>

extern "C" size_t first_func(void);

int main() 
{
    printf("%d\n", first_func());

    return 0;
}
```

* **NASM File**

```nasm
; A very simple nasm file

global first_func
section .text
first_func:
    mov rax, 10
    ret
```

### Building/Compiling/Running Mixed Code

* Not too much is different here... all of the same rules apply when compiling nasm and using GCC for the C Library. There are a couple additional things we need to note.
  * If using C++, use G++
  * When using G++/GCC, you also need to compile c code.
* Example:
  * `nasm -f elf64 file.s`
  * `gcc cFile.cpp file.o`
  * `./a.out`
