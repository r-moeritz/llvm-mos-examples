#ifndef C64_MACROS__H
#define C64_MACROS__H

#define ack_vic_irq(irq)                        \
  asm ("lda $d019\n\t"                          \
       "sta $d019"                              \
       : "=r" (irq)                             \
       :                                        \
       : "a"                                    \
       )

#define handle_sys_irq()                        \
  asm ("lda $dc0d\n\t"                          \
       "cli\n\t"                                \
       "jmp $ea31")

#define return_sys_irq()                        \
  asm ("jmp $ea7e")

#define is_sys_irq(irq)                         \
  (irq < 0x80)

#endif // #ifndef C64_MACROS__H
