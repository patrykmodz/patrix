#include "kernel/boot_init.h"
#include "kernel/drivers/vga.h"
#include "kernel/arch/x86/io.h"
#include "kernel/arch/x86/gdt.h"

void boot_init() {
    vga_init();
    //initialize the global descriptor table.
    gdt_init();

    //show that execution continued after loading the gdt.
    vga_write_string("gdt loaded\n");
}