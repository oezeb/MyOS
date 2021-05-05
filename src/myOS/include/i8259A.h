#ifndef __DEV_I8259A_H__
#define __DEV_I8259A_H__

#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1

void init8259A(void);

#endif