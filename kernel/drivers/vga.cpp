#include "kernel/drivers/vga.h"

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


void vga_write_char(char character) {
    //convert the two-dimensional cursor position into a one-dimensional array index.
    int index = vga_y * 80 + vga_x;
    //combine the text colour and character into one 16-bit vga entry.
    vga_memory[index] = ((unsigned short)0x07 << 8) | character;
    //move the cursor one character to the right.
    vga_x++;
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