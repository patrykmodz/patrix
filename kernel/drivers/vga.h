#pragma once

//initialize vga.
void vga_init();
//write a character to the screen.
void vga_write_char(char character);
//write a string of text to the screen.
void vga_write_string(const char* string);
//move all screen lines up by one line.
void vga_scroll();