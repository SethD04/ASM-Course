bits 64

extern value, value_outbuf, second_value, second_outbuf
global first_func, second_func, third_func, fourth_func, fifth_func
global sixth_func, seventh_func

first_func:
    push rbp
    mov rbp, rsp
    mov rax, 0xfeedbeef
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Using the and instruction,
;  check to see if the 16th bit
;  is set in the value stored
;  in RAX. Set RAX equal to 1
;  if the bit is set, and 0 if
;  the bit is not set. Hint:
;  setting a register equal to
;  1 and left shifting may help.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

second_func:
    push rbp
    mov rbp, rsp
    mov rax, 0xdeadbeef
    mov rdx, 0xc0ffee
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Find the intersection of bits
;  that are set in both RDX and RAX.
;  Set RAX equal to the result.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

third_func:
    push rbp
    mov rbp, rsp
    mov rax, 0x1000
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Without using the mov instruction,
;  set RAX equal to 0.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

fourth_func:
    push rbp
    mov rbp, rsp
    mov rax, 0x04
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Using only bit shifts,
;  multiply the value stored in
;  RAX by 16.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

fifth_func:
    push rbp
    mov rbp, rsp
    mov rax, 64
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Using only bit shift
;  instructions, divide the
;  value in RAX by 8.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    pop rbp
    ret

sixth_func:
    push rbp
    mov rbp, rsp
    mov rax, second_value
    mov rax, qword [rax]
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  The string Success! has been
;  stored in RAX, but is
;  slightly mangled ("ccuS!ess").
;  Set it to
;  the correct order via byte
;  rotations (the result will
;  print out in console).
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rcx, second_outbuf
    mov rcx, [rcx]
    mov [rcx], rax
    pop rbp
    ret

seventh_func:
    push rbp
    mov rbp, rsp
    mov rax, value
    mov rax, qword [rax]
    mov rdx, 0xbb
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  An 8-byte message has been
;  XOR-encoded with the key 0xBB,
;  and stored in RAX. Using all
;  of the knowledge you've gained
;  so far, XOR each byte of RAX
;  with 0xBB. The resulting message
;  will print out in console.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rdi, value_outbuf
    mov rdi, [rdi]
    mov [rdi], rax
    xor rax, rax
    pop rbp
    ret
