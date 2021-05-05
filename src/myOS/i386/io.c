#include "io.h"
#include "type.h"

unsigned char inb(uint16_t port_from)
{
    char value;
    __asm__ __volatile__("inb %w1, %0"
                         : "=a"(value)
                         : "Nd"(port_from));
    return value;
}

void outb(uint16_t port_to, uint8_t value)
{
    __asm__ __volatile__("outb %b0, %w1" ::"a"(value), "Nd"(port_to));
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
}