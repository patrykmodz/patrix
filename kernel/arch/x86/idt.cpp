#include "kernel/arch/x86/idt.h"


//store the interrupt descriptor table entries.
IDTEntry idt[256];
//store the location and size of the interrupt descriptor table.
IDTPointer idt_pointer;


//initialize the interrupt descriptor table.
void idt_init() {
    //set the size of the idt in bytes, minus one.
    idt_pointer.limit = sizeof(idt) - 1;
    //set the address of the idt.
    idt_pointer.base = (unsigned int)&idt;

    //clear all idt entries.
    for (int i = 0; i < 256; i++) {
        //clear the idt entry.
        idt[i].base_low = 0;
        idt[i].selector = 0;
        idt[i].zero = 0;
        idt[i].flags = 0;
        idt[i].base_high = 0;
    }

    //initialize the test interrupt.
    idt_test_init();
    //load the idt into the cpu.
    idt_flush((unsigned int)&idt_pointer);
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


//verify that the interrupt descriptor table was loaded correctly.
bool idt_verify() {

    //store the currently loaded idt pointer.
    IDTPointer loaded_pointer;

    //read the idt pointer currently loaded into the cpu.
    asm volatile (
        "sidt %0"
        : "=m"(loaded_pointer)
    );

    //check that the loaded idt matches the idt created by patrix.
    return loaded_pointer.base == (unsigned int)&idt
        && loaded_pointer.limit == sizeof(idt) - 1;
}