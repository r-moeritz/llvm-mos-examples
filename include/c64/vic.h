#ifndef C64_VIC__H
#define C64_VIC__H

// ==================================================
//                     constants
// ==================================================

// colours
#define BLACK 0
#define WHITE 1
#define RED 2
#define CYAN 3
#define PURPLE 4
#define GREEN 5
#define BLUE 6
#define YELLOW 7
#define ORANGE 8
#define BROWN 9
#define LT_RED 10
#define GRAY_1 11
#define GRAY_2 12
#define LT_GREEN 13
#define LT_BLUE 14
#define GRAY_3 15

// registers
#define VIC 0xd000
#define SCROLY VIC + 0x11
#define RASTER VIC + 0x12
#define VICIRQ VIC + 0x19
#define IRQMSK VIC + 0x1a
#define BORDER VIC + 0x20

// ==================================================
//                       macros
// ==================================================

#define ack_vic_irq(irq)                        \
  asm ("lda $d019\n\t"                          \
       "sta $d019"                              \
       : "=r" (irq)                             \
       :                                        \
       : "a"                                    \
       )

#endif // #ifndef C64_VIC__H
