#pragma once

//initialize vga.
void vga_init();
//verify that vga text memory can be accessed.
bool vga_verify();

//write a character to the screen.
void vga_write_char(char character);
//write a string of text to the screen.
void vga_write_string(const char* string);
//move all screen lines up by one line.
void vga_scroll();
//clear the entire screen.
void vga_clear();

//hardware-cursor
void vga_update_cursor();
void vga_hide_cursor();
void vga_show_cursor();