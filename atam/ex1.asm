.global _start

.section .text
_start:
    movq num,%rax
    movq $64,%rcx

loop:
    test $1,%rax
    jz next
    add $1,countBits
    
next:
    shr $1,%rax
    loop loop
    