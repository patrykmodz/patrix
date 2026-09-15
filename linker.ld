ENTRY(_start)

SECTIONS
{
    #place the kernel at address 1 MiB.
    . = 1M;

    #creates the final kernel's .text section.
    .text : {
        *(.multiboot) #take every .multiboot section and put it here.
        *(.text) #take every .text section and put it here.
    }

    #read-only data.
    .rodata : {
        *(.rodata)
    }

    #initialized writable data.
    .data : {
        *(.data)
    }

    #uninitialized data.
    .bss : {
        *(COMMON) #GCC can place certain uninitialized global/common symbols here.
        *(.bss)
    }
}