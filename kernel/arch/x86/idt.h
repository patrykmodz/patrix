#pragma once

//describe one entry in the interrupt descriptor table.
struct __attribute__((packed)) IDTEntry {
    unsigned short base_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_high;
};

//describe the location and size of the interrupt descriptor table.
struct __attribute__((packed)) IDTPointer {
    unsigned short limit;
    unsigned int base;
};

//initialize the interrupt descriptor table.
void idt_init();

//initialize the test interrupt.
void idt_test_init();

//handle the test interrupt.
extern "C" void idt_test_handler();