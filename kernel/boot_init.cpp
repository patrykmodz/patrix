#include "kernel/boot_init.h"
#include "kernel/drivers/vga.h"

void boot_init() {
    vga_init();
    vga_write_string("lorem ipsum");
    vga_write_char('\n');
    vga_write_string("dolor sit amet");
}