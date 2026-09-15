#include "kernel/drivers/vga.h"
#include "kernel/arch/x86/io.h"

//pointer to the beginning of vga text memory.
volatile unsigned short* vga_memory;
//current horizontal cursor position.
int vga_x;
//current vertical cursor position.
int vga_y;


void vga_init() {
    //set the pointer to the beginning of vga text memory.
    vga_memory = (volatile unsigned short*)0xB8000;
    //start the cursor at the left side of the screen.
    vga_x = 0;
    //start the cursor at the top of the screen.
    vga_y = 0;
}

//move all screen lines up by one line.
void vga_scroll() {
    //copy every row into the row above it.
    for (int y = 1; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            vga_memory[(y - 1) * 80 + x] = vga_memory[y * 80 + x];
        }
    }

    //clear the new bottom row.
    for (int x = 0; x < 80; x++) {
        vga_memory[24 * 80 + x] = ((unsigned short)0x07 << 8) | ' ';
    }

    //keep the cursor on the bottom row.
    vga_y = 24;
}

void vga_write_char(char character) {
    //move to the beginning of the next line when a newline is received.
    if (character == '\n') {
        vga_x = 0;
        vga_y++;

        //scroll the screen when the cursor moves below the last row.
        if (vga_y >= 25) {
            vga_scroll();
        }

        return;
    }

    //convert the two-dimensional cursor position into a one-dimensional array index.
    int index = vga_y * 80 + vga_x;
    //combine the text colour and character into one 16-bit vga entry.
    vga_memory[index] = ((unsigned short)0x07 << 8) | character;
    //move the cursor one character to the right.
    vga_x++;

    //move to the beginning of the next line when the cursor reaches the right edge.
    if (vga_x >= 80) {
        vga_x = 0;
        vga_y++;
    }

    //scroll the screen when the cursor moves below the last row.
    if (vga_y >= 25) {
        vga_scroll();
    }
}

//write each character in the string to the screen.
void vga_write_string(const char* string) {
    //continue until the null terminator is reached.
    while (*string != '\0') {
        //write the current character to the screen.
        vga_write_char(*string);
        //move to the next character in the string.
        string++;
    }
}

//clear the entire screen.
void vga_clear() {

    //go through every character cell on the screen.
    for (int i = 0; i < 80 * 25; i++) {

        //replace the character with a blank space.
        vga_memory[i] = ((unsigned short)0x07 << 8) | ' ';
    }

    //reset the cursor to the top-left corner.
    vga_x = 0;
    vga_y = 0;
}

/*
CURSOR
*/

//update the hardware cursor to match the software cursor.
void vga_update_cursor() {
    //calculate the cursor position from its x and y coordinates.
    unsigned short position = vga_y * 80 + vga_x;

    //select the cursor position high byte register.
    outb(0x3D4, 0x0E);
    //write the high byte of the cursor position.
    outb(0x3D5, (position >> 8) & 0xFF);
    //select the cursor position low byte register.
    outb(0x3D4, 0x0F);
    //write the low byte of the cursor position.
    outb(0x3D5, position & 0xFF);
}

//hide the hardware cursor.
void vga_hide_cursor() {
    //select the cursor start register.
    outb(0x3D4, 0x0A);
    //disable the cursor.
    outb(0x3D5, 0x20);
}

//show the hardware cursor.
void vga_show_cursor() {
    //select the cursor start register.
    outb(0x3D4, 0x0A);
    //enable the cursor and set its starting scanline.
    outb(0x3D5, 0x0E);
    //select the cursor end register.
    outb(0x3D4, 0x0B);
    //set the ending scanline.
    outb(0x3D5, 0x0F);
}

//verify that vga text memory can be accessed.
bool vga_verify() {

    //store the original value of the first screen cell.
    unsigned short original = vga_memory[0];

    //write a known value to the first screen cell.
    vga_memory[0] = ((unsigned short)0x07 << 8) | 'T';

    //check whether the value was written correctly.
    bool valid = vga_memory[0] == (((unsigned short)0x07 << 8) | 'T');

    //restore the original screen cell.
    vga_memory[0] = original;

    //return whether the vga memory test succeeded.
    return valid;
}