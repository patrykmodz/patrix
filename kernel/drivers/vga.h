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

//hardware-cursor
void vga_updatecurs();
void vga_hcurs();
void vga_scurs();