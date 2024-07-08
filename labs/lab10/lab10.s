bits 64

global first_func, second_func

first_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Using the rdtsc instruction,
;  1.) Obtain the current timestamp
;  2.) Combine the low 32 bits (from RAX)
;      and the high 32 bits (RDX), and
;      return them.
;
;   Hint: look at the return value for 
;   gettsc() to see how to combine reg
;   values
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret

second_func:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Using CPUID, get the vendor
;   string, and copy each chunk
;   returned into the buffer
;   passed to your function.
;   The buffer should be the
;   first (and only) argument.
;
;   Hint 1: preserve rbx and clear rax
;   Hint 2: look at getvstr(char **buf)
;   for example on how to save results to rdi
;
;  BEGIN student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  END student code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ret
