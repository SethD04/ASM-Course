# GDB Basics

## Introduction

GDB (GNU Debugger) is a powerful debugging tool for programs written in C, C++, and other languages. This guide will cover the basic commands and concepts to get you started with GDB.

## Starting GDB

To start GDB, use the following command in your terminal:

    gdb [program]

Replace `[program]` with the name of the executable you want to debug. If you want to pass arguments to the program, you can do it within GDB after starting it.

## Common Commands

### Running and Stopping

- **run (r)**: Start the program with optional arguments.

    ```sh
    run [args]
    ```

- **kill**: Stop the program.

    ```sh
    kill
    ```

- **quit (q)**: Exit GDB.

    ```sh
    quit
    ```

### Breakpoints

- **break (b)**: Set a breakpoint at a function or line.

    ```sh
    break [location]
    ```
    Example:
    ```sh
    break main
    break 42
    ```

- **info breakpoints**: List all breakpoints.

    ```sh
    info breakpoints
    ```

- **delete (d)**: Delete breakpoints by number.

    ```sh
    delete [breakpoint number]
    ```
    Example:
    ```sh
    delete 1
    ```

### Stepping Through Code

When debugging, you often need to execute your program line by line to inspect its behavior. GDB provides several commands for this purpose: `step`, `next`, `si`, and `ni`.

#### next (n)

The `next` command executes the current line of code and then stops at the next line in the same function. If the current line contains a function call, `next` will execute the entire function and stop at the next line after the function call.

Usage:
    
    next
    n

Example:
    
    (gdb) next

This command is useful when you want to step over function calls without stepping into them.

#### step (s)

The `step` command is similar to `next`, but it steps into function calls. If the current line contains a function call, `step` will stop at the first line of the called function.

Usage:
    
    step
    s

Example:
    
    (gdb) step

This command is useful when you want to debug inside the functions that are being called.

#### si (stepi)

The `si` or `stepi` command steps one instruction in the program, entering function calls. This command is useful for debugging at the assembly level.

Usage:
    
    stepi
    si

Example:
    
    (gdb) si

Use `si` when you need to step through your program at the machine instruction level.

#### ni (nexti)

The `ni` or `nexti` command steps one instruction in the program, but steps over function calls. Like `si`, this is used for assembly-level debugging.

Usage:
    
    nexti
    ni

Example:
    
    (gdb) ni

Use `ni` to step over assembly instructions without stepping into function calls.

### Examining Code

- **list (l)**: List source code around the current line or a specific function.

    ```sh
    list
    list [function]
    ```

- **print (p)**: Print the value of a variable or expression.

    ```sh
    print [variable or expression]
    ```
    Example:
    ```sh
    print x
    ```

- **display**: Display a variable's value each time the program stops.

    ```sh
    display [variable]
    ```

- **info locals**: Show local variables in the current function.

    ```sh
    info locals
    ```

- **backtrace (bt)**: Show the call stack.

    ```sh
    backtrace
    ```

### Memory

- **x**: Examine memory at a specific address.

    ```sh
    x/[format] [address]
    ```
    Example:
    ```sh
    x/4xw 0x601050
    ```
    Format options:
    - `x`: Hexadecimal
    - `d`: Decimal
    - `s`: String
    - `i`: Instruction

## Example Session

Here is an example session of using GDB:

1. Start GDB with your program:
    ```sh
    gdb ./my_program
    ```

2. Set a breakpoint at the `main` function:
    ```sh
    (gdb) break main
    ```

3. Run the program:
    ```sh
    (gdb) run
    ```

4. When the program stops at the breakpoint, step into the next line:
    ```sh
    (gdb) step
    ```

5. Print the value of a variable:
    ```sh
    (gdb) print my_variable
    ```

6. Continue running the program:
    ```sh
    (gdb) continue
    ```

7. Quit GDB:
    ```sh
    (gdb) quit
    ```

## Conclusion

This guide provides a starting point for using GDB. With practice, you'll become more familiar with its powerful features and be able to debug more effectively.
