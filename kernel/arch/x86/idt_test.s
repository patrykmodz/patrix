.section .text

.global idt_test_handler

idt_test_handler:

    #return from the interrupt.
    iret