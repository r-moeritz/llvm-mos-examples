#ifndef MACROS__H
#define MACROS__H

#define sei()                                   \
  asm ("sei")

#define cli()                                   \
  asm ("cli")

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

#endif // #ifndef MACROS__H
