bits 64

extern value
extern buf
extern val1
extern val2
global first_func, second_func, third_func, fourth_func, fifth_func, sixth_func


first_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Move the number 42 into
;  the register RAX.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	ret


second_func:
    mov rcx, 0x50
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Copy the contents of RCX into
; RBX.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rax, rbx
    ret


third_func:
    mov rcx, value
    mov rax, 0x20
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Copy the value from RAX to the
; location RCX points to.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


fourth_func:
    mov rcx, value
    xor rax, rax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Copy the value stored in the
; location RCX points to into RAX.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


fifth_func:
    mov rcx, buf
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Use LEA to calculate the address
; of the third element in the list,
; and copy the value stored at that
; address into RAX.
;
; Hint: each element size is 8 bytes 
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


sixth_func:
    mov rcx, val1
    mov rdx, val2
    xor rax, rax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Use XCHG to swap two values
; stored in addresses in memory.
; 
; Hint: use a register or two
; to save value before xchg
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret
