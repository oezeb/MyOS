/*
 * 本文件实现vga的相关功能，清屏和屏幕输出
 * clear_screen和append2screen必须按照如下借口实现
 * 可以增加其他函数供clear_screen和append2screen调用
 */
 
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e

extern void outb (unsigned short int port_to, unsigned char value);
extern unsigned char inb(unsigned short int port_from);

int getRow(int offset) { //get row from offset
    return offset / (2 * MAX_COLS);
}

int getOffset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int newLine(int offset) { //move offset to new line
    return getOffset(0, getRow(offset) + 1);
}

void putChar(char character, int offset, int color) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = color;
}

int getCursor() {
    outb(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int offset = inb(VGA_DATA_REGISTER) << 8;
    outb(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += inb(VGA_DATA_REGISTER);
    return offset * 2;
}

void setCursor(int offset) {
    offset /= 2;
    outb(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    outb(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    outb(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    outb(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

void copyMemory(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

int scroll(int offset) {
    copyMemory(
            (char *) (getOffset(0, 1) + VIDEO_ADDRESS),
            (char *) (getOffset(0, 0) + VIDEO_ADDRESS),
            MAX_COLS * (MAX_ROWS - 1) * 2
    );

    for (int col = 0; col < MAX_COLS; col++) {
        putChar(' ', getOffset(col, MAX_ROWS - 1),WHITE_ON_BLACK);
    }

    return offset - 2 * MAX_COLS;
}

void clear_screen(void) {
    for (int i = 0; i < MAX_COLS * MAX_ROWS; ++i) {
        putChar(' ', i * 2, WHITE_ON_BLACK);
    }
    setCursor(getOffset(0, 0));
}

void append2screen(char *str,int color){
    int offset = getCursor();
    int i = 0;
    while (str[i] != '\0') {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scroll(offset);
        }
        if (str[i] == '\n') {
            offset = newLine(offset);
        } 
        else {
            putChar(str[i], offset,color);
            offset += 2;
        }
        i++;
    }
    setCursor(offset);
}
