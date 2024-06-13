# Introduction to x86 and x86_64 Assembly Language

## Basic Operations

### Objectives

* Utilize basic arithmetic and bit operations.
* Understand the difference between signed and unsigned values from an assembly perspective.
* Understand the Two's Complement representation of signed numbers.
* Understand the stack in assembly programming and implement functions that utilize it to load and store data.

---

## Arithmetic Operations

### Basic Math Operations

#### The `add` and `sub` Instructions

**Description**:

* Adds and subtracts arbitrary values.
* The destination (where the result is stored) is the first value provided.

**Basic Use**:

* To add, use `mov` to place a value into a register. `add` will take the value on the right and add it to the value currently in the register. The sum is stored back in the register.

  ```nasm
  mov rax, 1 ; move 1 into rax
  add rax, 2 ; adds 2 to rax, rax now contains 3
  ```

* To subtract, use `mov` to place a value into a register. `sub` will take the value on the right and subtract it from what's currently in the register. The difference is stored back in the register.

  ```nasm
  mov rax, 2
  sub rax, 2 ; subtracts 2 from rax, rax now contains 0
  ```

* We can use a combination of registers and immediates as operands:

  ```nasm
  mov rax, 1
  add rax, 2 ; rax now contains 3
  sub rax, 1 ; rax now contains 2
  mov rcx, 2
  add rax, rcx ; rax now contains 4
  sub rax, rcx ; rax is now back to 2
  ```

#### The `mul` Instruction

**Description**:

* Allows multiplication of arbitrary values. Takes a single argument, multiplies by `rax/eax/ax` (depending on operand size).

**Basic Use**:

  ```nasm
  mov eax, 10
  mov ecx, 10
  mul ecx     ; rax now contains 100
  ```

  ```nasm
  mov rax, 5
  mov rbx, 7
  mul rbx     ; rax now contains 35
  ```

Results are mostly stored in the source operand (`ax/eax/rax`), but may be stored in `dx/edx/rdx` as well if overflow occurs. The table below illustrates this.

#### The `mul` Instruction: Storing Results

Results are stored in the source (possible), or in a combination of registers in the configuration below:

![mul instruction results](images/section_2_mul_table.jpg)

#### The `div` Instruction

**Description**:

* As with `mul`, `div` takes a single argument and divides the value stored in the dividend register(s) by it. This is typically `ax/eax/rax` (and the `*dx` equivalents), but may vary a bit depending on the size (chart provided below).

**Basic Use**:

  ```nasm
  ; clearing the register where the
  ; high bits would be stored, we're only using what's in rax!
  mov rdx, 0 
  mov rax, 10
  mov rcx, 2
  div rcx    ; rax now contains 5
  ```

#### `div`: Operation Results

Where to retrieve the results of a `div` from depends on the size of the arguments. The table below illustrates this relationship:

![div instruction results](images/section_2_div_table.jpg)

#### `inc` and `dec`

**Description**:

* Adds or subtracts one from the provided register, storing the result in place.

**Basic Use**:

  ```nasm
  mov rax, 1  ; rax now contains 1
  inc rax     ; rax now contains 2
  inc rax     ; rax now contains 3
  dec rax     ; rax now contains 2
  ```

---

## Lab 3: Arithmetic Operations

* Copy the Lab3 folder (and its contents).
* Modify the \*.nasm file (Each function should have a comment block - lines starting with ';' containing instructions).
* Build and run using the following commands:

  ```bash
  cmake . && cmake --build .
  ./lab3
  ```

---

## The Stack

### Stack Basics

* Grows from high memory to low memory.
* Current function typically exists within a stack "frame" (but not always!).

### Stack Frames

* `RSP` (or `ESP`) points to the top of the stack.
* `RBP` (or `EBP`) points to the "base" of the stack frame.

### Stack Frame Layout

![stack frame layout](images/section_2_stack_diagram_1.jpg)

### Expanding the Stack Frame

* Can modify the value of `RSP` directly to allocate more stack space:

  ```nasm
  sub rsp, 16
  ```

* But you must always ensure you clean up before the function returns:

  ```nasm
  add rsp, 16
  ```

### Stack Alignment

* x86_64 expects 16 byte stack alignment.
* Allocating odd amounts of space can cause things to break.
* ALWAYS make sure you clean up your stack before returning.

### GDB - Stack Frames

* Examining the Call Stack (backtrace / bt).
* Frames and information:
  * `frame` or `f` - Get information about the current frame.
  * `info args` - Get information about function arguments.
  * `info locals` - Information about local variables.

May be appropriate to demo GDB and stack frames.

### New Instructions: `push` and `pop`

**Description**:

* `push` will subtract a pointer-width amount of space from `RSP`, and place the argument in the newly-allocated location.
* `pop` performs the opposite action, storing the value just below `RSP` in the register provided, and adding a pointer-width amount to `RSP`.
* For every `push`, you will need to `pop`!

**Basic Use**:

  ```nasm
  mov rax, 1  ; 1 is now stored in rax.
  push rax    ; 1 is now stored at the top of the stack
  pop rcx     ; rcx now contains 1
  ```

### Growing the Stack

After a `push` operation:

![growing the stack](images/section_2_stack_diagram_2.jpg)

### Restoring the Stack

After a `pop` operation:

![restoring the stack](images/section_2_stack_diagram_3.jpg)

---

## Example

  ```nasm
  section .text
  global _start

  _start:
      call my_function
      ; Exit the program
      mov eax, 60         ; syscall: exit
      xor edi, edi        ; status: 0
      syscall

  my_function:
      ; Function prologue
      push rbp            ; Save base pointer
      mov rbp, rsp        ; Set base pointer to stack pointer

      ; Function body (local variables on stack)
      sub rsp, 16         ; Allocate space for local variables
      mov [rbp-4], dword 10 ; Example local variable

      ; Function epilogue
      mov rsp, rbp        ; Restore stack pointer
      pop rbp             ; Restore base pointer
      ret                 ; Return to caller
  ```

Before `sub rsp, 16`

  ```nasm
  | Higher memory addresses         |
  | ------------------------------- |
  | Old RBP (previous stack frame)  | <- RBP (and RSP) |
  | ------------------------------- |
  |                                 |
  |                                 |
  | Lower memory addresses          |
  ```

After `sub rsp, 16`

  ```nasm
  | Higher memory addresses         |
  | ------------------------------- |
  | Old RBP (previous stack frame)  | <- RBP |
  | ------------------------------- |
  | Local variable space (16 bytes) |
  | ------------------------------- |
  |                                 | <- RSP |
  | Lower memory addresses          |
  ```

## Lab 4: Stack Operations

* Copy the Lab4 folder (and its contents).
* Modify the \*.nasm file (Each function should have a comment block - lines starting with ';' containing instructions).
* Build and run using the following commands:

  ```bash
  cmake . && cmake --build .
  ./lab4
  ```

---

## Negative Numbers

### Two's Complement

![two's complement](images/section_2_counter.jpeg)

* Negative numbers on the x86(_64) platform are represented via Two's Complement.

On understanding Two's Complement: think of what happens when a mechanical counter (like the one pictured on the slide) counts down to zero, and rolls over. You might see it flip all the numbers over: e.g., 9999.

### Two's Complement Steps

* Invert the bits of the number (in binary), and add one!

![two's complement steps](images/section_2_twos_complement_p1.jpg)

* Simplifies addition operations.
* Unified Add/Sub.

Example: Adding 2 and -1

  ```text
  Carry Row:  11 
              1111
            + 0010
              ----
              0001
  ```

### Sub Registers and Sign Extending

* When copying smaller data into a register, sign extending may be used (rather than zero extending).
* Sign extending preserves the "signed" attributes of the data being copied.
* The `movsx` instruction (just like `movzx`) handles this.

### The `movsx` Instruction

**Description**:

* Much like `movzx`, `movsx` can be used to move data into a portion of a larger register while preserving its sign.

**Basic Use**:

  ```nasm
  mov cl, -1
  movsx rax, cl   ; rax now contains -1.
  ```

---

## Bitwise Operations

### Bit Shifting

* Two unsigned shift operations exist: `shl` (shift left) and `shr` (shift right).
* Shifting moves the bits in the register over the direction (left or right) and number of bits specified.
* Bits that fall off the end (and overflow) will disappear, except for the last one, which ends up in the carry flag.
* The extra space created gets padded with 0's.

### Left Shift Diagram

The following snippet of assembly:

  ```nasm
  mov rax, 1
  shl rax, 1
  shl rax, 3
  ```

Can be modeled by the following table:

![left shift diagram](images/section_2_bitops_shl_1.jpg)

### Right Shift Diagram

Similarly, the following snippet of assembly:

  ```nasm
  mov rax, 32
  shr rax, 1
  shr rax, 4
  ```

Can be modeled by the following table:

![right shift diagram](images/section_2_bitops_shr_1.jpg)

### Binary `and` / `or`

* `and` can be used to determine whether one or more bits are set.
* `or` will tell you if the bit is set in at least one place.
* Both take two operands, one of which will hold the result after the operation completes.

**Use**:

  ```nasm
  mov rax, 1      ; rax contains 00000001
  mov rcx, 5      ; rcx contains 00000101

  and rax, rcx    ; rax contains 00000001
  or rax, rcx     ; rax contains 00000101
  ```

Another way to think about this (if familiar with sets and set theory): `and` gives us the intersection between the two sets of bits, `or` gives us their union.

### `and` Table

![and table](images/section_2_bitops_and.jpg)

### `or` Table

![or table](images/section_2_bitops_or.jpg)

### Binary `not`

* Inverts the bits in a given register.

Example:

  ```nasm
  mov rax, 0  ; rax now contains 00000000
  not rax     ; rax is now all 1's (or 0xffffffff)
  ```

Similarly:

  ```nasm
  mov rcx, 1  ; rcx now contains 1
  not rcx     ; rcx now contains 0xfffffffe (all 1's minus the first bit)
  ```

### Properties of `eXclusive Or` (XOR)

* XOR yields 1 only if the bit is set in either the source or destination, but NOT both.
* Any value XOR'd with itself is 0.
* 0 XOR'd with any value is that value.
* For numbers A, B, and C, if A ^ B = C, then C ^ A = B and C ^ B = A.

### XOR Table

![xor table](images/section_2_bitops_xor.jpg)

### Rotating Bits

* The values in the register are rotated the indicated number of places to the right or left.
* Bits that are rotated off the end of the register and moved back to the beginning.

Instruction:

  ```nasm
  mov rax, 1  ; rax contains 1 (00000001)
  rol rax, 1  ; rax now contains 2 (00000010)
  ror rax, 1  ; rax now contains 1 (00000001)
  ror rax, 1  ; rax now looks like: (10000000)
  ```

### Signed Bit Operations

* Shift operations that are sign aware exist (`sar` for right and `sal` for left).
* Work in the same fashion as `shr/shl`, except for how bits shifted off the end are treated (bits still disappear, but the sign of the resulting value is retained).

---

## Lab 5: Bit Operations

* Copy the Lab5 folder (and its contents).
* Modify the \*.nasm file (Each function should have a comment block - lines starting with ';' containing instructions).
* Build and run using the following commands:

  ```bash
  cmake . && cmake --build .
  ./lab5
  ```

---

## Section Review

* Arithmetic Operations
* The Stack
  * Stack Frames
  * Stack Alignment
* Signed Values and Two's Complement
* Bit Operations
