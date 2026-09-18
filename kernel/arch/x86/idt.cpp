#include "arch/x86/idt.h"
#include "drivers/vga.h"
#include "core/panic.h"
#include "arch/x86/pic.h"
#include "drivers/keyboard/keyboard.h"


//store the interrupt descriptor table entries.
IDTEntry idt[256];
//store the location and size of the interrupt descriptor table.
IDTPointer idt_pointer;


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


void idt_set_entries() {
    //install the divide error handler at interrupt vector 0.
    idt_set_entry(
        0,
        (unsigned int)interrupt_stub_0,
        0x08,
        0x8E
    );

    //install the keyboard interrupt handler at interrupt vector 0x21.
    idt_set_entry(
        0x21,
        (unsigned int)interrupt_stub_33,
        0x08,
        0x8E
    );
}


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
    //set all entries.
    idt_set_entries();

    //load the idt into the cpu.
    idt_flush((unsigned int)&idt_pointer);
}


extern "C" void interrupt_handler(InterruptFrame* frame) {
    //handle a divide error.
    if (frame->interrupt_number == 0) {
        //halt the kernel after a divide error.
        kernel_panic("divide error");
    }

    //handle a keyboard interrupt.
    if (frame->interrupt_number == 0x21) {
        //call the keybaord interrupt
        keyboard_interrupt();
        //signal that the keyboard interrupt has been handled.
        pic_eoi(1);
    }
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