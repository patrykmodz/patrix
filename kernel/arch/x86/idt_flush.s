.section .text

.global idt_flush

idt_flush:
    #load the address of the idt pointer from the stack.
    mov 4(%esp), %eax
    #load the idt pointer into the idtr register.
    lidt (%eax)
    #return to the function that called idt_flush.
    ret