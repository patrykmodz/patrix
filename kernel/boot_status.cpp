#include "kernel/boot_status.h"
#include "kernel/drivers/vga.h"

//display the result of a boot initialization step.
void boot_status(BootStatus status, const char* name) {
    //display a successful initialization step.
    if (status == BootStatus::OK) {
        vga_write_string("[ OK ] ");
    }

    //display a warning for an initialization step.
    else if (status == BootStatus::WARNING) {
        vga_write_string("[ WARN ] ");
    }

    //display a failed initialization step.
    else if (status == BootStatus::FAILED) {
        vga_write_string("[ FAIL ] ");
    }

    //display the name of the initialization step.
    vga_write_string(name);

    //move to the next line.
    vga_write_char('\n');
}