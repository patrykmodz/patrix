#include "arch/x86/io.h"
#include "arch/x86/pic.h"
#include "drivers/vga/vga.h"


//KEYMAPS
#include "drivers/keyboard/keymap/keymaps.h"


unsigned short read_scancode() {
    unsigned short result = inb(0x60);
    return result;
}

void handle_key(unsigned short scancode) {
    for (int i = 0; i < sizeof(ukmap) / sizeof(ukmap[0]); i++) {
        if (ukmap[i].scancode == scancode) {
            if (ukmap[i].type == key_type::CHARACTER &&
                ukmap[i].modifier == key_modifier::BASE) {
                
                vga_char(ukmap[i].output);
            }
        }
    }
}

void keyboard_interrupt() {
    unsigned short scancode = read_scancode();
    handle_key(scancode);
}