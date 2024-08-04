bits 64

SECTION .data
deobfuscated db 'deobfuscated.txt', 0h

SECTION .text
global deobfuscate
global open_file
global write_to_file
global open_read_obfuscated_file

deobfuscate:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; deobfuscate
;
; This function should deobfuscate a string by
; XOR'ing each byte with the letter 'X'
; (hex 0x58).
;
; Arguments:
; - rdi: Pointer to the obfuscated string
; - rsi: Length of the string
;
; Return Value:
;   N/A
;
; Hints:
; - Loop through the string, applying XOR to
;   each byte.
; - Stop when the length reaches zero.
; - Save rdi pointer at the start and restore
;   at the end (iff you inc/dec rdi)
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


open_file:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; open_file
;
; This function creates/opens a file for reading and writing.
; The file should be opened using the O_RDWR flag. Mode should 
; be set to 0644.
;
; Arguments:
; - rdi: Pointer to the filename
;
; Return Value:
; - Valid file descriptor from calling sys_open
;
; Hints:
; - Use the syscall number 2 for sys_open.
; - Use the O_RDWR flag (value 2) for read/write and
;   O_CREAT flag (value 0100). You'll need to `or` them.
; - Use 0644 for file mode (rdx), 0x1A4 in octal
; - Store the file descriptor in rax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


write_to_file:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; write_to_file
;
; This function writes the decoded message
; to the opened file.
;
; Arguments:
; - rdi: File descriptor
; - rsi: Pointer to decoded string
; - rdx: Length of the string
;
; Return Value:
;   N/A
;
; Hints:
; - Use the syscall number 1 for sys_write.
; - File descriptor should be in rdi.
; - Pointer to the buffer (string) should be in rsi.
; - Length of the string should be in rdx.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

; BONUS
open_read_obfuscated_file:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; open_read_obfuscated_file:
;
; 1.) This function opens a file for reading. The file should 
;   be opened using the O_RDONLY flag. Filename is passed in rdi.
; 2.) This function should use the buffer passed in rsi to
;     store the file contents.
; 3.) Content length is given
;
; Summary: open file and read contents
;
; Arguments:
; - rdi: Pointer to the filename
; - rsi: Buffer to store contents
; - rdx: Content length to read
;
; Return Value:
;   Length of content read into buffer
;
; Hints:
; - Use the syscall number 2 for sys_open.
; - Use the O_RDONLY flag (value 0) for read.
; - Save rax (the fd) to a new register
;
; - Use the syscall number 0 for sys_read.
; - Use the saved fd
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret