#include "irqs.h"
#include "vga.h"

/* clear interrupt */
inline void enable_interrupt(void){
    __asm__ __volatile__ ("sti");
}

/* set interrupt */
inline void disable_interrupt(void){
    __asm__ __volatile__ ("cli");
}

void ignoreIntBody(void) {
    set_string_bottom("unknown interrupt", 0);
}