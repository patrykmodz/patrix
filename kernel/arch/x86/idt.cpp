#include "kernel/arch/x86/idt.h"

//store the interrupt descriptor table entries.
IDTEntry idt[256];
//store the location and size of the interrupt descriptor table.
IDTPointer idt_pointer;

//initialize the interrupt descriptor table.
void idt_init() {
}

//set the values of one idt entry.
void idt_set_entry(
    int index,
    unsigned int base,
    unsigned short selector,
    unsigned char flags
) {
    //store the lower 16 bits of the handler address.
    idt[index].base_low = base & 0xFFFF;
    //store the upper 16 bits of the handler address.
    idt[index].base_high = (base >> 16) & 0xFFFF;
    //set the kernel code segment selector.
    idt[index].selector = selector;
    //clear the reserved byte.
    idt[index].zero = 0;
    //set the interrupt gate flags.
    idt[index].flags = flags;
}

//set the first idt entry to the test interrupt handler.
void idt_test_init() {
    idt_set_entry(
        0,
        (unsigned int)idt_test_handler,
        0x08,
        0x8E
    );
}