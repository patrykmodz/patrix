#include "kernel/boot_init.h"
#include "kernel/drivers/vga.h"
#include "kernel/arch/x86/io.h"
#include "kernel/arch/x86/gdt.h"
#include "kernel/boot_status.h"

void boot_init() {
    //initialize the vga driver.
    vga_init();

    //hide the hardware cursor during boot.
    vga_hide_cursor();

    //verify that vga text memory is accessible.
    if (vga_verify()) {
        boot_status(BootStatus::OK, "vga initialized");
    } else {
        boot_status(BootStatus::FAILED, "vga initialization failed");
        return;
    }

    //initialize the global descriptor table.
    gdt_init();

    //verify that the gdt was loaded correctly.
    if (gdt_verify()) {
        boot_status(BootStatus::OK, "gdt initialized");
    } else {
        boot_status(BootStatus::FAILED, "gdt initialization failed");
        return;
    }
}