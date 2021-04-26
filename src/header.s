.set FLAGS,    0
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)
 
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .text
.global _start
_start:
    movl $0x2f652f48, 0xB8000   //He
    movl $0x2f6c2f6c, 0xB8004   //ll
    movl $0x2f202f6f, 0xB8008   //o 
    movl $0x2f6f2f57, 0xB800C   //Wo
    movl $0x2f6c2f72, 0xB8010   //rl
    movl $0x2f202f64, 0xB8014   //d 
    movl $0x2f722f66, 0xB8018   //fr
    movl $0x2f6d2f6f, 0xB801C   //om
    movl $0x2f452f20, 0xB8020   // E
    movl $0x2f652f7a, 0xB8024   //ze
    movl $0x2f692f6b, 0xB8028   //ki
    movl $0x2f6c2f65, 0xB802C   //el
    movl $0x2f3b2f20, 0xB8030   // ;
    movl $0x2f202f29, 0xB8034   //) 
    movl $0x2f742f53, 0xB8038   //St
    movl $0x2f642f75, 0xB803C   //ud
    movl $0x2f6e2f65, 0xB8040   //en
    movl $0x2f202f74, 0xB8044   //t 
    movl $0x2f752f4e, 0xB8048   //Nu
    movl $0x2f622f6d, 0xB804C   //mb
    movl $0x2f722f65, 0xB8050   //er
    movl $0x2f202f3a, 0xB8054   //: 
    movl $0x2f4c2f50, 0xB8058   //PL
    movl $0x2f392f31, 0xB805C   //19
    movl $0x2f312f32, 0xB8060   //21
    movl $0x2f302f35, 0xB8064   //50
    movl $0x2f312f30, 0xB8068   //01
    hlt
