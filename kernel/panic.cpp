#include "kernel/panic.h"
#include "kernel/drivers/vga.h"
#include "kernel/arch/x86/halt.h"

//halt the kernel after an unrecoverable error.
[[noreturn]] void kernel_panic(const char* reason) {
    vga_hcurs();
    vga_clear();
    VGA_COLOUR = VGA_LIGHT_BLUE;

    vga_str("\nkernel panic: ");
    vga_str(reason);

    kernel_halt();
}