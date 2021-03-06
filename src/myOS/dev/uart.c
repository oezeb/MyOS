#include "uart.h"
#include "io.h"

// unsigned char uart_get_char(void)
// {
// }

void uart_put_char(unsigned char c)
{
    if (c == '\n') {
        outb(uart_base, '\r');
        outb(uart_base, '\n');
        return;
    }
    outb(uart_base, c);
}

void uart_put_chars(char* str)
{
    for (char* p = str; *p; ++p) {
        uart_put_char(*p);
    }
}

unsigned char uart_get_char(void) {
    while (!(inb(uart_base+5)&1));
    
    return inb(uart_base);
}
