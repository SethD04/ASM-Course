# Introduction to x86 and x86_64 Assembly Language

## System Calls - an Introduction

### Objectives

* Understand the basic function and implementation of system calls (including legacy methods)
* Understand the basic functionality provided by a C Runtime
* Implement a system call wrapper in assembly
* Begin work on a C Runtime

### System Calls

* Mechanism by which we task the operating system (kernel) to do work
* Implemented by a number of mechanisms, depending on OS/architecture
* Many operations require additional privilege to perform
  * File I/O
  * Memory allocation
  * Process creation
  * Device I/O

* This requires kernel intervention to occur

![image](./images/section_5_syscall.png)

### Legacy System Call Method

* int 0x80/0x2e

### Modern Alternative

* x86: sysenter / sysexit
* x64: syscall

### My First Syscall

Wrapping system calls

* x86
* x64

### Getting Information

* Man pages often have a comprehensive list of required flags (even if definitions are buried in header files)
* May be more than 1 section to a man page (if the page overlaps with a utility page "2" generally has dev docs)

```bash
man mmap     
man 2 open
```

### C Runtimes: A good \_start

* What is a runtime?
* int main() vs your program's real entry point
* Building without a standard library
* stuff your crt usually does

### Compiling with no CRT

* All functions will need to implemented/provided
* Initial effort: Wrap system functionality
  * sys_exit
  * write

### sys\_exit

```text
+------+-----------------+
| RAX  | > RDI           |
+------+-----------------+
| 60   | status (int)    |
+------+-----------------+
```

### Implementing sys\_exit

```nasm
mov rax, 60  ; the syscall number (in this case exit)
xor rdi, rdi ; argument 1, the exit code
syscall 
ret
```

### Setup

* STDOUT - A special kind of file descriptor (1)
* sys_write

```text
+------+-----------------+-------------------+-----------+
| RAX  | > RDI           | > RSI             | RDX       |
+------+-----------------+-------------------+-----------+
| 1    | fd              | buffer ptr        | Count     |
+------+-----------------+-------------------+-----------+
```

### I/O

### I/O Objectives

* Understand and Identify basic facts about Linux files and file descriptors
* Implement wrappers for several file I/O system calls
* Understand and utilize file-based process bookkeeping mechanisms (via /proc)

### Files and Operations

* UNIX Model - Everything is a file!
* File Descriptors
  * A bookkeeping mechanism to represent your access to a resource
  * Some reserved numbers: 0/1/2 (for std in/out/err)

### What are file descriptors?

* Entries into a table
* One exists for each process
* Each entry in the process table points to a System File Table entry

### File Pointer

* A pointer that keeps track of your current location in a file
* Maintained per system file table entry
* Calls to "read", "write", or "lseek" (among others) modify

### File Pointer Example

Assume the file \"tmp.txt\" contains: \"abcdefghij\"

```C
char buf[10] = {0};
// Assuming no failures, fd
// now contains a file descriptor
int fd = open("tmp.txt", O_RDONLY); 
if(-1 == fd) {
    return -1; // the open failed!
}

// At this point, the file pointer is at the start.

read(fd, buf, 5);
// Where does it point now?
```

Assuming no errors and all 5 bytes were read:

* buf now contains: "abcde"
* The file pointer is now at 'f'

If we ready again:

```C
read(fd, buf, 5);
// What does buf contain? 
// Where is the file pointer now?
```

### File Operations

* Read and Write
* Open and Close (for existing files)
* Unlink (for deleting)
* Syncing changes - msync and fsync

## Process Information and Virtual Memory

### mmap - A different use

* Can be used to map a file into memory
* Essentially (part of) how executables are loaded
* Can be more efficient for I/O

### mmap - Some new flags

* Required to be set to Shared for changes to appear in base file
* Changes may not show up until either munmap or a call to msync

```nasm
%define MAP_SHARED  0x01  ; Share changes.  
```

### Process Information

* /proc - a special type of directory
* /proc/self
* Getting to process parameters - /proc/self/cmdline

### Syscall Info - pt1

```text
+--------+------+------------------+-------------------+-----------+------------+------------+--------+
|Syscall | RAX  |  RDI             |  RSI              | RDX       | R10        | R8         | R9     |
+--------+------+------------------+-------------------+-----------+------------+------------+--------+
| mmap   | 9    | address          | length            | Protection| Flags      | Descriptor | offset |
+--------+------+------------------+-------------------+-----------+------------+------------+--------+
| munmap | 11   | address          | length            |           |            |            |        | 
+--------+------+------------------+-------------------+-----------+------------+------------+--------+ 
| read   | 0    | Descriptor       | buffer ptr        | Count     |            |            |        |
+--------+------+------------------+-------------------+-----------+------------+------------+--------+
| write  | 1    | Descriptor       | buffer ptr        | Count     |            |            |        | 
+--------+------+------------------+-------------------+-----------+------------+------------+--------+
| open   | 2    | filename (char*) | flags             |   mode    |            |            |        |
+--------+------+------------------+-------------------+-----------+------------+------------+--------+ 
| close  | 3    | Descriptor       |                   |           |            |            |        | 
+--------+------+------------------+-------------------+-----------+------------+------------+--------+ 
```

------------------------------------------------------------------------

### Syscall Info - pt2

```text
+--------+------+--------------+-------------------+-----------+------------+------------+--------+
|Syscall | RAX  |  RDI         |  RSI              | RDX       | R10        | R8         | R9     |
+--------+------+--------------+-------------------+-----------+------------+------------+--------+
| unlink | 87   | Path (char*) |                   |           |            |            |        | 
+--------+------+--------------+-------------------+-----------+------------+------------+--------+ 
| msync  | 26   | address start| length            | flags     |            |            |        | 
+--------+------+--------------+-------------------+-----------+------------+------------+--------+ 
| fsync  | 74   | Descriptor   |                   |           |            |            |        | 
+--------+------+--------------+-------------------+-----------+------------+------------+--------+ 
```

### Flags and Modes

Msync options

```nasm
; Flags to `msync'.  
%define MS_ASYNC    1  ; Sync memory asynchronously.  
%define MS_SYNC     4  ; Synchronous memory sync.  
```

Open options:

* One of the following options must be chosen:

```nasm
%define O_RDONLY       00
%define O_WRONLY       01
%define O_RDWR         02
```

* Zero or more of the following may be chosen:

```nasm
%define O_CREAT    0100 ; Create the file 
%define O_TRUNC   01000 ; Truncate (if exists) 
%define O_APPEND  02000 ; Append 
```

### Mode

* If file is being created, specifies permissions to set on it
* Can be one of the following values (follow UNIX-style permission rules) specified on the next slide

```text
+---------+-------+--------------------------------------------------+
| S_IRWXU | 00700 | user  (file  owner)  has read, write and execute |
|         |       | permission                                       |
+---------+-------+--------------------------------------------------+
| S_IRUSR | 00400 | user has read permission                         |
+---------+-------+--------------------------------------------------+
| S_IWUSR | 00200 | user has write permission                        |
+---------+-------+--------------------------------------------------+
| S_IXUSR | 00100 | user has execute permission                      |
+---------+-------+--------------------------------------------------+
| S_IRWXG | 00070 | group has read, write and execute permission     |
+---------+-------+--------------------------------------------------+
| S_IRGRP | 00040 | group has read permission                        |
+---------+-------+--------------------------------------------------+
| S_IWGRP | 00020 | group has write permission                       |
+---------+-------+--------------------------------------------------+
| S_IXGRP | 00010 | group has execute permission                     |
+---------+-------+--------------------------------------------------+
| S_IRWXO | 00007 | others have read, write and execute permission   |
+---------+-------+--------------------------------------------------+
```

### Lseek

* Lets you move to an offset within a file (moves the file pointer)
* Returns the distance (in bytes) your current offset is from the file's beginning

```text
+--------+------+--------------+-------------------+-----------+------------+------------+--------+
|Syscall | RAX  |  RDI         |  RSI              | RDX       | R10        | R8         | R9     |
+--------+------+--------------+-------------------+-----------+------------+------------+--------+
| lseek  | 8    | int (fd)     |  long offset      | origin    |            |            |        | 
+--------+------+--------------+-------------------+-----------+------------+------------+--------+ 
```

Values for origin (indicating where to move from):

```nasm
%define SEEK_SET        0   ; Seek from beginning of file
%define SEEK_CUR        1   ; Seek from current position
%define SEEK_END        2   ; Seek from the end of the file
```

### Stat

* The stat system call can also be used to retrieve file size
* Requires an additional structure definition
* Take a look at "man 2 stat" for further information

### Directories

* Several syscalls exist to read directories
* Focus will be on getdents

### Getdents

```text
+----------+------+--------------+-------------------+-----------+------------+------------+--------+
|Syscall   | RAX  |  RDI         |  RSI              | RDX       | R10        | R8         | R9     |
+----------+------+--------------+-------------------+-----------+------------+------------+--------+
| getdents | 78   | int (fd)     |  struct dirent*   | buff size |            |            |        | 
+----------+------+--------------+-------------------+-----------+------------+------------+--------+
```

### Misc Syscalls

* Execve - Execute a program
* First arg is the binary path to run
* Second is argv[]
* Third is environment strings

```text
+----------+------+--------------+-------------------+--------------+------------+------------+--------+
|Syscall   | RAX  |  RDI         |  RSI              | RDX          | R10        | R8         | R9     |
+----------+------+--------------+-------------------+--------------+------------+------------+--------+
| execve   | 59   | char*        |  char* argv[]     | char* envp[] |            |            |        | 
+----------+------+--------------+-------------------+--------------+------------+------------+--------+ 
```

* Dup2 - replace the file table entry of a file descriptor with something else
* First arg is the file descriptor to replace with
* Second is the target to be replaced

```text
+----------+------+--------------+-------------------+--------------+------------+------------+--------+
|Syscall   | RAX  |  RDI         |  RSI              | RDX          | R10        | R8         | R9     |
+----------+------+--------------+-------------------+--------------+------------+------------+--------+
| dup2     | 33   | int fd       |  int fd           |              |            |            |        | 
+----------+------+--------------+-------------------+--------------+------------+------------+--------+
```

* Dup2 example (redirect stdout to a file):

```C
int fd = open("tmp.txt", O_WRONLY);
dup2(fd, STDOUT_FILENO);
printf("Now this gets written to tmp.txt!\n");
```

### Fork

* Creates a child process
* Execution begins at the same point as the parent
* Return value for parent is the PID of the child
* Return value for child is 0

```text
+----------+------+--------------+-------------------+--------------+------------+------------+--------+
|Syscall   | RAX  |  RDI         |  RSI              | RDX          | R10        | R8         | R9     |
+----------+------+--------------+-------------------+--------------+------------+------------+--------+
| fork     | 57   |              |                   |              |            |            |        | 
+----------+------+--------------+-------------------+--------------+------------+------------+--------+ 
```

* Inherits copy\* of parent's memory space
* Also inherits copy of existing file descriptors
  * New descriptors will be unique entries

\* On most modern systems, the copy is actually a copy-on-write

```C
if(0 == (pid = fork())) {
    printf("We are in the child process!\n");
} else {
    printf("We are in the parent process!\n");
}
```

### Lab - File I/O

Create system call wrappers to:

* Open existing file
* Read from a file
* Create a new file
* Write to a file
* Close a file
* Bonus
  * Delete a file using unlink

## Threading

* Understand at a basic level the Linux threading model
* Understand some of the pitfalls of working with multithreaded applications
* Understand and implement some of the basic synchronization tools provided by the x86(_64) instruction set
* Implement a simple threading library

### What is a Thread?

* Each thread is essentially a separate stream of execution
  * The register values for each thread are different
  * This is referred to as "context"
  * Transitions from one thread to another is referred to as "switching context"
* Multiple threads may be running at the same time
* It is difficult (if not impossible!) to predict how scheduling will occur

### Synchronization

* Access to data needs to be synchronized (meaning: we need to make sure only one thread at a time can modify it)
* Race conditions happen if multiple threads are trying to update the same data at once

### Safe memory access

* Think in terms of "transactions"
* The lock prefix
* Some instructions, such as xchg, implicitly lock

### The `clone` Syscall

* This syscall creates a new process, but allows you to specify some amount of sharing with the parent process
* Threads and processes in Linux are synonymous, but the amount of resources they share may differ

### Clone

```text
+--------+------+------------------+-------------------+-----------+------------+
|Syscall | RAX  |  RDI             |  RSI              | RDX       | R10        | 
+--------+------+------------------+-------------------+-----------+------------+
| Clone  | 56   | Clone flags      | Stack Pointer     | parent tid| child tid  | 
+--------+------+------------------+-------------------+-----------+------------+
```

### Clone Flags

Some flags we\'ll want for our thread library:

```nasm
%define CLONE_VM      0x00000100 ; VM shared between procs.  
%define CLONE_FS      0x00000200 ; fs info shared  
%define CLONE_FILES   0x00000400 ; open files shared 
%define CLONE_SIGHAND 0x00000800 ; signal handlers shared.  
%define CLONE_THREAD  0x00010000 ; add to same thread group.  
```

### Basic Steps to Success

1. Allocate Stack Space
2. Call Clone
3. Transfer Control to Intended function
4. Block main thread until children are done

### Allocating Stack Space

* The stack grows down, and thus we need to give the high part of the new stack segment to clone
* mmap is the best choice to do this, as it has flags that let us specify that we wish to use the allocated memory as a thread stack:

```nasm
%define MAP_GROWSDOWN   0x0100
```

### Calling Clone

* As seen above, clone has several arguments
* For our purposes, only two are really useful: the flags argument (RDI), and a pointer to our new stack
* We'll need to get to the end of the new stack:

```nasm
; assuming rsi contains a pointer to 
; our newly allocated stack segment
lea rsi, [rsi + STACK_SIZE]  
```

* After clone, both the parent and child continue executing in the same place (right after the syscall)
* The child (our newly created thread) will have the same initial register values as the parent, with two exceptions:
  * RAX - this will be set to 0
  * RSP - this will now point to our new stack
* The parent will now have (in RAX) the PID of the thread

### Running the Thread Function

* A number of options exist to transfer control to the new function
  * Pass via non-volatile register
  * Pass via stack
* If any thread-specific setup is to be done, just need to:

```nasm
test rax, rax
jz .child
jmp .parent
```

* easiest method of control transfer is probably passing via the new stack

### Running the Thread Function (cont\'d)

* Recall from our section on control flow that the ret instruction essentially performs "pop rip" (or pop X + jmp X)
* Thus, we can now set our stack up so that the new thread function will be our return point (we'll just change the way our stack looks before the call to clone):

Now, instead of:

```nasm
lea rsi, [rsi + STACK_SIZE]
; ...
syscall
```

we will:

```nasm
lea rsi, [rsi + STACK_SIZE - 8]
mov [rsi], rdi  ; our function pointer
; ...
syscall
; ...
ret
```

* With our function set to be at the top of the new stack, we can now simply return
* On return, our new thread will begin executing inside of the thread function
* This works wonderfully, BUT
  * What happens when the thread function returns?

### Exit

* We need to ensure that we call exit after execution completes
* Since we are at the top of the stack to begin with, there is no place to go
* The easy solution:

```nasm
lea rsi, [rsi + STACK_SIZE - 8]
mov [rsi], rdi  ; our function pointer
; ...
syscall
test rax, rax ; check to see if we are parent/child
jnz .parent ; jump to end if we are the parent
pop rax ; pop the function pointer (top of stack)
call rax    ; call our thread function!
; ...
call exit   ; call exit (no place to return)
.parent:
; ...       ; parent: cleanup/return
ret
```

### A Better Exit Strategy

* We can take the previous code a step further, and add another return address to the stack
* If we put exit first, we will still be able to transfer control in the same fashion, but don't need to wrap out child function with additional calls

```nasm
lea rsi, [rsi + STACK_SIZE - 8]
mov [rsi], exit     ; our exit function
sub rsi, 8          ; go back just a bit
mov [rsi], rdi      ; now our function pointer
; ...
syscall
; ...
ret
```

### Waiting till done

* Since all of the threads are part of the same thread group, can't wait() for them
* Alternate strategy is to "pause"
  * Will block us until a signal of some sort happens (such as all child threads exiting)
  * Syscall takes no arguments

### Pause

```text
+--------+------+------------------+-------------------+-----------+------------+
|Syscall | RAX  |  RDI             |  RSI              | RDX       | R10        | 
+--------+------+------------------+-------------------+-----------+------------+
| Pause  | 34   |                  |                   |           |            | 
+--------+------+------------------+-------------------+-----------+------------+
```

### Race Conditions

* Can occur when multiple threads access data at once, where the data is being modified
* Can be rather difficult to spot at first
* Multiple strategies exist to mitigate
  * Locks
  * Atomic Instructions
* Can be difficult to get absolutely correct

```text
Think in terms of a busy intersection with no stop sign.
```

### What do Race Conditions look like?

```nasm
mov rax, [rdi] ; we load our data
; but by the time we reach here,
; any number of things could have
; happened to the value in the pointer
test rax, rax
jz .bad_stuff
```

### More Problems

* Deadlocks
* Starvation
* Recursive locking
* And much, much, more!

### Making Atomic adds and Comparisons

```nasm
lock xadd       ; exchange and add
lock bts        ; bit test and set
lock btr        ; bit test and clear
lock cmpxchg    ; compare and swap
xchg            ; implicitly locks
```

### XADD

Exchanges the values in its two operands, adds them together, and stores the result into the first operand. Can be used with the lock prefix.

```nasm
xadd rax, rdx
; rdi contains: a pointer to "20", rax contains: 10
lock xadd [rdi], rax ; rdi now contains a pointer to "30"
```

### Bit Test and Set, Bit Test and Clear

Tests and sets the selected bit in memory, sets the carry bit to indicate the previous value. Bit test and clear resets the bit to 0, setting the carry bit to indicate the previous value.

```nasm
lock bts dword [rdi], 0
jc .was_set
; ...
lock btr dword [rdi], 0
jc .was_set
```

### Compare and Swap

Compares the first operand to the value in RAX/EAX/AX/AL, if they are equal, copies the second operand into the destination, and sets the zero flag (ZF). Otherwise, it leaves the destination alone, and clears the zero flag.

```nasm
mov rax, [rdi]
lock cmpxchg [rdi], 1
jnz .not_replaced
```

### Creating a Simple Spinlock

```nasm
lock_func:
    ; ...
    lock bts [rdi], 0
    jc lock_func
    ; ...
.done:
    ret

unlock_func:
    ; ...
    lock btr [rdi], 0
    ; ...
```
