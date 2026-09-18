#include "arch/x86/io.h"

//write an 8-bit value to an x86 I/O port.
void outb(unsigned short port, unsigned char value) {
    //send the value to the specified port.
    asm volatile (
        "outb %0, %1"
        :
        : "a"(value), "Nd"(port)
    );
}

//read an 8-bit value from an x86 i/o port.
unsigned char inb(unsigned short port) {
    //store the value read from the port.
    unsigned char value;

    //read one byte from the specified i/o port.
    asm volatile (
        "inb %1, %0"
        : "=a"(value)
        : "Nd"(port)
    );

    //return the value read from the port.
    return value;
}