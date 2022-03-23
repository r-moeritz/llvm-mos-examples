/*
  raster-c64.c -- a basic raster IRQ demonstration for the Commodore 64

  This is the most basic example of a raster interrupt handler that I could
  think of. It is an adaptation of the example program "rasterzeilen-irq" from
  the book "C64/C128 Alles über Maschinensprache" by Frank Riemenschneider.
*/

#include "types.h"
#include "macros.h"

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
void handle_irq() __attribute__ ((noreturn));

void main() {
  sei ();

  WPTR irqvec = IRQVEC;
  PTR raster = RASTER;
  PTR scroly = SCROLY;
  PTR irqmsk = IRQMSK;

  *irqvec = &handle_irq;
  *raster = RTOP;
  *scroly = *scroly & 0x7f;
  *irqmsk = 0x81;

  cli ();
}

void handle_irq() {
  PTR raster = RASTER;
  PTR border = BORDER;

  // read and acknowledge vic irq
  BYTE irq;
  ack_vic_irq (irq);

  if (irq <= 127) {
    // system interrupt
    handle_sys_irq ();
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

  return_sys_irq ();
}
