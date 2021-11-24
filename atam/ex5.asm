.global _start

.section .text
_start:
    xor %rax,%rax
    xor %rbx,%rbx
    xor %rcx,%rcx
    xor %rdx,%rdx
    cmpq $0,head
    je end
    movq head,%rsi
    movq head,%rdi
    movq (%rsi),%r11
    cmpq src,%r11
    je head_is_src
    jmp loop
    
head_is_src:    
    movq $head,%rsi
    jmp searching_dst
    
loop:
    cmpq $NULL,8(%rdi)
    je end
    
    searching_src:
        movq src,%rax
        movq 8(%rdi),%r11
        cmpq %rax,(%r11)
        jne continue
        movq %rdi,%rsi
        leaq 8(%rsi),%rsi
        
    searching_dst:
        movq dst,%rax
        movq 8(%rdi),%r11
        cmpq %rax,(%r11)
        je swap
        
        movq 8(%rdi),%rdi
        cmpq $NULL,8(%rdi)
        je end
        jmp searching_dst
    
    continue:
        movq 8(%rdi),%rdi
    
    jmp loop
    
swap:
    lea 0(%rdi),%rbx
    lea 8(%rbx),%rbx
    movq (%rbx),%rbx 
    
    movq (%rsi),%rax
    
    lea 8(%rax),%rcx
    lea 8(%rbx),%rdx
    
    movq (%rcx),%r11
    movq (%rdx),%r12
    
    movq %rdi,%r8
    lea 8(%r8),%r8
    
    cmp %r11,%rbx
    je one_after_other
    
    movq %rbx,(%rsi)
    movq %r11,(%rdx)
    movq %r12,(%rcx)
    movq %rax,(%r8)
    jmp end  
    
one_after_other:
    movq %rbx,(%rsi)
    movq %rax,(%rdx)
    movq %r12,(%rcx)
    
end:
