#include "kernel/boot_status.h"
#include "kernel/drivers/vga.h"


void boot_status(BootStatus status, const char* name) {
    if (status == BootStatus::OK) {
        vga_str("[ OK ] ");
    }
    else if (status == BootStatus::WARNING) {
        vga_str("[ WARN ] ");
    }
    else if (status == BootStatus::FAILED) {
        vga_str("[ FAIL ] ");
    }

    vga_str(name);
    vga_char('\n');
    vga_updatecurs();
}