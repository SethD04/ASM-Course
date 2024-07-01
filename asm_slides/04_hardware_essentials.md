# Introduction to x86 and x86_64 Assembly Language

## Hardware Overview

### Objectives

* Understand the different privilege modes of operation, and some of their implications
* Understand basic memory segmentation and some descriptor tables
* Understand, at a basic level, virtual memory
* Understand basic processor features, control registers, and how they fit together
* Understand and implement Model Specific Registers  (MSRs)
* Utilize x86(_64) instructions to identify the current processor, and understand how to programmatically query its capabilities

## Processor Modes

### User and Kernel modes

* x86(_64) defines several modes of operation (or "rings") the processor can work in
* Each mode has various instructions (and portions of memory) it is allowed to perform
* User mode (which is least privileged) is Ring 3 (which is where most of your applications reside)
* Kernel mode (most privileged) is Ring 0, which is where the core (or kernel) of the OS resides
* Rings 1 and 2 are (largely) unused by most operatings systems

### User Mode

* Mode of least privilege (Ring 3)
* Cannot touch more privileged memory sections
* Cannot execute "privileged" instructions
* Typically must task some facility in the kernel in order to get resources

### Kernel Mode

* Mode of most privilege (Ring 0)
* Can access any portion of memory (and change protection)
* Can perform privileged instructions
* Device drivers often run here (in addition to the core portions of the OS)

![image](./images/ring_levels.svg)

## Interrupts and Memory Segmentation

### Tables and Memory Segmentation

* Intel Specifies a number of tables, populated by the OS, which map functionality to the processor.
  * The Interrupt Descriptor Table, or IDT
  * The Global Descriptor Table, or GDT
  * The Local Descriptor Table, or LDT
* Virtual memory also relies on a set of page tables

## Interrupts and The Interrupt Descriptor Table

### Interrupts

* What are interrupts?
  * Interrupts provide a special mechanism to alert the kernel of an event
  * Some (though not all) can be temporarily disabled
  * Specified via the IDT
* Interrupts can be generated many ways:
  * Via hardware events (e.g., a keypress on a keyboard)
  * Page or segmentation faults
  * Software interrupts also exist
  * Many others

```text
We won't spend too much time on this particular topic (as it only
loosely relates to segmentation), but it is important to understand how
interrupts work (at a low level), and this will give you the
foundational knowledge needed to understand what's happening under the
hood later on.
```

* Interrupt Service Routines (ISRs)
  * Functions that respond to interrupts
  * Set via Interrupt Gates in the IDT (See below)

* Interrupt Gates
  * Essentially the entry number (in the IDT) of the ISR you want to call
  * The 'int' assembly instruction will call the corresponding ISR
  * The 'iret' instruction is provided (on the kernel side) to return back to user mode

### Interrupts - Example

The following code will perform an exit(0) on Linux (x86):

```nasm
mov eax, 0x01   ; the system call number
mov ebx, 0x00   ; first parameter
int 0x80        ; interrupt
```

```text
https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
```

### Segment Registers

* Segment registers are a special type of register not covered yet, which come in a variety of flavors
  * Each of them can be mapped to provide a special "view" of a section of memory
  * Most modern operating systems use a "flat" memory model, forgoing segmentation (almost) entirely
  * Still have some real world applications, particularly in Windows

* The Basics:
  * CS - Code Segment
  * DS - Data Segment
  * SS - Stack Segment
  * FS - Far Segment
  * GS - Global Segment

Example: Getting a value from some offset into a segment

```nasm
; Retrieves the value stored at offset
; 0x33 into the Global Segment
mov rax, [gs:0x33]
```

## Segmentation - Segments

* What is a segment?
  * Describes a logical section of memory
  * Specifies who can access it (e.g., what privilege level you need)
  * Indicates the range (start address and length)
* Why are they important?
  * Part of the segmentation model, used to map a flat section of memory to the segment registers

### The Global Descriptor Table (GDT)

* Initialized by the operating system
* Contains various segment descriptors in its entries
* The GDT Register (GDTR) indicates where it is located
* Contains information about how the memory in your system gets mapped
* Also (partially) defines how the transition from user to kernel mode occurs
* Intended to be a global structure

### The Local Descriptor Table (LDT)

* Similar to the GDT
* Intended to have smaller scope: e.g., a per-process construct

### Segmentation - Real World examples

* Microsoft uses segmentation to provide fast access to key data structures
* The Thread Environment Block (TEB) in user mode
  * Hangs off of the FS register in x86/GS in x64
  * Provides lots of important per-thread information
* The Processor Control Block (or KPRCB) in kernel mode
  * Hangs off of the FS register in x86/GS in x64
  * Provides lots of important per-processor information

Further Reading (if interested):

* The OSDev Wiki describes GDT initialization - http://wiki.osdev.org/GDT_Tutorial
* The Segment Descriptor Cache - Mr. Robert Collins (from a Dr. Dobbs article) - http://www.rcollins.org/ddj/Aug98/Aug98.html

## Other Processor Features

### Processor Security Features

* DEP/NX
* SMEP/SMAP
* Page Protection
* Write Protection

### Control Registers

* Control CPU enforcement of a variety of features
* Most security features are enabled in this fashion
* Requires privileged execution (Ring0) to access
* Other features (such as hardware virtualization) also enabled in this fashion
* Feature mappings detailed in the Intel manuals

### Virtual Memory

* Allows a virtual abstraction of hardware addresses
* Paging enabled via CR1
* Page Table location stored in CR3
* Tables and Directories provide fast lookup of address translations

### Page Tables and Directories

![image](./images/page_tables2.png)

Image Credit: <https://notes.shichao.io/utlk/ch2/>

### Model Specific Registers (MSRs)

* Many of these exist for x86(_64)
* Most only accessible in privileged mode
* used (sometimes) via RDMSR and WRMSR
* Others have special instructions
* Mainly documented by vendor (e.g., Intel manual)

### Time Stamp Counter

* Can read from user mode (via rdtsc)
* Can only modify from kernel mode
* Low bits of result are stored into EAX/high bits in EDX
  * This is the same on both x86 and x86_x64
  * x64 - rdtsc will clear the high bits of storage registers
  * Results can be combined on x64 to full width with a left-shift and a bitwise or

### Feature Support

* The CPUID instruction can provide information about the current CPU
  * Vendor string
  * Model number
  * Size of internal cache
  * Various features supported
* The instruction behaves similarly on BOTH x86 and x86_64
* The value in EAX at the time of the CPUID call determines what information comes back
  * 0 -> Vender ID String - stored in EBX/EDX/ECX
  * 1 -> Returns a bitfield containing supported features
  * ...

## Lab 10

MSRs and CPUID

* Copy the Lab10 folder (and its contents)
* Modify the \*.nasm file (Each function should have a comment block - lines starting with ';' containing instructions)
* Build and run using the following commands:

```bash
cmake . && cmake --build .
./lab10
```

## Section Review

* Ring 0/3
* Interrupts
* Memory Segmentation
  * GDT
  * LDT
* MSRs
