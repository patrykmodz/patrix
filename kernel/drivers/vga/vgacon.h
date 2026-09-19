#pragma once

void vgacon_init();
bool vgacon_verify();
void vgacon_char(char character);
void vgacon_bck();
void vgacon_str(const char* string);
void vgacon_syncurs();
void vgacon_clear();


extern int curs_x;
extern int curs_y;
