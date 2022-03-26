#ifndef C64_KERNAL__H
#define C64_KERNAL__H

// ==================================================
//                     constants
// ==================================================

#define CINV 0x0314

// ==================================================
//                       macros
// ==================================================

#define handle_sys_irq()                        \
  asm ("lda $dc0d\n\t"                          \
       "cli\n\t"                                \
       "jmp $ea31")

#define return_sys_irq()                        \
  asm ("jmp $ea7e")

#define is_sys_irq(irq)                         \
  (irq < 0x80)

#endif // #ifndef C64_KERNAL__H
