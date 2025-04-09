.section __TEXT,__text
.global _diffsquare

_diffsquare:
    # input: %eax, %ebx
    # computes: (eax + ebx) * (eax - ebx)
    
    push %ecx                # Save ecx, since we'll use it
    movl %eax, %ecx          # ecx = eax
    addl %ebx, %ecx          # ecx = eax + ebx

    movl %eax, %edx          # edx = eax
    subl %ebx, %edx          # edx = eax - ebx

    imull %edx, %ecx         # ecx = (eax + ebx) * (eax - ebx)

    movl %ecx, %eax          # eax = result

    pop %ecx                 # Restore ecx
    ret
