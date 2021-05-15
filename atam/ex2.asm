.global _start

.section .text
_start:
    cmp $0,num
    jle end
    xor %rcx,%rcx
    xor %rax,%rax
    xor %rbx,%rbx
    mov num,%rcx
     
loop:
    movb source(%rbx),%al
    movb %al,destination(%rbx)
    inc %rbx
    loop loop

end:
