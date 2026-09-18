#include "core/boot_init.h"
#include "drivers/vga.h"
#include "arch/x86/gdt.h"
#include "core/boot_status.h"
#include "arch/x86/idt.h"
#include "arch/x86/halt.h"
#include "arch/x86/pic.h"
#include "core/panic.h"


void boot_init() {
const char* vga_description = "vga initialization";
const char* gdt_description = "gdt initialization";
const char* idt_description = "idt initialization";
const char* pic_description = "pic initialization";

    //initialize the vga driver.
    vga_init();

    if (vga_verify()) {
        boot_status(BootStatus::OK, vga_description);
    } else {
        boot_status(BootStatus::FAILED, vga_description);
        //if we have nothing to display a panic with, just halt.
        kernel_halt();
    }

    //initialize the global descriptor table.
    gdt_init();

    if (gdt_verify()) {
        boot_status(BootStatus::OK, gdt_description);
    } else {
        boot_status(BootStatus::FAILED, gdt_description);
        kernel_panic("gdt initialization failed");
    }

    //initialize the interrupt descriptor table
    idt_init();

    if (idt_verify()) {
        boot_status(BootStatus::OK, idt_description);
    } else {
        boot_status(BootStatus::FAILED, idt_description);
        kernel_panic("idt initialization failed");
    }

    //initialize the pic
    pic_init();

    if (idt_verify()) {
        boot_status(BootStatus::OK, pic_description);
    } else {
        boot_status(BootStatus::FAILED, pic_description);
        kernel_panic("pic initialization failed");
    }

    asm volatile ("sti");
}