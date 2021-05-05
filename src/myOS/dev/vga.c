#include "vga.h"
#include "io.h"
#include "uart.h"
#include "string.h"

int col = 0;
int row = 0;

struct vga_char * vga_base_p = (struct vga_char *)VGA_BASE;

struct vga_char * vga_bottom_bar_p = (struct vga_char *)VGA_BASE + VGA_COL * VGA_ROW;

void update_cursor(void)
{
    int position = col + row * VGA_COL;
    outb(0x3D4, 0x0F);
    outb(0x3D5, position);
    outb(0x3D4, 0x0E);
    outb(0x3D5, position >> 8);
}

void clear_screen(void)
{
    uint16_t blank = ' ' | ((0<<4)|7)<<8;
    uint16_t white = ' ' | ((15<<4)|0)<<8;

    memsetw(vga_base_p, blank, VGA_COL * VGA_ROW);
    memsetw(vga_bottom_bar_p, white, VGA_COL);

    col = row = 0;
    update_cursor();
}

void scroll_screen(void)
{
    uint16_t blank = ' ' | ((0<<4)|7)<<8;
  
    memcpy(vga_base_p, (uint16_t *)VGA_BASE + VGA_COL, VGA_COL*(VGA_ROW - 1)*2);
    memsetw(vga_bottom_bar_p - VGA_COL, blank, VGA_COL);

    --row;
    update_cursor();
}

void append_char_to_screen(char c, int color)
{
    struct vga_char *p = vga_base_p;

    switch (c){
        case '\r': 
            col = 0; 
            break;
        case '\n': 
            row = row + 1; 
            col = 0;   
            break;
        case '\b': 
            row -= (col == 0)?1:0;
            col = (col + VGA_COL - 1)%VGA_COL;
            p[row*VGA_COL + col].ch = ' ';
            p[row*VGA_COL + col].fc = color;
            p[row*VGA_COL + col].bc = 0;
            break;
        case '\t': 
            do {
                p[row*VGA_COL + col].ch = ' ';
                p[row*VGA_COL + col].fc = color;
                p[row*VGA_COL + col].bc = 0;
                row += (col + 1) / VGA_COL;
                col = (col + 1) % VGA_COL;
            } while (col % 4 != 0); 
            break;
        default: 
            p[row*VGA_COL + col].ch = c;
            p[row*VGA_COL + col].fc = color;
            p[row*VGA_COL + col].bc = 0;
            row += (col + 1) / VGA_COL;
            col = (col + 1) % VGA_COL;      
    }

    if (row >= VGA_ROW) {
        scroll_screen();
    }

    update_cursor();
}

void append2screen(char* str, int color)
{
    for (char* p = str; *p != '\0'; ++p) {
        append_char_to_screen(*p, color);
    }
}

inline void set_char_bottom(char c, unsigned int index) {
    vga_bottom_bar_p[index].ch = c;
}

void set_string_bottom(char *str, unsigned int start) {
    struct vga_char *vga_p = vga_bottom_bar_p;
    vga_p += start;
    for (char* p = str; *p != '\0'; ++p) {
        vga_p->ch = *p;
        ++vga_p;
    }
}
