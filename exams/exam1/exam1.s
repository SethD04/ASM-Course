bits 64

extern buf
global first_func, second_func, third_func, fourth_func, fifth_func

first_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  First problem:
;  
;  Move the number 8 into
;  the register RAX.
;
;  Next add 14 to RAX
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


second_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Second problem:
;  
;  Move the number 10 into
;  the register RAX.
;
;  Next subtract 3 from RAX
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


third_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Third problem:
;  
;  Move the number 7 into
;  the register RAX.
;
;  Next multiply the value in
;  RAX by 5.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


fourth_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Fourth problem:
;  
;  Move the number 120 into
;  the register RAX.
;
;  Next divide the value in
;  RAX by 6.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret


fifth_func:
  lea rcx, [rel buf]
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  BONUS:
;
;  You will need to use LEA to calculate
;  addresses in a list of 4 byte elements, 
;  and then copy the value of the fourth
;  element stored at that address into RAX.
;
;  There is a a pointer to the
;  beginning of the list stored
;  in RCX.
;
;  Hint: clear RAX
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret
