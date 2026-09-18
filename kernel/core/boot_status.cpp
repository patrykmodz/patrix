#include "core/boot_status.h"
#include "drivers/vga/vga.h"


void boot_status(BootStatus status, const char* name) {
    if (status == BootStatus::OK) {
        VGA_COLOUR = VGA_WHITE;
        vga_char('[');
        VGA_COLOUR = VGA_GREEN;
        vga_str(" OK ");
        VGA_COLOUR = VGA_WHITE;
        vga_char(']');
        vga_char(' ');
    }
    else if (status == BootStatus::WARNING) {
        VGA_COLOUR = VGA_WHITE;
        vga_char('[');
        VGA_COLOUR = VGA_YELLOW;
        vga_str(" WARN ");
        VGA_COLOUR = VGA_WHITE;
        vga_char(']');
        vga_char(' ');
    }
    else if (status == BootStatus::FAILED) {
        VGA_COLOUR = VGA_WHITE;
        vga_char('[');
        VGA_COLOUR = VGA_RED;
        vga_str(" FAIL ");
        VGA_COLOUR = VGA_WHITE;
        vga_char(']');
        vga_char(' ');
    }

    vga_str(name);
    vga_char('\n');
    vga_updatecurs();
}