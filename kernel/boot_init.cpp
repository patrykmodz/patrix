#include "kernel/boot_init.h"
#include "kernel/drivers/vga.h"
#include "kernel/arch/x86/gdt.h"
#include "kernel/boot_status.h"
#include "kernel/arch/x86/idt.h"


void boot_init() {
const char* vga_description = "vga initialization";
const char* gdt_description = "gdt initialization";
const char* idt_description = "idt initialization";


    //initialize the vga driver.
    vga_init();
    //hide the hardware cursor during boot.
    vga_hide_cursor();

    //verify that vga text memory is accessible.
    if (vga_verify()) {
        boot_status(BootStatus::OK, vga_description);
    } else {
        boot_status(BootStatus::FAILED, vga_description);
        return;
    }

    //initialize the global descriptor table.
    gdt_init();

    //verify that the gdt was loaded correctly.
    if (gdt_verify()) {
        boot_status(BootStatus::OK, gdt_description);
    } else {
        boot_status(BootStatus::FAILED, gdt_description);
        return;
    }

    idt_init();

    if (idt_verify()) {
        boot_status(BootStatus::OK, idt_description);
    } else {
        boot_status(BootStatus::FAILED, idt_description);
        return;
    }
}