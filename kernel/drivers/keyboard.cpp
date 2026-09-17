#include "kernel/arch/x86/io.h"
#include "kernel/arch/x86/pic.h"
#include "kernel/drivers/vga.h"
#include "kernel/drivers/scancodes.h"

//KEYMAPS
#include "kernel/drivers/keymap.h"


unsigned short read_scancode() {
    unsigned short result = inb(0x60);
    return result;
}


void handle_key(unsigned short scancode) {
    if(scancode == KEY_A) {
        vga_char('a');
        vga_updatecurs();
    }
    if(scancode == KEY_F1) {
        vga_clear();
        vga_updatecurs();
    }
}


void keyboard_interrupt() {
    unsigned short scancode = read_scancode();
    handle_key(scancode);
}