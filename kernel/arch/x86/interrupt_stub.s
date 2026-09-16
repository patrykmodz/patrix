.section .text

.global interrupt_stub_0

.extern interrupt_handler

interrupt_stub_0:
    #push a placeholder error code because divide errors do not provide one.
    push $0
    #push the interrupt vector number.
    push $0
    #save the general purpose registers.
    pusha
    #pass the current stack pointer to the common interrupt handler.
    mov %esp, %eax
    #pass the interrupt frame to the common interrupt handler.
    push %eax
    #call the common interrupt handler.
    call interrupt_handler
    #remove the interrupt frame argument.
    add $4, %esp
    #restore the general purpose registers.
    popa
    #remove the interrupt vector number and error code.
    add $8, %esp
    #return from the interrupt.
    iret
