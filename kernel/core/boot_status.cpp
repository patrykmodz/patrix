#include "core/boot_status.h"
#include "drivers/vga/vga.h"
#include "drivers/vga/vgacon.h"


void boot_status(BootStatus status, const char* name) {
    if (status == BootStatus::OK) {
        VGA_COLOUR = VGA_WHITE;
        vgacon_char('[');
        VGA_COLOUR = VGA_GREEN;
        vgacon_str(" OK ");
        VGA_COLOUR = VGA_WHITE;
        vgacon_char(']');
        vgacon_char(' ');
    }
    else if (status == BootStatus::WARNING) {
        VGA_COLOUR = VGA_WHITE;
        vgacon_char('[');
        VGA_COLOUR = VGA_YELLOW;
        vgacon_str(" WARN ");
        VGA_COLOUR = VGA_WHITE;
        vgacon_char(']');
        vgacon_char(' ');
    }
    else if (status == BootStatus::FAILED) {
        VGA_COLOUR = VGA_WHITE;
        vgacon_char('[');
        VGA_COLOUR = VGA_RED;
        vgacon_str(" FAIL ");
        VGA_COLOUR = VGA_WHITE;
        vgacon_char(']');
        vgacon_char(' ');
    }

    vgacon_str(name);
    vgacon_char('\n');
    vga_updatecurs();
}