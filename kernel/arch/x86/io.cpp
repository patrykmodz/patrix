#include "kernel/arch/x86/io.h"

//write an 8-bit value to an x86 I/O port.
void outb(unsigned short port, unsigned char value) {

    //send the value to the specified port.
    asm volatile (
        "outb %0, %1"
        :
        : "a"(value), "Nd"(port)
    );
}