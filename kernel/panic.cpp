#include "kernel/panic.h"
#include "kernel/drivers/vga.h"
#include "kernel/arch/x86/halt.h"

//halt the kernel after an unrecoverable error.
[[noreturn]] void kernel_panic(const char* reason) {
    //display the kernel panic message.
    vga_str("\nkernel panic: ");
    //display the reason for the panic.
    vga_str(reason);
    //halt the processor.
    kernel_halt();
}