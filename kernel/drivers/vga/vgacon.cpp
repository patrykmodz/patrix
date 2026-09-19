#include "drivers/vga/vga.h"
#include "drivers/vga/vgacon.h"

int curs_x;
int curs_y;

void vgacon_syncurs() {
    vga_x = curs_x;
    vga_y = curs_y;
    vga_setcurs(curs_x, curs_y);
}

void vgacon_char(char character) {
    if(character=='\n') {
        curs_x = 0;
        curs_y++;
        vgacon_syncurs();
    }else {
        vga_char(character);
        curs_x++;
        vgacon_syncurs();
    }


    //move to the beginning of the next line when the cursor reaches the right edge.
    if (curs_x >= 80) {
        curs_x = 0;
        curs_y++;
    }

    //scroll the screen when the cursor moves below the last row.
    if (curs_y >= 25) {
        vga_scroll();
        vgacon_syncurs();
    }
}

void vgacon_str(const char* string) {
    //continue until the null terminator is reached.
    while (*string != '\0') {
        //write the current character to the screen.
        vgacon_char(*string);
        //move to the next character in the string.
        string++;
    }
}


void vgacon_init() {
    //initial sync
    curs_x = vga_x;
    curs_y = vga_y;
}

void vgacon_bck() {
    if(curs_x>0) {
        curs_x--; // we go back one pos.
        vgacon_syncurs();
        vgacon_char(' '); // moves us forward.
        curs_x--; // we go back again.
        vgacon_syncurs();
    }
}

// verify that the console was initialised correctly.
bool vgacon_verify() {
    // check whether the console cursor matches the vga cursor.
    bool valid = curs_x == vga_x && curs_y == vga_y;

    // return whether the console initialisation succeeded.
    return valid;
}

void vgacon_clear() {
    vga_clear();
    curs_x = 0;
    curs_y = 0;
    vgacon_syncurs();
}