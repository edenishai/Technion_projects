.global _start

.section .text
_start:
    xor %rax,%rax
    xor %rbx,%rbx
    xor %rcx,%rcx
    xor %r15,%r15
    movl $0,begin
    movl $0,len

loop:
    cmpl n,%r15d
    je end
    inc %ecx
    cmpl len,%ecx
    jle continue
    movl %ebx,begin
    movl %ecx,len
    
    continue:
        movl arr(,%r15d,4),%eax
        inc %r15
        cmpl arr(,%r15d,4),%eax
        jg loop
  
    new_sequance:
        movl %r15d,%ebx
        xor %rcx,%rcx
        
    jmp loop
        
end:
    