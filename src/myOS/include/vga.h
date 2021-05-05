#ifndef __VGA_H__
#define __VGA_H__

#define VGA_COL 80
#define VGA_ROW 24

#define VGA_BASE 0xB8000

struct vga_char{
    char ch: 8;
    char fc: 4;
    char bc: 4;
};

void update_cursor(void);
void clear_screen(void);
void scroll_screen(void);
void append_char_to_screen(char c, int color);
void append2screen(char* str, int color);
void set_char_bottom(char c, unsigned int index);
void set_string_bottom(char *str, unsigned int start);

#endif