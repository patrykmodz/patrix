#include "drivers/vga/vga.h"
#include "drivers/vga/vgacon.h"

int curs_x;
int curs_y;

void vgacon_char(char character) {
    vga_char(character);
    //sync
    curs_x = vga_x;
    curs_y = vga_y;
    vga_setcurs(curs_x, curs_y);
}

void vgacon_init() {
    curs_x = vga_x;
    curs_y = vga_y;
}


// verify that the console was initialised correctly.
bool vgacon_verify() {
    // check whether the console cursor matches the vga cursor.
    bool valid = curs_x == vga_x && curs_y == vga_y;

    // return whether the console initialisation succeeded.
    return valid;
}