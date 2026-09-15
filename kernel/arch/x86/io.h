#pragma once

//read an 8-bit value from an x86 i/o port.
unsigned char inb(unsigned short port);
//write an 8-bit value to an x86 I/O port.
void outb(unsigned short port, unsigned char value);