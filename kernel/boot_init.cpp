#include "kernel/boot_init.h"
#include "kernel/drivers/vga.h"
#include "kernel/arch/x86/io.h"

void boot_init() {
    vga_init();
    vga_hide_cursor();
    vga_write_string("lorem ipsum");

    for (volatile unsigned long i = 0; i < 3000000; i++) {
    }

    vga_clear();
    vga_show_cursor();
    vga_update_cursor();
}