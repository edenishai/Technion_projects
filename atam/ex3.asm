.global _start

.section .text
_start:
    xor %rax,%rax
    xor %rbx,%rbx
    xor %rdx,%rdx
    
loop:
    movl arr(,%rbx,4),%eax
    test %eax,%eax
    jz loop_end
    addq %rax,%rdx
    inc %rbx
    jmp loop
    
loop_end:
    test %rbx,%rbx
    jz end
    movq %rdx,%rax
    xor %rdx,%rdx
    div %rbx
    
end:
    movl %eax,avg
    