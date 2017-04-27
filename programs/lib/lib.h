#include "int.h"
#ifndef LIB_H
#define LIB_H

#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_BROWN 6
#define COLOR_LIGHT_GREY 7
#define COLOR_DARK_GREY 8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED 12
#define COLOR_LIGHT_MAGENTA 13
#define COLOR_LIGHT_BROWN 14
#define COLOR_WHITE 15

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define KEY_BUFFER_SIZE 0x800

void set_char_at(u8 c, u8 fg, u8 bg, u8 x, u8 y);
void clear_screen(u8 color);
int next_key_event();

#endif
