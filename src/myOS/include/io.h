#ifndef __I386_IO_H__
#define __I386_IO_H__

#include "type.h"

unsigned char inb(uint16_t port_from);

void outb(uint16_t port_to, uint8_t value);

#endif