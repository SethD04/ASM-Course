bits 64

extern buf
extern tempfloat1
extern tempfloat2

section .text
global ex_strlen, find_largest, copy_reverse, find_min, swap_func

ex_strlen:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  This function has one argument:
;  - Param1: A pointer to a string
;
;  Find the length of the string
;  passed to ex_strlen
;
;  System V calling conventions apply
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


find_largest:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  This function has two arguments:
;  - Param1: A pointer to an array of size_t elements
;  - Param2: The number of elements in the array
;
;  Find and return the largest element in the array.
;
;  System V calling conventions apply
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


copy_reverse:
    push rbp
    mov rbp, rsp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  This function has two arguments:
;  - Param1: RDI a pointer to the source string
;  - Param2: RSI a pointer to the dest buffer
;  - Param3: RDX is the length of the string in RDI
;
;  Copy the values from source to destination in
;  in reverse. 
; 
;  HINT: there might be some useful flags
;        in the string instructions
;        using lea, can start at end
;        and copy byte by byte
;        (dec one and inc the the other)
;
;  System V calling conventions apply
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

find_min:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  This function has two arguments:
;  - Param1: scalar value
;  - Param2: scalar value
;
;  Find the min of the two, and return 
;  it as your result.
;
;  System V calling conventions apply
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


swap_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  BONUS
;  This function has two arguments:
;  - Param1: a pointer to float
;  - Param2: a pointer to float
;
;  Swap the values held in the two pointers.
;
;  System V calling conventions apply
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;  END student code.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ret
