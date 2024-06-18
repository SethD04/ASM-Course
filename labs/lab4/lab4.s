bits 64

extern value
global first_func, second_func

first_func:
    push rbp
    mov rbp, rsp
    mov rcx, 0x20
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For this task, you must allocate
;  8 bytes of space on the stack, and
;  store the value of RCX there.
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    cmp rsp, rbp
    je .nsc
    jmp .end
.nsc:
    sub rsp, 8
.end:
    pop rax
    pop rbp
    ret

second_func:
    push rbp
    mov rbp, rsp
    mov rcx, value
    mov rax, 2
    mov rdx, 4
    mov rsi, 6
    mov rdi, 8
    mov r8, 10
    mov r9, 12
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  For this task, you must allocate
;  space to manage your registers and 
;  save them to the stack as needed. 
;  Divide the number stored where RCX
;  points by 5, and place the value
;  back at that address. Make sure all
;  the register values are the same at 
;  the end of the call!
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    cmp rax, 2
    jnz .fail
    cmp rdx, 4
    jnz .fail
    cmp rsi, 6
    jnz .fail
    cmp rdi, 8
    jnz .fail
    cmp r8, 10
    jnz .fail
    cmp r9, 12
    jnz .fail
    jmp .end
.fail:
    mov rax, -1
.end:
    pop rbp
    ret
