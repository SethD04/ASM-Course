bits 64

global first_func, second_func, third_func, fourth_func, fifth_func

first_func:
    xor rax, rax
    mov rcx, 10
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Add 10 to the value stored
;  in RAX.
;
;  Add RCX and RAX, make sure the
;  result is in RAX
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

second_func:
    mov rax, 35
    mov rcx, 10
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Subtract 15 from the value
;  in RAX.
;
;  Subtract RCX from RAX, result
;  should be stored in RAX
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

third_func:
    mov rcx, 5
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Multiply RCX by 20.
;
;  Return the result in RAX.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

fourth_func:
    mov rax, 18
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Divide RAX by 3 and return
;  the quotient.
;  Hint: clear the high bits!
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

fifth_func:
    mov rax, 13
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Divide RAX by 4 and move
;  the remainder into RAX.
;  Hint: clear the high bits!
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret
