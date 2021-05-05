#include "i8253.h"
#include "io.h"

void init8253(void) {
    outb(0x43, 0x34);
    outb(0x40, I8253_FREQ & 0x00ff);
    outb(0x40, I8253_FREQ >> 8);
}