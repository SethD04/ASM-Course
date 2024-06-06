## Using a Simple .gdbinit File

GDB allows you to customize its behavior using a `.gdbinit` file. This file can contain various settings and commands that GDB will execute when it starts. Below is an example of a `.gdbinit` file that sets the disassembly flavor to Intel and defines a custom `hook-stop` to display useful debugging information every time the program stops.

### Creating the .gdbinit File

1. Open your terminal.

2. Create a new file named `.gdbinit` in your home directory (or in the directory where you will run GDB):

    ```sh
    nano ~/.gdbinit
    ```

3. Copy and paste the following content into the `.gdbinit` file:

    ```sh
    set disassembly-flavor intel

    define hook-stop
    echo -------------- $PC -------------------\n
    x/7i $pc
    echo -------------- PARAMS ----------------\n
    info reg rdi rsi rdx rcx r8 r9 rax
    echo -------------- $SP -------------------\n
    x/4gx $rsp
    echo ---------- Format String -------------\n
    x/s $rdi
    echo ----------- Other Regs ---------------\n
    info reg rbx r12
    echo -------------- END -------------------\n
    end
    ```

4. Save the file and exit the editor (in nano, you can do this by pressing `Ctrl+X`, then `Y` to confirm, and `Enter` to save).

Once you have created and saved your `.gdbinit` file, GDB will automatically execute the commands in this file whenever it starts. To see the custom `hook-stop` in action, simply start GDB and run your program as usual. Each time the program stops (e.g., at a breakpoint or after a step command), GDB will display the additional debugging information defined in the hook. If you want more advanced features then use the instructions for installing`GEF`.

## Installing and Using GEF (GDB Enhanced Features)

GEF (GDB Enhanced Features) is a powerful script for GDB that enhances its functionality and provides a better debugging experience.

### Installation

1. Open your terminal.

2. Download and install GEF by running the following command:

    ```sh
    bash -c "$(wget https://gef.blah.cat/sh -O -)"
    ```

### Using GEF

GEF enhances GDB with many useful features. Here are a few key commands:

- **context**: Display a comprehensive view of the program's state, including registers, stack, and disassembly.

    ```sh
    context
    ```

- **dereference (deref)**: Dereference a pointer and display the memory content at that location.

    ```sh
    dereference [address]
    ```

- **heap**: Display information about the program's heap.

    ```sh
    heap
    ```

- **pattern create**: Create a unique pattern of a specified length, useful for finding buffer overflow offsets.

    ```sh
    pattern create [length]
    ```

- **pattern search**: Search for a pattern in memory.

    ```sh
    pattern search [pattern]
    ```

- **gef help**: Display help for GEF commands.

    ```sh
    gef help
    ```