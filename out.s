.section __TEXT,__text,regular,pure_instructions
.globl _main
_main:
    movl $3, %eax
    movl $2, %ebx
    .byte 0x0f, 0xaa  ## diffsquare
    ret
