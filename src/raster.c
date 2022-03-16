#include "types.h"

// memory locations
const WORD VIC = 0xd000;
const WORD SCROLY = VIC + 0x11;
const WORD VICIRQ = VIC + 0x19;
const WORD IRQMSK = VIC + 0x1a;
const WORD RASTER = VIC + 0x12;
const WORD BORDER = VIC + 0x20;
const WORD IRQVEC = 0x314;

// values
const BYTE GRAY3 = 15;
const BYTE GREEN = 5;
const BYTE RTOP = 106;
const BYTE RBOTTOM = 194;

// function prototypes
void handleInterrupt() __attribute__ ((noreturn));

void main() {
  asm ("sei");

  WPTR irqvec = IRQVEC;
  PTR raster = RASTER;
  PTR scroly = SCROLY;
  PTR irqmsk = IRQMSK;

  *irqvec = &handleInterrupt;
  *raster = RTOP;
  *scroly = *scroly & 0x7f;
  *irqmsk = 0x81;

  asm ("cli");
}

void handleInterrupt() {
  BYTE irq;
  PTR raster = RASTER;
  PTR border = BORDER;

  // read and acknowledge irq
  asm("lda $d019\n\t"
      "sta $d019"
      : "=r" (irq) // output
      : // no input
      : "a" // clobbered registers
      );

  if (irq <= 127) {
    // system interrupt
    asm ("lda $dc0d\n\t"
         "cli\n\t"
         "jmp $ea31");
  }

  // raster interrupt
  if (*raster < RBOTTOM) {
    *border = GREEN;
    *raster = RBOTTOM;
  }
  else {
    *border = GRAY3;
    *raster = RTOP;
  }

  asm ("jmp $ea7e");
}
