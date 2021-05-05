/* ===== data ======= */
.data

# IDT
    .p2align 4
    .globl IDT
    .globl idtptr
    
IDT:
    .rept 256
    .word 0,0,0,0
    .endr
    
idtptr:
    .word  (256*8 -1)
    .long  IDT

.text
.code32

.globl setup_idt

.p2align 4

setup_idt:
    movl $ignore_int1,%edx
    movl $0x00080000,%eax
    movw %dx,%ax            /* selector = 0x0010 = cs */
    movw $0x8E00,%dx        /* interrupt gate -dpl=0, present */
    movl $IDT,%edi
    mov $256,%ecx
    
rp_sidt:
    movl %eax,(%edi)
    movl %edx,4(%edi)
    addl $8,%edi
    dec %ecx
    jne rp_sidt
    # ret  /* if do not set timer*/
    
setup_time_int_32:
    movl $time_interrupt,%edx
    movl $0x00080000,%eax    /* selector：0x0010 = cs */
    movw %dx,%ax 
    movw $0x8E00,%dx        /* interrupt gate -dpl=0, present */

    movl $IDT,%edi
    addl $(32*8), %edi
    movl %eax,(%edi)
    movl %edx,4(%edi)

    ret

time_interrupt:
    cld
    pushf
    pusha
    call tick
    popa
    popf
    iret
    
    .p2align 4
    
ignore_int1:
    cld
    pusha
    call    ignoreIntBody
    popa
    iret
