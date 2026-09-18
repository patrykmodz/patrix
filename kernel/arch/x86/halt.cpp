#include "arch/x86/halt.h"

//halt the cpu indefinitely.
[[noreturn]] void kernel_halt() {

    //disable interrupts before halting the cpu.
    asm volatile ("cli");

    //halt the cpu until the next interrupt.
    while (true) {
        asm volatile ("hlt");
    }
}