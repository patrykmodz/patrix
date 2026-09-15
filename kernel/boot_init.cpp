#include "kernel/boot_init.h"
#include "kernel/drivers/vga.h"

void boot_init() {
    vga_init();
    vga_write_char('a');
}