#include "kernel/kernel_panic.h"
#include "kernel/drivers/vga.h"
#include "kernel/arch/x86/halt.h"

//halt the kernel after an unrecoverable error.
[[noreturn]] void kernel_panic(const char* reason) {
    //display the kernel panic message.
    vga_write_string("\nkernel panic: ");
    //display the reason for the panic.
    vga_write_string(reason);
    //halt the processor.
    kernel_halt();
}