#include "arch/x86/io.h"
#include "arch/x86/pic.h"
#include "drivers/vga.h"


//KEYMAPS
#include "drivers/keyboard/scancodes.h"

#include "drivers/keyboard/keymap/keymap.h"
#include "drivers/keyboard/keymap/uk_keymap.h"


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