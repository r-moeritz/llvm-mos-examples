/*
  raster-c64.c -- a basic raster IRQ demonstration for the Commodore 64

  This is the most basic example of a raster interrupt handler that I could
  think of. It is an adaptation of the example program "rasterzeilen-irq" from
  the book "C64/C128 Alles über Maschinensprache" by Frank Riemenschneider.
*/

#include "types.h"
#include "macros.h"
#include "c64/kernal.h"
#include "c64/vic.h"

// values
const BYTE RTOP = 106;
const BYTE RBOTTOM = 194;

// function prototypes
void handle_irq() __attribute__ ((noreturn));

void main() {
  sei ();

  WPTR irqvec = CINV;
  PTR raster = RASTER;
  PTR scroly = SCROLY;
  PTR irqmsk = IRQMSK;

  *irqvec = &handle_irq;
  *raster = RTOP;
  *scroly &= 0x7f;
  *irqmsk = 0x81;

  cli ();
}

void handle_irq() {
  PTR raster = RASTER;
  PTR border = BORDER;

  // read and acknowledge vic irq
  BYTE irq;
  ack_vic_irq (irq);

  if (is_sys_irq (irq)) {
    // system interrupt
    handle_sys_irq ();
  }

  // raster interrupt
  if (*raster < RBOTTOM) {
    *border = GREEN;
    *raster = RBOTTOM;
  }
  else {
    *border = GRAY_3;
    *raster = RTOP;
  }

  return_sys_irq ();
}
