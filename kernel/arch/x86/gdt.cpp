#include "kernel/arch/x86/gdt.h"

//store the global descriptor table entries.
GDTEntry gdt[3];

//store the location and size of the global descriptor table.
GDTPointer gdt_pointer;

/*
index        which GDT entry
base         where the segment starts
limit        how large the segment is
access       permissions/type
granularity  extra descriptor settings
*/

//set the values of one gdt entry.
void gdt_set_entry(
    int index,
    unsigned int base,
    unsigned int limit,
    unsigned char access,
    unsigned char granularity
) {
    //store the lower 16 bits of the base address.
    gdt[index].base_low = base & 0xFFFF;
    //store the middle 8 bits of the base address.
    gdt[index].base_middle = (base >> 16) & 0xFF;
    //store the upper 8 bits of the base address.
    gdt[index].base_high = (base >> 24) & 0xFF;
    //store the lower 16 bits of the segment limit.
    gdt[index].limit_low = limit & 0xFFFF;
    //store the upper 4 bits of the segment limit and granularity settings.
    gdt[index].granularity = ((limit >> 16) & 0x0F) | (granularity & 0xF0);
    //store the segment access settings.
    gdt[index].access = access;
}

//initialize the global descriptor table.
void gdt_init() {
    //set the size of the gdt in bytes, minus one.
    gdt_pointer.limit = sizeof(gdt) - 1;
    //set the address of the gdt.
    gdt_pointer.base = (unsigned int)&gdt;

    //create the null descriptor.
    gdt_set_entry(0, 0, 0, 0, 0);
/*
base        = 0
limit       = 0xFFFFFFFF
access      = 0x9A
granularity = 0xCF
*/
    //create the kernel code descriptor.
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    //create the kernel data descriptor.
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    //load the gdt and activate its segment descriptors.
    gdt_flush((unsigned int)&gdt_pointer);
}