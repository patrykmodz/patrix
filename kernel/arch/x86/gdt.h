#pragma once

//describe one entry in the global descriptor table.
struct __attribute__((packed)) GDTEntry {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
};

//describe the location and size of the global descriptor table.
struct __attribute__((packed)) GDTPointer {
    unsigned short limit;
    unsigned int base;
};

//initialize the global descriptor table.
void gdt_init();

//load the global descriptor table and reload the segment registers.
extern "C" void gdt_flush(unsigned int pointer);