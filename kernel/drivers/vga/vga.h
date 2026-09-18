#pragma once

//initialize vga.
void vga_init();
//verify that vga text memory can be accessed.
bool vga_verify();

//write a character to the screen.
void vga_char(char character);
//write a string of text to the screen.
void vga_str(const char* string);
//move all screen lines up by one line.
void vga_scroll();
//clear the entire screen.
void vga_clear();

//current horizontal cursor position.
extern int vga_x;
//current vertical cursor position.
extern int vga_y;

extern volatile unsigned short* vga_memory;

//hardware-cursor
void vga_updatecurs();
void vga_setcurs(int posx, int posy);
void vga_hcurs();
void vga_scurs();

/*
EVERY VGA COLOUR HEX
*/
extern unsigned char VGA_COLOUR;

#define VGA_BLACK       0x0
#define VGA_BLUE        0x1
#define VGA_GREEN       0x2
#define VGA_CYAN        0x3
#define VGA_RED         0x4
#define VGA_MAGENTA     0x5
#define VGA_BROWN       0x6
#define VGA_LIGHT_GREY  0x7
#define VGA_DARK_GREY   0x8
#define VGA_LIGHT_BLUE  0x9
#define VGA_LIGHT_GREEN 0xA
#define VGA_LIGHT_CYAN  0xB
#define VGA_LIGHT_RED   0xC
#define VGA_PINK        0xD
#define VGA_YELLOW      0xE
#define VGA_WHITE       0xF